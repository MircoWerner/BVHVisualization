/**
 * BVHVisualization.
 *
 * @author Mirco Werner
 */
#include "renderengine/engine/RenderEngine.h"
#include "renderengine/utils/IOUtils.h"

#include "visualization/BVHVisualizationRenderLogic.h"


int main(int argc, char *argv[]) {
    GLFWwindow *window = RenderEngine::initGL("BVHVisualization", 1920, 1080);
    if (window == nullptr) {
        return -1;
    }
    RenderEngine::initImGui(window);

    IRenderLogic *renderLogic = new BVHVisualizationRenderLogic();

    for (int i = 1; i < argc; i++) {
        renderLogic->m_startupParameters.emplace_back(argv[i]);
    }

    auto *renderEngine = new RenderEngine(window, renderLogic);
    try {
        renderEngine->run();
    } catch (const std::exception &e) {
        delete renderEngine;
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    delete renderEngine;

    return EXIT_SUCCESS;
}
