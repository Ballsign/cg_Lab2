Лабораторная работа №2 по дисциплине "Инженерная и компьютерная графика"
***
## 1) Перемещение
Создаём глобальную переменную gWorldLocation:
```c++
GLuint gWorldLocation;
```
 Добавляем код шейдера:
 ```c++
#version 330                                                                                               
layout (location = 0) in vec3 Position;
uniform mat4 gWorld;
void main() {
    gl_Position = gWorld * vec4(Position, 1.0); // Умножаем вектор вершин на всемирную матрицу для смещения треугольника
}
 ```
 В функцию отрисовки добавляем:
  ```c++
static float Scale = 0.0f; // Переменная для изменения значения X
Scale += 0.001f; // С каждой отрисовкой увеличиваем Scale

// Подготавливаем матрицу 4x4 для изменения координаты X на значение синуса Scale
glm::mat4 World;
World[0][0] = 1.0f; World[0][1] = 0.0f; World[0][2] = 0.0f; World[0][3] = sinf(Scale);
World[1][0] = 0.0f; World[1][1] = 1.0f; World[1][2] = 0.0f; World[1][3] = 0.0f;
World[2][0] = 0.0f; World[2][1] = 0.0f; World[2][2] = 1.0f; World[2][3] = 0.0f;
World[3][0] = 0.0f; World[3][1] = 0.0f; World[3][2] = 0.0f; World[3][3] = 1.0f;

// Загружаем данные в uniform-переменные шейдера (адрес переменной, количество матриц, передаётся ли матрица по строкам, указатель на первый элемент матрицы)
glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World[0][0]);
 ```
 Добавляем две новые функции:
  ```c++
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) // Функция, добавляющая шейдер к программе
{
  GLuint ShaderObj = glCreateShader(ShaderType);// Создаём шейдер

  if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

// Сохраняем код шейдера в массиве
const GLchar *p[1];
p[0] = pShaderText.c_str();

// Массив длин кодов шейдеров
GLint lengths[1];
lengths[0] = pShaderText.length();

glShaderSource(ShaderObj, 1, p, Lengths);// Задаём исходники шейдера
glCompileShader(ShaderObj);// Компилируем шейдер

// Проверяем, что шейдер успешно скомпилировался
GLint success;
glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

// Добавляем шейдер в программу
glAttachShader(ShaderProgram, ShaderObj);
}

// Функция, компилирующая программу-шейдер
static void CompileShaders()
{
GLuint ShaderProgram = glCreateProgram();// Создаём программу-шейдер
 if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

// Добавляем шейдер для вершин
AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);

GLint Success = 0;
GLchar ErrorLog[1024] = { 0 };
// Линкуем программу
glLinkProgram(ShaderProgram);
// Проверяем, что линковка прошла успешно
glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
if (Success == 0) {
glGetProgramInfoLog(ShaderProgram, sizeof(errorLog), nullptr, ErrorLog);
fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
exit(1);
}

// Валидируем программу
glValidateProgram(ShaderProgram);
// Проверяем, что валидация прошла успешно
glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
if (Success == 0) {
glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), nullptr, ErrorLog);
fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
exit(1);
}

// Указываем OpenGL, что надо использовать эту программу
glUseProgram(ShaderProgram);

// Сохраняем местоположение переменной gWorld
gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
assert(gWorldLocation != 0xFFFFFFFF);
}
   ```
