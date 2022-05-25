#include <GL/freeglut.h>
#include "Camera.h"

const static float STEP_SCALE = 1.0f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)
{
    windowWidth = WindowWidth;
    windowHeight = WindowHeight;
    pos = Vector3f(0.0f, 0.0f, 0.0f);
    target = Vector3f(0.0f, 0.0f, 1.0f);
    target.Normalize();
    up = Vector3f(0.0f, 1.0f, 0.0f);

    Init();
}

//Конструктор камеры теперь принимает размеры окна.(для перемещения курсора в центр экрана)
Camera::Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    windowWidth = WindowWidth;
    windowHeight = WindowHeight;
    pos = Pos;

    target = Target;
    target.Normalize();

    up = Up;
    up.Normalize();

    Init(); //установит внутренние параметры камеры
}


void Camera::Init()
{
    Vector3f HTarget(target.x, 0.0, target.z);//HTarget (направление по горизонтали)
    HTarget.Normalize(); //нормируем
    //вычисления горизонтального угла
    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            AngleH = 360.0f - ToDegree(asin(HTarget.z));
        }
        else
        {
            AngleH = 180.0f + ToDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            AngleH = ToDegree(asin(-HTarget.z));
        }
        else
        {
            AngleH = 90.0f + ToDegree(asin(-HTarget.z));
        }
    }
    //подсчитываем вертикальный угол
    AngleV = -ToDegree(asin(target.y));
    //4 новых параметра для проверки не касается ли курсор границ экрана
    OnUpperEdge = false;
    OnLowerEdge = false;
    OnLeftEdge = false;
    OnRightEdge = false;
    //Следующие 2 строки кода вычисляют центр экрана
    mousePos.x = windowWidth / 2;
    mousePos.y = windowHeight / 2;
    //перемещает курсор
    glutWarpPointer(mousePos.x, mousePos.y);
}


bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
    {
        pos += (target * STEP_SCALE);
        Ret = true;
    }
    break;

    case GLUT_KEY_DOWN:
    {
        pos -= (target * STEP_SCALE);
        Ret = true;
    }
    break;

    case GLUT_KEY_LEFT:
    {
        Vector3f Left = target.Cross(up);
        Left.Normalize();
        Left *= STEP_SCALE;
        pos += Left;
        Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT:
    {
        Vector3f Right = up.Cross(target);
        Right.Normalize();
        Right *= STEP_SCALE;
        pos += Right;
        Ret = true;
    }
    break;
    }

    return Ret;
}

//Эта функция используется что бы сообщить камере, что положение мыши изменилось.
void Camera::OnMouse(int x, int y)
{
    //подсчет разницы между новыми координатами и предыдущими по осям и X и Y.
    const int DeltaX = x - mousePos.x;
    const int DeltaY = y - mousePos.y;

    mousePos.x = x;
    mousePos.y = y;
    //обновляем текущие горизонтальные и вертикальные углы на эту разность в значениях.
    AngleH += (float)DeltaX / 20.0f;
    AngleV += (float)DeltaY / 20.0f;
    //обновляем значения 'm_OnEdge' согласно положению курсора
    if (DeltaX == 0) {
        if (x <= MARGIN) { //если у левой границы вращение влево
            //    m_AngleH -= 1.0f;
            OnLeftEdge = true;
        }
        else if (x >= (windowWidth - MARGIN)) { //у правой границы вращение вправо
            //    m_AngleH += 1.0f;
            OnRightEdge = true;
        }
    }
    else {
        OnLeftEdge = false;
        OnRightEdge = false;
    }

    if (DeltaY == 0) {
        if (y <= MARGIN) {
            OnUpperEdge = true;
        }
        else if (y >= (windowHeight - MARGIN)) {
            OnLowerEdge = true;
        }
    }
    else {
        OnUpperEdge = false;
        OnLowerEdge = false;
    }

    Update();//для перерасчета векторов направления и вектора вверх,
             //основанных на новых горизонтальном и вертикальном углах
}

//для случаев, когда мышь не движется, но находится около одной из границ экрана.
void Camera::OnRender()
{
    bool ShouldUpdate = false;
    //проверяем не установлен ли хоть один из флагов, 
    //и если таковой найден, то изменится один из углов.
    if (OnLeftEdge) {
        AngleH -= 0.1f;
        ShouldUpdate = true;
    }
    else if (OnRightEdge) {
        AngleH += 0.1f;
        ShouldUpdate = true;
    }

    if (OnUpperEdge) {
        if (AngleV > -90.0f) {
            AngleV -= 0.1f;
            ShouldUpdate = true;
        }
    }
    else if (OnLowerEdge) {
        if (AngleV < 90.0f) {
            AngleV += 0.1f;
            ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        Update(); //для обновления векторов камеры.
    }
}
//функция обновляет значения векторов направления и вверх согласно горизонтальному и вертикальному углам.
void Camera::Update()
{
    const Vector3f Vaxis(0.0f, 1.0f, 0.0f);//вектор параллелен земле

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(AngleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.Rotate(AngleV, Haxis);

    target = View;//меняется вектор направленмя
    target.Normalize();
    //меняется вектор вверх
    up = target.Cross(Haxis);
    up.Normalize();
}