#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <functional>
#include <cstddef>
#include <cmath>
#include <limits>

struct Vertex {
    float x, y, z;
};

struct Face {
    std::vector<int> indices;
};

class Object3d {
private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

public:
    Object3d() {}

    Object3d(const std::string& filename) {
        std::ifstream in(filename.c_str());
        if (in) {
            loadFromStream(in);
        }
    }

    Object3d(std::istream& in) {
        loadFromStream(in);
    }

    int getVertexCount() const {
        return vertices.size();
    }

    int getFaceCount() const {
        return faces.size();
    }

    void save(const std::string& filename) const {
        std::ofstream out(filename.c_str());
        if (!out) {
            return;
        }
        print(out);
    }

    void print(std::ostream& out) const {
        out << "ply\n";
        out << "format ascii 1.0\n";
        out << "element vertex " << vertices.size() << "\n";
        out << "property float x\n";
        out << "property float y\n";
        out << "property float z\n";
        out << "element face " << faces.size() << "\n";
        out << "property list uchar int vertex_indices\n";
        out << "end_header\n";

        for (Vertex v : vertices) {
            out << v.x << " " << v.y << " " << v.z << "\n";
        }

        for (Face f : faces) {
            out << f.indices.size();
            for (int index : f.indices) {
                out << " " << index;
            }
            out << "\n";
        }
    }

    Object3d cut(std::function<bool(float, float, float)> predicate) const {
        Object3d result;
        result.vertices = vertices;

        for (Face f : faces) {
            bool all_good = true;
            for (int idx : f.indices) {
                Vertex v = vertices[idx];
                if (!predicate(v.x, v.y, v.z)) {
                    all_good = false;
                }
            }
            if (all_good) {
                result.faces.push_back(f);
            }
        }

        return result;
    }

    void flip() {
        for (Face& f : faces) {
            int n = f.indices.size();
            for (int i = 0; i < n / 2; ++i) {
                int temp = f.indices[i];
                f.indices[i] = f.indices[n - i - 1];
                f.indices[n - i - 1] = temp;
            }
        }
    }

private:
    void loadFromStream(std::istream& in) {
        std::string line;
        int vertexCount = 0;
        int faceCount = 0;
        bool readingHeader = true;

        while (std::getline(in, line)) {
            if (readingHeader) {
                if (line.length() >= 7 && line.substr(0, 7) == "comment") {
                } else if (line == "ply") {
                } else if (line == "format ascii 1.0") {
                } else if (line.length() >= 14 && line.substr(0, 14) == "element vertex") {
                    vertexCount = std::atoi(line.c_str() + 15);
                } else if (line.length() >= 12 && line.substr(0, 12) == "element face") {
                    faceCount = std::atoi(line.c_str() + 13);
                } else if (line.length() >= 8 && line.substr(0, 8) == "property") {
                } else if (line == "end_header") {
                    readingHeader = false;
                }
            } else if (vertexCount > 0) {
                float x = 0, y = 0, z = 0;
                const char* ptr = line.c_str();
                x = std::strtof(ptr, (char**)&ptr);
                y = std::strtof(ptr, (char**)&ptr);
                z = std::strtof(ptr, (char**)&ptr);
                vertices.push_back(Vertex{x, y, z});
                vertexCount--;
            } else if (faceCount > 0) {
                int expectedVertices = 0;
                const char* ptr = line.c_str();
                expectedVertices = std::strtol(ptr, (char**)&ptr, 10);
                Face f;
                for (int i = 0; i < expectedVertices; ++i) {
                    int idx = std::strtol(ptr, (char**)&ptr, 10);
                    f.indices.push_back(idx);
                }
                faces.push_back(f);
                faceCount--;
            }
        }
    }
};

// THIS CODE IS WORKING

int main() {
    Object3d b("./bunny.ply");
    Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
    return y + z < 0.12;
    }) ;
    b_cut.save("./bunny_cut1.ply");
}