#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <core/window.h>

namespace World
{

enum class Direction
{
    FORWARD,
    BACK,
    RIGHT,
    LEFT
};

class Camera
{
public:
    Camera(glm::vec3 from, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    float GetZoom();
    glm::vec3 GetPosition();

    void ProcessKeyboard(Direction direction);
    void ProcessScroll(bool mouseWheelUp, bool mouseWheelDown);
    void ProcessMouse(float xOffset, float yOffset);

    float GetFov();
    void SetFov(float fov);

    float GetNear();
    void SetNear(float near);

    float GetFar();
    void SetFar(float far);
private:
    void UpdateCameraVectors();

private:
    glm::vec3 right, up, forward;
    glm::vec3 from, to;
    glm::vec3 _up;
    float zoom;
    float yaw, pitch;
    float speed, sensitivity;
    float fov, width, height, near, far;
};
};
