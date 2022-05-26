#include "pipeline.h"

const Matrix4f& Pipeline::GetWorldTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.InitScaleTransform(mScale.x, mScale.y, mScale.z);
    RotateTrans.InitRotateTransform(mRotateInfo.x, mRotateInfo.y, mRotateInfo.z);
    TranslationTrans.InitTranslationTransform(mWorldPos.x, mWorldPos.y, mWorldPos.z);

    m_WorldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
    return m_WorldTransformation;
}

const Matrix4f& Pipeline::GetWVPTrans()
{
    GetWorldTrans();

    Matrix4f CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPersProjTransform(mPersProj.FOV, mPersProj.width, mPersProj.height, mPersProj.zNear, mPersProj.zFar);

    m_WVPtransformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * m_WorldTransformation;
    return m_WVPtransformation;
}