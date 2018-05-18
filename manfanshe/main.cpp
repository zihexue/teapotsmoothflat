//
//  main.cpp
//  manfanshe
//
//  Created by 薛梓赫 on 2018/5/3.
//  Copyright © 2018年 薛梓赫. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//#define OPEN_SPOT  // 开启聚光灯

static int spin = 0;  // 光源旋转角度
typedef unsigned char uchar;

void init(void)
{
    // 定义镜面材料颜色
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // 定义材料光泽度
    GLfloat mat_shininess[] = { 30.0 };
    // 光源位置、环境光、漫反射光
    GLfloat light_position[] = { 0.5, 0.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
    // 设置物体前面接受光照
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    // 设置光源属性
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
#ifdef OPEN_SPOT
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_direction);
#endif
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
void display(void)
{
    GLfloat light_position[] = { 0.0, 0.0, 2, 1.0 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    //glTranslatef(0.0, 0.0, -5.0);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(spin, 1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glTranslated(0., 0.0, 1.5);
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 1.0, 1.0);
    glutWireCube(0.1);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    
   
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 150);// 指定镜面指数
    glutSolidTeapot(0.7);
    glPopMatrix();
    //glutSolidSphere(1.0, 50, 16);
   // gluLookAt(0.0,0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);
    //glTranslatef(0.0,0.0,-1.2);
    //glRotatef(0.0,0.0,0.0,2.0);
    //glColor3f(2.0,1.0,1.0);
    //glutWireTeapot(1.0);

    
    
    glPopMatrix();
    glFlush();
}
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                spin = (spin + 30) % 360;
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                spin = (spin - 30) % 360;
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}
void keyboard(uchar theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
        default:
            break;
    }
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    // 透视投影
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w < h)
    {
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
                1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else
    {
        glOrtho(-1.5 * (GLfloat)h / (GLfloat)w,
                1.5 * (GLfloat)h / (GLfloat)w,
                -1.5, 1.5, -10.0, 10.0);
    }
    // 当前为模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" OpenGL光照");
    init();
    glutDisplayFunc(&display);
    glutReshapeFunc(&reshape);
    glutMouseFunc(&mouse);
    //glutKeyboardFunc(&keyboard);
    glutMainLoop();
    return 0;
}
