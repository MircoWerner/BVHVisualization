#pragma once

#include <GL/glew.h>

#include "../renderengine/camera/ACamera.h"
#include "../renderengine/shader/ShaderProgram.h"

#include "BVH.h"

/**
 * Renders the visualization.
 *
 * @author Mirco Werner
 */
class BVHVisualizerRenderer {
public:
    void init(const std::string &path);

    void render(ACamera *camera, int windowWidth, int windowHeight);

    void cleanUp();

    void updateBVHVisualization();

    int m_bvhVisualizationMinLevel = 0;
    int m_bvhVisualizationMaxLevel = 32;
    bool m_leafGreen = true;

    glm::vec3 m_position{0};
    glm::vec3 m_rotation{0};
    glm::vec3 m_scale{1};

private:
    BVH m_bvh;

    GLuint m_vaoId = 0;
    GLuint m_vertexVboId = 0;
    GLuint m_colorVboId = 0;
    GLuint m_indicesVboId = 0;

    GLsizei m_count = 0;

    ShaderProgram m_shaderProgram;
};