## 2) Вращение вокруг оси OZ
В функции отрисовки меняем матрицу World:
```c++
 World[0][0] = cosf(Scale); World[0][1] = -sinf(Scale); World[0][2] = 0.0f; World[0][3] = 0.0f;
 World[1][0] = sinf(Scale); World[1][1] = cosf(Scale);  World[1][2] = 0.0f; World[1][3] = 0.0f;
 World[2][0] = 0.0f;        World[2][1] = 0.0f;         World[2][2] = 1.0f; World[2][3] = 0.0f;
 World[3][0] = 0.0f;        World[3][1] = 0.0f;         World[3][2] = 0.0f; World[3][3] = 1.0f;
```
## 3) Преобразования масштаба
По аналогии с прошлым пунктом меняем матрицу World:
```c++
World[0][0] = sinf(Scale); World[0][1] = 0.0f;          World[0][2] = 0.0f;          World[0][3] = 0.0f;
World[1][0] = 0.0f;        World[1][1] = cosf(Scale);   World[1][2] = 0.0f;          World[1][3] = 0.0f;
World[2][0] = 0.0f;        World[2][1] = 0.0f;          World[2][2] = sinf(Scale);   World[2][3] = 0.0f;
World[3][0] = 0.0f;        World[3][1] = 0.0f;          World[3][2] = 0.0f;          World[3][3] = 1.0f;
```
## 4) Объединение преобразований
Создадим класс с пайплайном преобразований:
```c++
class Pipeline {
public:
    // Конструктор для начальных значений
    Pipeline() : 
        mScale(glm::vec3(1.0f, 1.0f, 1.0f)),
        mWorldPos(glm::vec3(0.0f, 0.0f, 0.0f)),
        mRotateInfo(glm::vec3(0.0f, 0.0f, 0.0f)),
        mTransformation(glm::mat4()) {}

    // Функция задания изменения масштаба
    void Scale(float ScaleX, float ScaleY, float ScaleZ)
    {
        mScale[0] = ScaleX;
        mScale[1] = ScaleY;
        mScale[2] = ScaleZ;
    }

    // Функция задания изменения положения
    void WorldPos(float x, float y, float z)
    {
        mWorldPos[0] = x;
        mWorldPos[1] = y;
        mWorldPos[2] = z;
    }
    // Функция задания вращения
    void Rotate(float RotateX, float RotateY, float RotateZ)
    {
        mRotateInfo[0] = RotateX;
        mRotateInfo[1] = RotateY;
        mRotateInfo[2] = RotateZ;
    }

    // Функция получения итоговой матрицы
    const glm::mat4* getTransformation();

private:
    // Вспомогательные функции
    void InitScaleTransform(glm::mat4& m) const;
    void InitRotateTransform(glm::mat4& m) const;
    void InitTranslationTransform(glm::mat4& m) const;

    // Необходимые переменные
    glm::vec3 mScale;
    glm::vec3 mWorldPos;
    glm::vec3 mRotateInfo;
    glm::mat4 mTransformation;
};
```
В функции отрисовки вместо ручного задания матрицы World используем пайплайн:
```c++
    Pipeline p;// Создаём pipeline для трансформаций
    p.Scale(0.1f, 0.1f, 0.1f);// Меняем масштаб
    p.Rotate(0, Scale, 0);// Вращаем его по всем осям
    p.WorldPos(0.0f, 0.0f, 100.0f);// Двигаем треугольник по оси X
    p.perspectiveProj(90.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 10.0f, 10000.0f);
    // Загружаем данные в uniform-переменные шейдера (адрес переменной, количество матриц,
    // передаётся ли матрица по строкам, указатель на первый элемент матрицы)
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.getTransformation());
```
## 5) Проекция перспективы
В пайплайн добавляем вспомогательные методы и переменную:
```c++
void InitPerspectiveProj(glm::mat4 &m) const;

struct {
    float FOV
    float width;
    float height;
    float zNear;
    float zFar;
} mPersProj;

void PerspectiveProj(float FOV, float width, float height, float zNear, float zFar) {
    mPersProj.FOV = FOV;
    mPersProj.width = width;
    mPersProj.height = height;
    mPersProj.zNear = zNear;
    mPersProj.zFar = zFar;
}
```
В методе getTransformation добавляем в умножение матрицу перспективы:
```c++
mTransformation = persProjTrans * translationTrans * rotateTrans * scaleTrans;
```
В шейдер вершин добавим вычисление цвета:
```c++
Color = vec4(clamp(Position, 0.0, 0.5), 1.0);  
```
Создадим шейдер фрагментов для установки цвета:
```c++                                                    
#version 330                                                               

in vec4 Color;
out vec4 FragColor;

void main() {
    // Устанавливаем цвет                                                    
    FragColor = Color;
} 
```
Изменим преобразования матрицы:
```c++
// Создаём pipeline для трансформаций
Pipeline p;
// Меняем масштаб
p.Scale(0.1f, 0.1f, 0.1f);
// Вращаем фигуру
p.Rotate(0, Scale, 0);
// Устанавливаем положение фигуры
p.WorldPos(0.0f, 0.0f, 5.0f);
// Задаём проекцию перспективы
p.PerspectiveProj(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
```
