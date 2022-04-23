#ifndef CG_LAB1_PIPELINE_H
#define CG_LAB1_PIPELINE_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <glm/detail/type_mat4x4.hpp>

#define ToRadian(x) ((x) * M_PI / 180.0f)

class Pipeline {
public:
    Pipeline() :
        mScale(glm::vec3(1.0f, 1.0f, 1.0f)),
        mWorldPos(glm::vec3(0.0f, 0.0f, 0.0f)),
        mRotateInfo(glm::vec3(0.0f, 0.0f, 0.0f)),
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
    const glm::mat4* getTransformation();

private:
    void InitScaleTransform(glm::mat4& m) const;
    void InitRotateTransform(glm::mat4& m) const;
    void InitTranslationTransform(glm::mat4& m) const;

    glm::vec3 mScale;
    glm::vec3 mWorldPos;
    glm::vec3 mRotateInfo;
    glm::mat4 mTransformation;
};


#endif