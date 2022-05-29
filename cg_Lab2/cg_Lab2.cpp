#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "util.h"
#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "lighting_technique.h"
#include "glut_backend.h"
#include "mesh.h"
#include "skybox.h"

#define WINDOW_WIDTH  1366
#define WINDOW_HEIGHT 768


class Main : public ICallbacks
{
public:

    Main()
    {
        m_pLightingTechnique = NULL;
        m_pGameCamera = NULL;
        m_pTankMesh = NULL;
        m_scale = 0.0f;
        m_pSkyBox = NULL;

        m_dirLight.AmbientIntensity = 0.2f;
        m_dirLight.DiffuseIntensity = 0.8f;
        m_dirLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_dirLight.Direction = Vector3f(1.0f, -1.0f, 0.0f);

        m_persProjInfo.FOV = 60.0f;
        m_persProjInfo.Height = WINDOW_HEIGHT;
        m_persProjInfo.Width = WINDOW_WIDTH;
        m_persProjInfo.zNear = 1.0f;
        m_persProjInfo.zFar = 100.0f;
    }


    virtual ~Main()
    {
        SAFE_DELETE(m_pLightingTechnique);
        SAFE_DELETE(m_pGameCamera);
        SAFE_DELETE(m_pTankMesh);
        SAFE_DELETE(m_pSkyBox);
    }


    bool Init()
    {
        Vector3f Pos(0.0f, 1.0f, -20.0f);
        Vector3f Target(0.0f, 0.0f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);

        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

        m_pLightingTechnique = new LightingTechnique();

        if (!m_pLightingTechnique->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pLightingTechnique->Enable();
        m_pLightingTechnique->SetDirectionalLight(m_dirLight);
        m_pLightingTechnique->SetTextureUnit(0);

        m_pTankMesh = new Mesh();

        if (!m_pTankMesh->LoadMesh("C:/Users/zypok/Desktop/Content/phoenix_ugv.md2")) {
            return false;
        }

        m_pSkyBox = new SkyBox(m_pGameCamera, m_persProjInfo);

        if (!m_pSkyBox->Init(".",
            "C:/Users/zypok/Desktop/Content/sp3right.jpg",
            "C:/Users/zypok/Desktop/Content/sp3left.jpg",
            "C:/Users/zypok/Desktop/Content/sp3top.jpg",
            "C:/Users/zypok/Desktop/Content/sp3bot.jpg",
            "C:/Users/zypok/Desktop/Content/sp3front.jpg",
            "C:/Users/zypok/Desktop/Content/sp3back.jpg")) {
            return false;
        }

        return true;
    }


    void Run()
    {
        GLUTBackendRun(this);
    }


    virtual void RenderSceneCB()
    {
        m_pGameCamera->OnRender();
        m_scale += 0.05f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_pLightingTechnique->Enable();

        Pipeline p;
        p.Scale(0.1f, 0.1f, 0.1f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.0f, -5.0f, 3.0f);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(m_persProjInfo);

        m_pLightingTechnique->SetWVP(p.GetWVPTrans());
        m_pLightingTechnique->SetWorldMatrix(p.GetWorldTrans());
        m_pTankMesh->Render();

        m_pSkyBox->Render();

        glutSwapBuffers();
    }


    virtual void IdleCB()
    {
        RenderSceneCB();
    }


    virtual void SpecialKeyboardCB(int Key, int x, int y)
    {
        m_pGameCamera->OnKeyboard(Key);
    }


    virtual void KeyboardCB(unsigned char Key, int x, int y)
    {
        switch (Key) {
        case 'q':
            glutLeaveMainLoop();
            break;
        }
    }


    virtual void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(x, y);
    }

private:

    LightingTechnique* m_pLightingTechnique;
    Camera* m_pGameCamera;
    float m_scale;
    DirectionalLight m_dirLight;
    Mesh* m_pTankMesh;
    SkyBox* m_pSkyBox;
    PersProjInfo m_persProjInfo;
};


int main(int argc, char** argv)
{
    GLUTBackendInit(argc, argv);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 32, false, "Kirill rulz ok")) {
        return 1;
    }

    Main* pApp = new Main();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;

    return 0;
}