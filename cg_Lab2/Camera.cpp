#include <GL/freeglut.h>
#include "Camera.h"
#include "pipeline.h"

const static float StepScale = 1.0f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)
{
    windowWidth = WindowWidth;
    windowHeight = WindowHeight;
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    target = glm::vec3(0.0f, 0.0f, 1.0f);
    Pipeline::Normalize(target);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    Init();
}


Camera::Camera(int WindowWidth, int WindowHeight, const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
{
    windowWidth = WindowWidth;
    windowHeight = WindowHeight;

    pos = Pos;
    target = Target;
    Pipeline::Normalize(target);
    up = Up;
    Pipeline::Normalize(up);

    Init();
}

void Camera::Init()
{
    glm::vec3 HTarget(target.x, 0.0, target.z);
    Pipeline::Normalize(HTarget);

    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            AngleH = 360.0f - ToDegree(asin(HTarget.z));
        }
        else
        {
            AngleH = 180.0f + ToDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            AngleH = ToDegree(asin(-HTarget.z));
        }
        else
        {
            AngleH = 90.0f + ToDegree(asin(-HTarget.z));
        }
    }

    AngleV = -ToDegree(asin(target.y));

    OnUpperEdge = false;
    OnLowerEdge = false;
    OnLeftEdge = false;
    OnRightEdge = false;
    mousePos.x = windowWidth / 2;
    mousePos.y = windowHeight / 2;

    glutWarpPointer(mousePos.x, mousePos.y);
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

void Camera::OnMouse(int x, int y)
{
    int DeltaX = (x - mousePos.x);
    int DeltaY = (y - mousePos.y);

    mousePos.x = x;
    mousePos.y = y;

    AngleH += (float)DeltaX / 20.0f;
    AngleV += (float)DeltaY / 20.0f;

    if (DeltaX == 0) {
        if (x <= MARGIN) {
            OnLeftEdge = true;
        }
        else if (x >= (windowWidth - MARGIN)) {
            OnRightEdge = true;
        }
    }
    else {
        OnLeftEdge = false;
        OnRightEdge = false;
    }

    if (DeltaY == 0) {
        if (y <= MARGIN) {
            OnUpperEdge = true;
        }
        else if (y >= (windowHeight - MARGIN)) {
            OnLowerEdge = true;
        }
    }
    else {
        OnUpperEdge = false;
        OnLowerEdge = false;
    }

    Update();
}

void Camera::OnRender()
{
    bool ShouldUpdate = false;

    if (OnLeftEdge) {
        AngleH -= 0.1f;
        ShouldUpdate = true;
    }
    else if (OnRightEdge) {
        AngleH += 0.1f;
        ShouldUpdate = true;
    }

    if (OnUpperEdge) {
        if (AngleV > -90.0f) {
            AngleV -= 0.1f;
            ShouldUpdate = true;
        }
    }
    else if (OnLowerEdge) {
        if (AngleV < 90.0f) {
            AngleV += 0.1f;
            ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        Update();
    }
}

void Camera::Update()
{
    glm::vec3 Vaxis(0.0f, 1.0f, 0.0f);

    Pipeline View;
    View.v = glm::vec3(1.0f, 0.0f, 0.0f);
    View.Rotate(AngleH, Vaxis);
    View.Normalize();

    glm::vec3 Haxis = Pipeline::Cross(Vaxis, View.v);
    Pipeline::Normalize(Haxis);
    View.Rotate(AngleV, Haxis);

    target = View.v;
    Pipeline::Normalize(target);

    up = Pipeline::Cross(target, Haxis);
    Pipeline::Normalize(up);
}
