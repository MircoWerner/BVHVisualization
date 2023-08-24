#include "BVHVisualizerRenderLogic.h"

#include "../../../lib/imgui/imgui.h"
#include "../renderengine/utils/IOUtils.h"

void BVHVisualizerRenderLogic::init() {
    if (m_startupParameters.size() != 1) {
        std::cout << "[Warning] No input path to the BVH csv file as program argument provided. Using the example file instead. Otherwise use: ./BVHVisualizer <pathToBVH.csv>" << std::endl;
    }
    m_startupParameters.emplace_back("../resources/bvhexample/lbvh.csv");

    m_renderer.init(m_startupParameters[0]);
}

void BVHVisualizerRenderLogic::update(float time, KeyboardInput *keyboardInput, MouseInput *mouseInput) {
    static const float CAMERA_POS_STEP = 3.f;
    static const float MOUSE_SENSITIVITY = 0.25f;

    float factor = 1.0f;
    if (keyboardInput->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        factor = 25.f;
    }

    glm::vec3 cameraInc(0.f);
    if (keyboardInput->isKeyPressed(GLFW_KEY_W)) {
        cameraInc.z -= factor;
    }
    if (keyboardInput->isKeyPressed(GLFW_KEY_S)) {
        cameraInc.z += factor;
    }
    if (keyboardInput->isKeyPressed(GLFW_KEY_A)) {
        cameraInc.x -= factor;
    }
    if (keyboardInput->isKeyPressed(GLFW_KEY_D)) {
        cameraInc.x += factor;
    }
    if (keyboardInput->isKeyPressed(GLFW_KEY_LEFT_SHIFT) || keyboardInput->isKeyPressed(GLFW_KEY_Q)) {
        cameraInc.y -= factor;
    }
    if (keyboardInput->isKeyPressed(GLFW_KEY_SPACE) || keyboardInput->isKeyPressed(GLFW_KEY_E)) {
        cameraInc.y += factor;
    }

    m_camera.moveCenter(cameraInc.x * CAMERA_POS_STEP * time, cameraInc.y * CAMERA_POS_STEP * time,
                        cameraInc.z * CAMERA_POS_STEP * time);

    if (mouseInput->isRightButtonPressed()) {
        glm::vec2 motion = mouseInput->getMotion();
        m_camera.move(0.0f, motion.y * MOUSE_SENSITIVITY * time, -motion.x * MOUSE_SENSITIVITY * time);
    }
    if (mouseInput->getScroll(false).y != 0) {
        m_camera.move(-mouseInput->getScroll(true).y, 0.f, 0.f);
    }
}

void BVHVisualizerRenderLogic::render() {
    m_renderer.render(&m_camera, windowSize.x, windowSize.y);
}

void BVHVisualizerRenderLogic::renderGui() {
    ImGui::Begin("BVHVisualizer");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);

    ImGui::Spacing();

    ImGui::Text("Cell (X,Y,Z) = (%i,%i,%i)", static_cast<int>(glm::floor(m_camera.getPosition().x)),
                static_cast<int>(glm::floor(m_camera.getPosition().y)),
                static_cast<int>(glm::floor(m_camera.getPosition().z)));
    ImGui::Text("Position (X,Y,Z) = (%.3f,%.3f,%.3f)", m_camera.getPosition().x, m_camera.getPosition().y,
                m_camera.getPosition().z);
    ImGui::Text("Rotation (R,Phi,Theta) = (%.3f,%.3f,%.3f)", m_camera.getR(), m_camera.getPhi(),
                m_camera.getTheta());

    ImGui::Spacing();

    if (ImGui::Checkbox("BVH Color Leaf", &m_renderer.m_leafGreen)) {
        m_renderer.updateBVHVisualization();
    }
    if (ImGui::InputInt("BVH Min Depth", &m_renderer.m_bvhVisualizationMinLevel)) {
        m_renderer.updateBVHVisualization();
    }
    if (ImGui::InputInt("BVH Max Depth", &m_renderer.m_bvhVisualizationMaxLevel)) {
        m_renderer.updateBVHVisualization();
    }

    ImGui::Spacing();

    if (ImGui::Button("Screenshot")) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << "screenshot_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".png";
        IOUtils::writeFramebufferToFile(oss.str(), windowSize.x, windowSize.y);
    }


    ImGui::End();
}

void BVHVisualizerRenderLogic::cleanUp() {
    m_renderer.cleanUp();
}

void BVHVisualizerRenderLogic::onWindowResized(int width, int height) {
    windowSize = glm::vec2(width, height);
}

bool BVHVisualizerRenderLogic::generateSceneScreenshot(int number, IRenderLogic::SceneScreenshotInfo *info) {
    return false;
}