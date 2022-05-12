#include <GL/freeglut.h>
#include "Camera.h"

const static float StepScale = 0.1f;

Camera::Camera()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    target = glm::vec3(0.0f, 0.0f, 1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}


Camera::Camera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
{
    pos = Pos;
    target = Target;
    Pipeline::Normalize(target);
    up = Up;
    Pipeline::Normalize(up);
}


bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
    {
        pos += (target * StepScale);
        Ret = true;
    }
    break;

    case GLUT_KEY_DOWN:
    {
        pos -= (target * StepScale);
        Ret = true;
    }
    break;

    case GLUT_KEY_LEFT:
    {
        glm::vec3 Left = Pipeline::Cross(target, up);
        Pipeline::Normalize(Left);
        Left *= StepScale;
        pos += Left;
        Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT:
    {
        glm::vec3 Right = Pipeline::Cross(up, target);
        Pipeline::Normalize(Right);
        Right *= StepScale;
        pos += Right;
        Ret = true;
    }
    break;
    }

    return Ret;
}