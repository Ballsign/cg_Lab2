#include "pipeline.h"


#define ToRadian(x) ((x) * M_PI / 180.0f)

void Pipeline::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
    m[0][0] = ScaleX;    m[0][1] = 0.0f;      m[0][2] = 0.0f;      m[0][3] = 0.0f;
    m[1][0] = 0.0f;      m[1][1] = ScaleY;    m[1][2] = 0.0f;      m[1][3] = 0.0f;
    m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = ScaleZ;    m[2][3] = 0.0f;
    m[3][0] = 0.0f;      m[3][1] = 0.0f;      m[3][2] = 0.0f;      m[3][3] = 1.0f;
}

void Pipeline::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
{
    glm::mat4 rx, ry, rz;

    const float x = ToRadian(RotateX);
    const float y = ToRadian(RotateY);
    const float z = ToRadian(RotateZ);

    rx[0][0] = 1.0f;        rx[0][1] = 0.0f;       rx[0][2] = 0.0f;        rx[0][3] = 0.0f;
    rx[1][0] = 0.0f;        rx[1][1] = cosf(x);    rx[1][2] = -sinf(x);    rx[1][3] = 0.0f;
    rx[2][0] = 0.0f;        rx[2][1] = sinf(x);    rx[2][2] = cosf(x);     rx[2][3] = 0.0f;
    rx[3][0] = 0.0f;        rx[3][1] = 0.0f;       rx[3][2] = 0.0f;        rx[3][3] = 1.0f;

    ry[0][0] = cosf(y);     ry[0][1] = 0.0f;       ry[0][2] = -sinf(y);    ry[0][3] = 0.0f;
    ry[1][0] = 0.0f;        ry[1][1] = 1.0f;       ry[1][2] = 0.0f;        ry[1][3] = 0.0f;
    ry[2][0] = sinf(y);     ry[2][1] = 0.0f;       ry[2][2] = cosf(y);     ry[2][3] = 0.0f;
    ry[3][0] = 0.0f;        ry[3][1] = 0.0f;       ry[3][2] = 0.0f;        ry[3][3] = 1.0f;

    rz[0][0] = cosf(z);     rz[0][1] = -sinf(z);   rz[0][2] = 0.0f;        rz[0][3] = 0.0f;
    rz[1][0] = sinf(z);     rz[1][1] = cosf(z);    rz[1][2] = 0.0f;        rz[1][3] = 0.0f;
    rz[2][0] = 0.0f;        rz[2][1] = 0.0f;       rz[2][2] = 1.0f;        rz[2][3] = 0.0f;
    rz[3][0] = 0.0f;        rz[3][1] = 0.0f;       rz[3][2] = 0.0f;        rz[3][3] = 1.0f;

    m = rz * ry * rx;
}

void Pipeline::InitTranslationTransform(float x, float y, float z)
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Pipeline::InitPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar) {
    const float ar = Width / Height;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));

    m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;              m[0][2] = 0.0f;                     m[0][3] = 0.0;
    m[1][0] = 0.0f;                     m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;                     m[1][3] = 0.0;
    m[2][0] = 0.0f;                     m[2][1] = 0.0f;              m[2][2] = (-zNear - zFar) / zRange; m[2][3] = 2.0f * zFar * zNear / zRange;
    m[3][0] = 0.0f;                     m[3][1] = 0.0f;              m[3][2] = 1.0f;                     m[3][3] = 0.0;
}

void Pipeline::InitCameraTransform(const glm::vec3& Target, const glm::vec3& Up)
{
    Pipeline N;
    N.m_camera.Target = Target;
    N.Normalize();
    Pipeline U;
    U.m_camera.Up = Up;
    U.Normalize();
    U.m_camera.Up = U.Cross(Target);
    Pipeline V;
    V.m_camera.Pos = N.Cross(U.m_camera.Up);

    m[0][0] = U.m_camera.Up[0]; m[0][1] = U.m_camera.Up[1]; m[0][2] = U.m_camera.Up[2]; m[0][3] = 0.0f;
    m[1][0] = V.m_camera.Pos[0]; m[1][1] = V.m_camera.Pos[1]; m[1][2] = V.m_camera.Pos[2]; m[1][3] = 0.0f;
    m[2][0] = N.m_camera.Target[0]; m[2][1] = N.m_camera.Target[1]; m[2][2] = N.m_camera.Target[2]; m[2][3] = 0.0f;
    m[3][0] = 0.0f;             m[3][1] = 0.0f;             m[3][2] = 0.0f;             m[3][3] = 1.0f;
}

const glm::mat4* Pipeline::getTransformation()
{
    //glm::mat4 scaleTrans, rotateTrans, translationTrans, persProjTrans;

    //InitScaleTransform(scaleTrans);
    //InitRotateTransform(rotateTrans);
    //InitTranslationTransform(translationTrans);
    //InitPerspectiveProj(persProjTrans);

    //mTransformation = persProjTrans * translationTrans * rotateTrans * scaleTrans/* * persProjTrans*/;
    //return &mTransformation;

    Pipeline ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    ScaleTrans.InitScaleTransform(mScale[0], mScale[1], mScale[2]);
    RotateTrans.InitRotateTransform(mRotateInfo[0], mRotateInfo[1], mRotateInfo[2]);
    TranslationTrans.InitTranslationTransform(mWorldPos[0], mWorldPos[1], mWorldPos[2]);
    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPerspectiveProj(mPersProj.FOV, mPersProj.width, mPersProj.height, mPersProj.zNear, mPersProj.zFar);

    mTransformation = PersProjTrans.m * CameraRotateTrans.m * CameraTranslationTrans.m * TranslationTrans.m * RotateTrans.m * ScaleTrans.m;
    return &mTransformation;
}