#ifndef __Object3d_H
#define __Object3d_H
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include <cmath>
#include <limits>


struct Vertex
{
    float x, y , z; // координати на точка
};

struct Face{
    std::vector<int> indices; // индекси
};

class Object3d{
private:
    std::vector<Vertex> vertices; // върхове
    std::vector<Face> faces; // лица

    void startFile(std::istream& file){
        std::string str;
        bool inHeader = true;
        int vertexCount = 0;
        int faceCount = 0;
        bool foundPly = false;
        bool foundAscii = false;

        while(std::getline(file, str)){
            if(inHeader){
                if(str.substr(0, 7) == "comment") continue;
                if(str == "ply") {foundPly = true; continue;}
                if(str == "format ascii 1.0") {foundAscii = true; continue;}
                
                if(str.substr(0,14) == "element vertex"){
                    vertexCount = std::stoi(str.substr(15));
                    continue;
                } // взимане на брой на върхове
                
                if(str.substr(0, 12) == "element face"){
                    faceCount = std::stoi(str.substr(13));
                    continue;
                } // взимане на брой лица

                if(str == "end_header"){
                    if(!foundPly || !foundAscii){
                        throw std::invalid_argument("Keyword 'ply' or 'format ascii 1.0' missing");
                    } // проверка за наличие на думи ply и format ascii 1.0
                    inHeader = false;
                    continue;
                }
            }
            else if (vertexCount > 0) { // преобразуваме координатите от str към float
                float x = 0, y = 0, z = 0;
                std::size_t pos = 0;
                std::size_t next_pos = 0;
                x = std::stof(str.substr(pos), &next_pos);
                pos += next_pos;
                y = std::stof(str.substr(pos), &next_pos);
                pos += next_pos;
                z = std::stof(str.substr(pos), &next_pos);
                vertices.push_back(Vertex{x, y, z});
                vertexCount--; // махаме 1 връх от всички 
            } 
            else if (faceCount > 0) { // взимаме върховете, четем индексите на върховете от str и ги добавяме към face
                std::size_t pos = 0;
                std::size_t next_pos = 0;
                int expectedVertices = std::stoi(str.substr(pos), &next_pos);
                pos += next_pos;
                Face face;
                for (int i = 0; i < expectedVertices; ++i) {
                    int index = std::stoi(str.substr(pos), &next_pos);
                    pos += next_pos;
                    face.indices.push_back(index);
                }
                faces.push_back(face);
                faceCount--;
            }
        }
    }            
    
public:
    Object3d(const std::string &filename){ // файл с подадено име 
        std::ifstream file(filename);
        if(!file.is_open()){
            throw std::invalid_argument("Cant open file");
        }
        startFile(file);
    }
    
    Object3d(std::istream &file){ // входен поток
        if(!file){
            throw std::invalid_argument("Cant open this file");
        }
        startFile(file);
    }

    Object3d() {}

    int getVertexCount() const{ // връща брой върхове
        return vertices.size();
    }

    int getFaceCount() const{ // връща брой лица
        return faces.size();    
    }

    void save(const std::string &o) const{ // запазваме нов обект във файл с някакво подадено име
        std::ofstream file(o);
        file << "ply\n";
        file << "format ascii 1.0\n";
        file << "element vertex " << vertices.size() << "\n";
        file << "property float x\n";
        file << "property float y\n";
        file << "property float z\n";
        file << "element face " << faces.size() << "\n";
        file << "property list uchar int vertex_indices\n";
        file << "end_header\n";

        for(const Vertex& v : vertices){
            file << v.x << " " << v.y << " " << v.z << "\n";
        }

        for (const Face& f : faces){
            file << f.indices.size();
            for(int index : f.indices){
                file << " " << index;
            }
            file << "\n";
        }
    }

    void print(std::ostream &os) const{ // изписваме нещата от обект
        os << "ply\n";
        os << "format ascii 1.0\n";
        os << "element vertex " << vertices.size() << "\n";
        os << "property float x\n";
        os << "property float y\n";
        os << "property float z\n";
        os << "element face " << faces.size() << "\n";
        os << "property list uchar int vertex_indices\n";
        os << "end_header\n";

        for(const Vertex& v : vertices){
            os << v.x << " " << v.y << " " << v.z << "\n";
        }

        for (const Face& f : faces){
            os << f.indices.size();
            for(int index : f.indices){
                os << " " << index;
            }
            os << "\n";
        }
    }

    Object3d cut(std::function<bool(float, float, float)> func){ // добавяме върхове и лица към нов обект по някакъв предикат
        Object3d object;
        object.vertices = vertices;
        for (Face face : faces){
            bool validPredicate = true;
            for(int index : face.indices){
                Vertex vert = vertices[index];
                if(!func(vert.x, vert.y, vert.z)){
                    validPredicate = false;
                }
            }
            if(validPredicate){ // ако не отговарят на предиката, не ги добавяме
                object.faces.push_back(face);
            }
        }
        return object;
    }

    void flip(){ // обръщаме индексите на лицата на обекта
        for(Face &face : faces){
            int n = face.indices.size();
            for (int i = 0; i < n / 2; ++i){   
                int temp = face.indices[i];
                face.indices[i] = face.indices[n - 1 -i];
                face.indices[n - 1 -i] = temp;
            }
        }
    }

    static Object3d createCube(float edgelength){ // генерираме кубче с някаква подадена дължина на ръба
        Object3d cube;
        float s = edgelength / 2.0f;
        cube.vertices = {
            {-s,-s,-s},{s,-s,-s},{s,-s,s},{-s,-s,s},{-s,s,-s},{s,s,-s},{s,s,s},{-s,s,s}
        };
        cube.faces={
            {{0,1,2,3}},{{7,6,5,4}},{{0,4,5,1}},{{1,5,6,2}},{{2,6,7,3}},{{3,7,4,0}}
        };
        return cube;
    }

    //Daniel Sieger - Generating Meshes of a Sphere blog
    static Object3d createSphere(float radius){ // генериране на сфера с даден радиус
        Object3d sphere;
        int latsegment = 10; // брой точки на ширина /latitude
        int longsegment = 20; // брой точки на височина /longitude
        for (int lat = 0; lat <= latsegment; ++lat){
            float phi = lat * M_PI / latsegment; // phi -> ъгли по ширина
            float sinphi = std::sin(phi);
            float cosphi = std::cos(phi);
            for (int lon = 0; lon <= longsegment; ++lon){
                float psi = lon * 2.0f * M_PI / longsegment; // psi -> ъгли по височина
                float sinpsi = std::sin(psi);
                float cospsi = std::cos(psi);

                // сферични координати на точката в 3-мерното пространство
                float x = radius * cospsi * sinphi;
                float y = radius * cosphi;
                float z = radius * sinpsi * sinphi;

                sphere.vertices.push_back(Vertex{x,y,z}); // добавяме точката към върховете
            }
        }

        for (int lat = 0; lat < latsegment; ++lat){
            for (int lon = 0; lon < longsegment; ++lon){
                int current = lat * (longsegment + 1) + lon;
                int next = current + longsegment + 1;
                
                //sphere.faces.push_back({{current, next, next + 1, current + 1}}); // сфера с квадратно лице
                
                //2 триъгълни лица, които образуват 1 квадратно лице 
                sphere.faces.push_back({{current, next, current + 1}});
                sphere.faces.push_back({{next, next+1, current + 1}});
            }
        }
        return sphere;
    }

};

#endif