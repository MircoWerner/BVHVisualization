#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "AABB.h"

/**
 * BVH and traversal.
 *
 * @author Mirco Werner
 */
class BVH {
public:
    struct BVHNode {
        int32_t left = -1;
        int32_t right = -1;
        uint32_t primitiveIdx = 0;
        AABB aabb;
    };

    void fromCSV(const std::string &path);

    std::vector<BVHNode> m_bvh;

    void
    traverseBVH(std::vector<float> *vertices, std::vector<float> *colors, std::vector<int> *indices, int bvhNodeIdx,
                int level, int minLevel, int maxLevel, bool colorLeafs);

    static void
    buildCube(std::vector<float> *vertices, std::vector<float> *colors, std::vector<int> *indices, glm::vec3 min,
              glm::vec3 max, glm::vec3 color);
};