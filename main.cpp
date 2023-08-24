/**
 * BVHVisualizer.
 *
 * @author Mirco Werner
 */
#include "renderengine/engine/RenderEngine.h"
#include "renderengine/utils/IOUtils.h"


int main(int argc, char *argv[]) {
    GLFWwindow *window = RenderEngine::initGL("BVHVisualizer", 1920, 1080);
    if (window == nullptr) {
        return -1;
    }
    RenderEngine::initImGui(window);

    IRenderLogic *renderLogic = new SomeRenderLogic();

    auto *renderEngine = new RenderEngine(window, renderLogic);
    renderEngine->run();
    delete renderEngine;

    return 0;
}
