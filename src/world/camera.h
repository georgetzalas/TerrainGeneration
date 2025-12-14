#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float SPEED = 0.5f;
constexpr float SENSITIVITY = 0.1f;

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
    glm::mat4 getViewMatrix();
    float getZoom();
    glm::vec3 getPosition();

    void processKeyboard(Direction direction);
    void processScroll(bool mouseWheelUp, bool mouseWheelDown);
    void processMouse(float xOffset, float yOffset);
private:
    void updateCameraVectors();

private:
    glm::vec3 right, up, forward;
    glm::vec3 from, to;
    glm::vec3 _up;
    float zoom;
    float yaw, pitch;
};
