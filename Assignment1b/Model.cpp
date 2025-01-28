#include "Model.h"
#include "Box.h"
#define GLM_FORCE_SWIZZLE
#include "Stencil.h"
using namespace std;

#include "VertexAttribWithColor.h"
#include "PolygonMesh.h" // Include your PolygonMesh header

Model::Model() {
    Stencil stencil(0,0,310,310);
    
    //create a set of 10x10 windows
    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++) {
            stencil.cut(10+30*(i),10+30*(j),20,20);
        }
    }

    stencil.cut(110,80,120,55);
    meshes = stencil.getMeshes(); // Store meshes for rendering
    // Example of adding a single mesh to the vector
    if (!meshes.empty()) {
        meshes.push_back(meshes[0]);
    }
}

vector<util::PolygonMesh<VertexAttrib>> Model::getMeshes() {
    return meshes;
}

Model::~Model() {

}