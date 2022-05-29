#ifndef SKYBOX_TECHNIQUE_H
#define	SKYBOX_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"


class SkyboxTechnique : public Technique {
public:

    SkyboxTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);

    virtual ~SkyboxTechnique();

private:

    GLuint m_WVPLocation;
    GLuint m_textureLocation;
};


#endif