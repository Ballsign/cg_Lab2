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

    glm::vec3 Cross(const glm::vec3& v) const
    {
        glm::vec3 tmp;
        tmp[0] = mWorldPos[1] * v[2] - mWorldPos[2] * v[1];
        tmp[1] = mWorldPos[2] * v[0] - mWorldPos[0] * v[2];
        tmp[2] = mWorldPos[0] * v[1] - mWorldPos[1] * v[0];
        
        return tmp;
    }///

    void SetCamera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }

    glm::vec3& Normalize() {
        const float Length = sqrtf(mWorldPos[0] * mWorldPos[0] + mWorldPos[1] * mWorldPos[1] + mWorldPos[2] * mWorldPos[2]);

        mWorldPos[0] /= Length;
        mWorldPos[1] /= Length;
        mWorldPos[2] /= Length;

        return mWorldPos;
    }///

private:
    void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
    void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
    void InitTranslationTransform(float x, float y, float z);
    void InitPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar);
    void InitCameraTransform(const glm::vec3& Target, const glm::vec3& Up);

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