#ifndef PIPELINE_H
#define	PIPELINE_H

#include "math_3d.h"

class Pipeline {
public:
    Pipeline()
    {
        mScale = Vector3f(1.0f, 1.0f, 1.0f);
        mWorldPos = Vector3f(0.0f, 0.0f, 0.0f);
        mRotateInfo = Vector3f(0.0f, 0.0f, 0.0f);
    }
    void Scale(float ScaleX, float ScaleY, float ScaleZ)
    {
        mScale.x = ScaleX;
        mScale.y = ScaleY;
        mScale.z = ScaleZ;
    }
    void WorldPos(float x, float y, float z)
    {
        mWorldPos.x = x;
        mWorldPos.y = y;
        mWorldPos.z = z;
    }
    void Rotate(float RotateX, float RotateY, float RotateZ)
    {
        mRotateInfo.x = RotateX;
        mRotateInfo.y = RotateY;
        mRotateInfo.z = RotateZ;
    }
    void SetPerspectiveProj(const PersProjInfo& p)
    {
        persProjInfo = p;
    }

    const Matrix4f& GetWVPTrans();
    const Matrix4f& GetWorldTrans();


    void SetCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }
private:
    Vector3f mScale;
    Vector3f mWorldPos;
    Vector3f mRotateInfo;
    Matrix4f m_WVPtransformation;
    Matrix4f m_WorldTransformation;

    PersProjInfo persProjInfo;

    struct {
        Vector3f Pos;
        Vector3f Target;
        Vector3f Up;
    } m_camera;
};

#endif