#include "Object3d.h"

int main(){

    {
        std::ifstream file("example.ply");
        // Object3d bWrong(file);

        Object3d b("./bunny.ply");
        Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
        return y + z < 0.12;
        }) ;
        b_cut.save("./bunny_cut1112.ply");

        // std::cout << "Върхове на заека: " << b.getVertexCount() << std::endl;
        // std::cout << "Лица на заека: "  << b.getFaceCount() << std::endl;
        // std::cout << "Върхове на отрязан заек: " << b_cut.getVertexCount() << std::endl;
        // std::cout << "Лица на отрязан заек: "  << b_cut.getFaceCount() << std::endl;
    }

    Object3d cube = Object3d::createCube(10.0);
    //cube.save("./newcube.ply");

    {
        Object3d sphere = Object3d::createSphere(20.0);
        //sphere.save("./newSphere.ply");
    
        std::cout << "Върхове на сферата: " << sphere.getVertexCount() << std::endl;
        std::cout << "Лица на сферата: "  << sphere.getFaceCount() << std::endl;
    }

    Object3d object("./bunny_cut.ply");
    // object.print(std::cout);
}