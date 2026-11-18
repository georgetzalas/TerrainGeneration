#include <gfx/frustum.h>

Gfx::Frustum::Frustum(const World::Camera& camera)
{
    this->camera = camera;
    GenerateFrustumPlanes();
}

Gfx::Frustum::Frustum()
{

}

Gfx::Frustum::~Frustum()
{

}

void Gfx::Frustum::SetCamera(const World::Camera& camera)
{
    this->camera = camera;
    GenerateFrustumPlanes();
}

bool Gfx::Frustum::IsAABBVisible(const glm::vec3& min, const glm::vec3& max)
{
    for (size_t i=0; i<6; i++) {
        const glm::vec4& g = frustumPlanes[i];
        if ((glm::dot(g, glm::vec4(min.x, min.y, min.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(max.x, min.y, min.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(min.x, max.y, min.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(max.x, max.y, min.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(min.x, min.y, max.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(max.x, min.y, max.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(min.x, max.y, max.z, 1.0f)) < 0.0) &&
            (glm::dot(g, glm::vec4(max.x, max.y, max.z, 1.0f)) < 0.0))
        {
            // Not visible - all returned negative
            return false;
        }
    }
    return true;
}

void Gfx::Frustum::GenerateFrustumPlanes()
{
    const glm::mat4 vp  = camera.GetProjectionMatrix() * camera.GetViewMatrix();
    const glm::mat4 vpt = glm::transpose(vp);

    //left
    frustumPlanes[0] = vpt[3] + vpt[0];
    //right
    frustumPlanes[1] = vpt[3] - vpt[0];
    //bottom
    frustumPlanes[2] = vpt[3] + vpt[1];
    //top
    frustumPlanes[3] = vpt[3] - vpt[0];
    //near
    frustumPlanes[4] = vpt[3] + vpt[2];
    //far
    frustumPlanes[5] = vpt[3] - vpt[2];
}