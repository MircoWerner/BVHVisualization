#include "BVH.h"

#include <iostream>
#include <fstream>
#include <sstream>

void BVH::fromCSV(const std::string &path) {
    std::ifstream csv(path);
    if (!csv.is_open()) {
        throw std::runtime_error("Unable to open csv file.");
    }

    csv.ignore(LLONG_MAX, '\n'); // skip first line

    std::string line;
    while (std::getline(csv, line)) {
        std::istringstream iss(line);

        BVHNode node{};

        std::string field;
        if (std::getline(iss, field, ' ')) {
            node.left = static_cast<int32_t>(std::stoll(field));
        }
        if (std::getline(iss, field, ' ')) {
            node.right = static_cast<int32_t>(std::stoll(field));
        }
        if (std::getline(iss, field, ' ')) {
            node.primitiveIdx = static_cast<uint32_t>(std::stoll(field));
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.min.x = std::stof(field);
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.min.y = std::stof(field);
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.min.z = std::stof(field);
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.max.x = std::stof(field);
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.max.y = std::stof(field);
        }
        if (std::getline(iss, field, ' ')) {
            node.aabb.max.z = std::stof(field);
        }
        m_bvh.push_back(node);
    }

    csv.close();
}

void
BVH::traverseBVH(std::vector<float> *vertices, std::vector<float> *colors, std::vector<int> *indices, int bvhNodeIdx,
                 int level, int minLevel, int maxLevel, bool colorLeafs) {
    if (level > maxLevel) {
        return;
    }

    if (level >= minLevel) {
        glm::vec3 min = m_bvh[bvhNodeIdx].aabb.min;
        glm::vec3 max = m_bvh[bvhNodeIdx].aabb.max;

        glm::vec3 color(1);
        if (m_bvh[bvhNodeIdx].left == 0 && colorLeafs) {
            color = glm::vec3(0, 1, 0);
        }
        buildCube(vertices, colors, indices, min, max, color);
    }

    if (m_bvh[bvhNodeIdx].left == 0) {
        return;
    }

    traverseBVH(vertices, colors, indices, m_bvh[bvhNodeIdx].left, level + 1, minLevel, maxLevel, colorLeafs);
    traverseBVH(vertices, colors, indices, m_bvh[bvhNodeIdx].right, level + 1, minLevel, maxLevel, colorLeafs);
}

void BVH::buildCube(std::vector<float> *vertices, std::vector<float> *colors, std::vector<int> *indices, glm::vec3 min,
                    glm::vec3 max, glm::vec3 color) {
    const uint8_t FOUR = 0x4;
    const uint8_t TWO = 0x2;
    const uint8_t ONE = 0x1;

    for (uint8_t cornerIdx = 0; cornerIdx < 8; cornerIdx++) {
        float x = (cornerIdx & FOUR) == FOUR ? max.x : min.x;
        float y = (cornerIdx & TWO) == TWO ? max.y : min.y;
        float z = (cornerIdx & ONE) == ONE ? max.z : min.z;

        vertices->push_back(static_cast<float>(x));
        vertices->push_back(static_cast<float>(y));
        vertices->push_back(static_cast<float>(z));

        colors->push_back(color.r);
        colors->push_back(color.g);
        colors->push_back(color.b);
    }

    int indexOffset = static_cast<int>(vertices->size()) / 3 - 8;

    indices->push_back(0 + indexOffset);
    indices->push_back(1 + indexOffset);

    indices->push_back(0 + indexOffset);
    indices->push_back(2 + indexOffset);

    indices->push_back(0 + indexOffset);
    indices->push_back(4 + indexOffset);

    indices->push_back(1 + indexOffset);
    indices->push_back(3 + indexOffset);

    indices->push_back(2 + indexOffset);
    indices->push_back(3 + indexOffset);

    indices->push_back(2 + indexOffset);
    indices->push_back(6 + indexOffset);

    indices->push_back(4 + indexOffset);
    indices->push_back(6 + indexOffset);

    indices->push_back(4 + indexOffset);
    indices->push_back(5 + indexOffset);

    indices->push_back(1 + indexOffset);
    indices->push_back(5 + indexOffset);

    indices->push_back(3 + indexOffset);
    indices->push_back(7 + indexOffset);

    indices->push_back(5 + indexOffset);
    indices->push_back(7 + indexOffset);

    indices->push_back(6 + indexOffset);
    indices->push_back(7 + indexOffset);
}
