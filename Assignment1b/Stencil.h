#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "Box.h"
#include <vector>
#include <iostream>
#include "VertexAttrib.h"
#include <PolygonMesh.h>
#include <GLFW/glfw3.h>
using namespace std;

/**
 * @brief This class represents a stencil constructed out of a rectangular
 * piece of paper with rectangular cutouts. All rectangles here are
 * axis-aligned.
 * 
 */
class Stencil{

public:
    Stencil(int x, int y, int width, int height);
    ~Stencil();

    void cut(int x, int y, int width, int height);
    vector<Box> getRectangles();

    // For converting stencil boxes into vertices and indices
    vector<util::PolygonMesh<VertexAttrib>> getMeshes();

private:
    vector<Box> boxes;
};

Stencil::Stencil(int x, int y, int width, int height) {
    this->boxes.push_back(Box(x, y, width, height));
}

Stencil::~Stencil() {}

vector<Box> Stencil::getRectangles() {
    return vector<Box>(this->boxes);
}

void Stencil::cut(int x, int y, int width, int height) {
    vector<Box> result;
    Box other(x, y, width, height);

    if (this->boxes.size() == 0) {
        return; // Empty
    }

    for (int i = 0; i < boxes.size(); i++) {
        if (other.overlaps(boxes[i])) {
            Box common = boxes[i].intersect(other);
            vector<Box> containedResult = boxes[i].containedDifference(common);
            result.insert(result.end(), containedResult.begin(), containedResult.end());
        }
        else {
            result.push_back(boxes[i]);
        }
    }
    boxes = result;
}

vector<util::PolygonMesh<VertexAttrib>> Stencil::getMeshes() {
    vector<util::PolygonMesh<VertexAttrib>> meshes;

    // Loop through all boxes and generate meshes
    for (const auto& box : boxes) {
        vector<glm::vec4> positions;
        vector<VertexAttrib> vertexData;
        vector<unsigned int> indices;

        // Create vertex data for the box (4 vertices for a rectangle)
        positions.push_back(glm::vec4(box.getX(), box.getY(), 0, 1));                          // Bottom-left
        positions.push_back(glm::vec4(box.getX() + box.getWidth(), box.getY(), 0, 1));         // Bottom-right
        positions.push_back(glm::vec4(box.getX() + box.getWidth(), box.getY() + box.getHeight(), 0, 1));  // Top-right
        positions.push_back(glm::vec4(box.getX(), box.getY() + box.getHeight(), 0, 1));         // Top-left

        // Create vertex attributes
        for (int i = 0; i < positions.size(); i++) {
            vector<float> data;
            VertexAttrib v;
            for (int j = 0; j < 4; j++) {
                data.push_back(positions[i][j]);
            }
            v.setData("position", data);
            vertexData.push_back(v);
        }

        // Create indices (2 triangles for the rectangle)
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);

        util::PolygonMesh<VertexAttrib> mesh;
        mesh.setVertexData(vertexData);
        mesh.setPrimitives(indices);
        mesh.setPrimitiveType(GL_TRIANGLES);
        mesh.setPrimitiveSize(3);

        meshes.push_back(mesh);
    }

    return meshes;
}

#endif