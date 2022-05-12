#ifndef CAMERA_H
#define	CAMERA_H
#include <glm/glm.hpp>

#include "pipeline.h"


class Camera
{
public:

    Camera();

    Camera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up);

    bool OnKeyboard(int Key);

    const glm::vec3& GetPos() const
    {
        return pos;
    }

    const glm::vec3& GetTarget() const
    {
        return target;
    }

    const glm::vec3& GetUp() const
    {
        return up;
    }

private:

    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
};

#endif