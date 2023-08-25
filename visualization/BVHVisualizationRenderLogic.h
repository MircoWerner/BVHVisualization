#pragma once

#include <GL/glew.h>

#include "../../renderengine/engine/IRenderLogic.h"
#include "../../renderengine/camera/ThirdPersonCamera.h"

#include "BVHVisualizationRenderer.h"

/**
 * Render logic of the program.
 * Handles inputs, gui and calls the renderer.
 *
 * @author Mirco Werner
 */
class BVHVisualizationRenderLogic : public IRenderLogic {
public:
    void init() override;

    void update(float time, KeyboardInput *keyboardInput, MouseInput *mouseInput) override;

    void render() override;

    void renderGui() override;

    void cleanUp() override;

    void onWindowResized(int width, int height) override;

    bool generateSceneScreenshot(int number, SceneScreenshotInfo *info) override;

private:
    ThirdPersonCamera m_camera;
    BVHVisualizationRenderer m_renderer;

    glm::ivec2 windowSize = glm::ivec2(1920, 1080);
};
