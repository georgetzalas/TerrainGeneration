#pragma once

#include <glm/glm.hpp>
#include <world/camera.h>

namespace Gfx{
    class Frustum
    {
    public:
        Frustum(const World::Camera& camera);
        Frustum();
        ~Frustum();
        
        void SetCamera(const World::Camera& camera);
        bool IsAABBVisible(const glm::vec3& min, const glm::vec3& max);
    
    private:
        void GenerateFrustumPlanes();

    private:
        World::Camera camera;
        glm::vec4 frustumPlanes[6];
    };
};