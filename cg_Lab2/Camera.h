#ifndef CAMERA_H
#define	CAMERA_H
#include <glm/glm.hpp>

#include "pipeline.h"
#include "math_3d.h"

class Camera
{
public:

    Camera(int WindowWidth, int WindowHeight);
    Camera(int WindowWidth, int WindowHeight, const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up);

    bool OnKeyboard(int Key);
    void OnMouse(int x, int y);
    void OnRender();

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

    void Init();
    void Update();

    int windowWidth;
    int windowHeight;

    float AngleH;
    float AngleV;

    bool OnUpperEdge;
    bool OnLowerEdge;
    bool OnLeftEdge;
    bool OnRightEdge;

    glm::vec2 mousePos;
};

#endif