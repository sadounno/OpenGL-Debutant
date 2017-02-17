#ifndef SCENE3D_H
#define SCENE3D_H

#include<QOpenGLWindow>
#include<QOpenGLFunctions>
#include <Qtime>
#include <Qtimer>
#include <QMatrix4x4>
#include<QKeyEvent>
//#include "shader.h"


class Scene3D : public QOpenGLWindow,protected QOpenGLFunctions {

public:
    Scene3D(QWindow *parent = 0);
    ~Scene3D();

private:

    // FPS
    QTime time;
    QTimer timer;

    size_t frame_count{};
    size_t last_count{};
float  width = 800.0f;
float  height = 600.0f;


// Variable angle

float angle =0.0f;
//float x =0.0f;
//float y =0.0f;
//float z =0.0f;
//    float vertices[18];// = {0.0, 0.0,   0.5, 0.0,   0.0, 0.5,-0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};   // Triangle 2
//    float couleurs[18];// = {0.0, 0.0,   0.5, 0.0,   0.0, 0.5,-0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};   // Triangle 2

    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

protected:
    // OpenGL
    void initializeGL();
    void paintGL() ;
    void resizeGL(int width, int height) ;

    // Events
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void wheelEvent(QWheelEvent *event) override;

};

#endif // SCENE3D_H
