#include "BVHVisualizationRenderer.h"

#include <random>

#include "../../renderengine/utils/Transformation.h"

void BVHVisualizationRenderer::init(const std::string &path) {
    m_bvh.fromCSV(path);

    updateBVHVisualization();
}

void BVHVisualizationRenderer::render(ACamera *camera, int windowWidth, int windowHeight) {
    glm::mat4 modelMatrix = Transformation::getModelMatrix(m_position, m_rotation, m_scale);

    static const float FOV = glm::radians(90.0f);
    static const float Z_NEAR = 0.01f;
    static const float Z_FAR = 1000.f;
    glm::mat4 projectionMatrix = Transformation::getProjectionMatrix(FOV, static_cast<float>(windowWidth), static_cast<float>(windowHeight), Z_NEAR, Z_FAR);
    glm::mat4 viewMatrix = Transformation::getViewMatrix(camera);
    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    m_shaderProgram.bind();

    m_shaderProgram.setUniform("MVP", MVP);

    glBindVertexArray(m_vaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_LINES, m_count, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    ShaderProgram::unbind();
}

void BVHVisualizationRenderer::cleanUp() {
    glDeleteBuffers(1, &m_vertexVboId);
    glDeleteBuffers(1, &m_indicesVboId);
    glDeleteVertexArrays(1, &m_vaoId);
    m_shaderProgram.cleanUp();
}

void BVHVisualizationRenderer::updateBVHVisualization() {
    cleanUp();

    m_shaderProgram.init();
    m_shaderProgram.createVertexShader("../resources/shaders/bvh_visualization_vertex.glsl");
    m_shaderProgram.createFragmentShader("../resources/shaders/bvh_visualization_fragment.glsl");
    m_shaderProgram.link();
    m_shaderProgram.createUniform("MVP");
    ShaderProgram::unbind();

    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<int> indices;

    m_bvh.traverseBVH(&vertices, &colors, &indices, 0, 0, m_bvhVisualizationMinLevel, m_bvhVisualizationMaxLevel, m_leafGreen);

    m_count = indices.size();

    glGenVertexArrays(1, &m_vaoId);
    glBindVertexArray(m_vaoId);

    glGenBuffers(1, &m_vertexVboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVboId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &m_colorVboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVboId);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &m_indicesVboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesVboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}
