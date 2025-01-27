#include "Controller.h"
#include <iostream>
using namespace std;

Controller::Controller(Model& m,View& v) {
    model = m;
    view = v;
}

Controller::~Controller()
{

}

void Controller::run()
{
    vector<util::PolygonMesh<VertexAttrib> > meshes = model.getMeshes();
    view.init(this,meshes);
    while (!view.shouldWindowClose()) {
        view.display();
    }
    view.closeWindow();
    exit(EXIT_SUCCESS);
}

void Controller::onkey(int key, int scancode, int action, int mods)
{
}

void Controller::reshape(int width, int height) 
{
    glViewport(0, 0, width, height);
}

void Controller::dispose()
{
    view.closeWindow();
}

void Controller::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}