#include "pipeline.h"

const Matrix4f* Pipeline::getTransformation()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    ScaleTrans.InitScaleTransform(mScale.x, mScale.y, mScale.z);
    RotateTrans.InitRotateTransform(mRotateInfo.x, mRotateInfo.y, mRotateInfo.z);
    TranslationTrans.InitTranslationTransform(mWorldPos.x, mWorldPos.y, mWorldPos.z);
    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPersProjTransform(mPersProj.FOV, mPersProj.width, mPersProj.height, mPersProj.zNear, mPersProj.zFar);

    mTransformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
    return &mTransformation;
}   
