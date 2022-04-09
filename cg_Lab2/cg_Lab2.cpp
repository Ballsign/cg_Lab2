#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/vec3.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


//#include <math_3d.h>
using namespace std;

GLuint VBO;
GLuint gWorldLocation;


void RenderSceneCB() {
    static float Scale = 0.0f;
    /*glClearColor(0.7f, 1.0f, 0.7f, 0.0);*/
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);

    /*glPushMatrix();*/
    glLoadIdentity();//восстанавливаем нашу матрицу делая ее единичной
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(Scale, 0.0f, 1.0f, 1.0f);
    


    //glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
    //glm::mat4 Model = glm::mat4(1.0);
    //Model = glm::vec4(1.0, 1.0, 0.0, 1.0);
    //glm::vec4 Transformed = Model * Position;

    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 3);

    /*glBegin(GL_TRIANGLES);

    glVertex2f(-0.5, 0.0);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, 0.0);

    glEnd();*/

    glutWireTeapot(0.5);
    glFlush();

    /*glPopMatrix();*/
    Scale += 0.1f;
    
    //glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("kirill rulz ok");
    glutDisplayFunc(RenderSceneCB);

    //glm::vec3 Vertices[4];
    //Vertices[0] = glm::vec3(-0.5f, 0.0f, 0.0f);
    //Vertices[1] = glm::vec3(0.0f, 0.5f, 0.0f);
    //Vertices[2] = glm::vec3(0.5f, 0.0f, 0.0f);
    //Vertices[3] = glm::vec3(0, 0, 0);



    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);





    //glm::mat4 myMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
    //glm::vec4 myVector(10.0f, 10.0f, 10.0f, 1.0f);
    //glm::vec4 transformedVector = myMatrix * myVector;


    glutIdleFunc(RenderSceneCB);
    glutMainLoop();
}