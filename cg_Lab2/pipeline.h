#ifndef CG_LAB1_PIPELINE_H
#define CG_LAB1_PIPELINE_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <glm/detail/type_mat4x4.hpp>

#define ToRadian(x) ((x) * M_PI / 180.0f)

class Pipeline {
public:
    glm::mat4 m;
    Pipeline() :
        mScale(glm::vec3(1.0f, 1.0f, 1.0f)),
        mWorldPos(glm::vec3(0.0f, 0.0f, 0.0f)),
        mRotateInfo(glm::vec3(0.0f, 0.0f, 0.0f)),
        mPersProj(),
        mTransformation(glm::mat4()) {}
    void Scale(float ScaleX, float ScaleY, float ScaleZ)
    {
        mScale[0] = ScaleX;
        mScale[1] = ScaleY;
        mScale[2] = ScaleZ;
    }
    void WorldPos(float x, float y, float z)
    {
        mWorldPos[0] = x;
        mWorldPos[1] = y;
        mWorldPos[2] = z;
    }
    void Rotate(float RotateX, float RotateY, float RotateZ)
    {
        mRotateInfo[0] = RotateX;
        mRotateInfo[1] = RotateY;
        mRotateInfo[2] = RotateZ;
    }
    void PerspectiveProj(float FOV, float width, float height, float zNear, float zFar) {
        mPersProj.FOV = FOV;
        mPersProj.width = width;
        mPersProj.height = height;
        mPersProj.zNear = zNear;
        mPersProj.zFar = zFar;
    }
    const glm::mat4* getTransformation();

    glm::vec3 Cross(glm::vec3& v1, glm::vec3& v2) {
        float _x = v1.y * v2.z - v1.z * v2.y;
        float _y = v1.z * v2.x - v1.x * v2.z;
        float _z = v1.x * v2.y - v1.y * v2.x;

        return glm::vec3(_x, _y, _z);
    }


    void SetCamera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }

    /**/void Normalize(glm::vec3& v) {
        float Length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (Length != 0) {
            v.x /= Length;
            v.y /= Length;
            v.z /= Length;
        }
    }

private:
    void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
    void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
    void InitTranslationTransform(float x, float y, float z);
    void InitPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar);
    void InitCameraTransform(glm::vec3& Target, glm::vec3& Up);

    glm::vec3 mScale;
    glm::vec3 mWorldPos;
    glm::vec3 mRotateInfo;
    glm::mat4 mTransformation;

    struct {
        float FOV;
        float width;
        float height;
        float zNear;
        float zFar;
    } mPersProj;

    struct {
        glm::vec3 Pos;
        glm::vec3 Target;
        glm::vec3 Up;
    } m_camera;
};


#endif