#pragma once
#include "gameobject.h"             // Include base class
/*#include <glm/gtx/transform.hpp> */   // glm transform functions.

class Camera : public GameObject {
public:
    Camera(float left, float right, float bottom, float top)
        : GameObject(__FUNCTION__) {
        m_projection = glm::ortho(left, right, bottom, top);
    }

    ~Camera() {

    }

    const glm::mat4& getProjectionMatrix() const {
        return  m_projection;
    }

private:
    glm::mat4  m_projection;
};
