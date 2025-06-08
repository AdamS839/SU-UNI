#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <limits>

class PLYReader {
public:
    PLYReader(const std::string& filepath) : filepath(filepath) {}

    void readFile() {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file." << std::endl;
            return;
        }

        std::string line;
        bool headerEnd = false;
        int vertexCount = 0, faceCount = 0;
        int currentVertexCount = 0, currentFaceCount = 0;

        std::vector<std::array<float, 3>> vertices;
        std::vector<std::vector<int>> faces;

        // Read the header
        while (std::getline(file, line)) {
            if (line.find("end_header") != std::string::npos) {
                headerEnd = true;
                break;
            }

            if (line.find("element") != std::string::npos) {
                // Split the line
                size_t pos = line.find("vertex");
                if (pos != std::string::npos) {
                    vertexCount = std::stoi(line.substr(pos + 7));
                }

                pos = line.find("face");
                if (pos != std::string::npos) {
                    faceCount = std::stoi(line.substr(pos + 5));
                }
            }
        }

        if (!headerEnd) {
            std::cerr << "Error: Missing 'end_header' line in PLY file." << std::endl;
            return;
        }

        // Read vertices
        while (std::getline(file, line)) {
            if (line.find("end_header") != std::string::npos) {
                headerEnd = true;
                break;
            }
        
            if (line.find("element vertex") != std::string::npos) {
                size_t last_space = line.rfind(' ');
                if (last_space != std::string::npos) {
                    vertexCount = std::stoi(line.substr(last_space + 1));
                }
            }
        
            if (line.find("element face") != std::string::npos) {
                size_t last_space = line.rfind(' ');
                if (last_space != std::string::npos) {
                    faceCount = std::stoi(line.substr(last_space + 1));
                }
            }
        }

        // Read faces
        while (currentFaceCount < faceCount && std::getline(file, line)) {
            if (line.empty()) continue;

            int nVertices;
            // First number is the count of vertices in the face
            if (std::sscanf(line.c_str(), "%d", &nVertices) != 1) {
                std::cerr << "Error: Invalid face data at line " << currentFaceCount + 1 << std::endl;
                return;
            }

            // Now extract the vertex indices for the face
            std::vector<int> vertexIndices;
            size_t pos = line.find(' '); // skip the first number (the number of vertices)
            size_t start = pos + 1; // Start after the first number

            while ((pos = line.find(' ', start)) != std::string::npos) {
                int vertexIndex = std::stoi(line.substr(start, pos - start));
                vertexIndices.push_back(vertexIndex);
                start = pos + 1;
            }

            // Add the last vertex index after the final space
            int vertexIndex = std::stoi(line.substr(start));
            vertexIndices.push_back(vertexIndex);

            // Check if the number of vertex indices matches the expected number for this face
            if (vertexIndices.size() != nVertices) {
                std::cerr << "Error: Face has incorrect number of vertex indices at line " << currentFaceCount + 1 << std::endl;
                return;
            }

            faces.push_back(vertexIndices);
            currentFaceCount++;
        }

        // Check if the number of vertices and faces matches the header count
        if (currentVertexCount != vertexCount) {
            std::cerr << "Error: Number of vertices read does not match the header count." << std::endl;
        }
        if (currentFaceCount != faceCount) {
            std::cerr << "Error: Number of faces read does not match the header count." << std::endl;
        }

        std::cout << "Successfully read PLY file." << std::endl;
    }

private:
    std::string filepath;
};

int main() {
    PLYReader reader("your_file.ply");
    reader.readFile();
    return 0;
}
