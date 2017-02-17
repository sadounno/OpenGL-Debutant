#include "scene3d.h"
#include <QDebug>
#include <QPainter>
#include "cube.h"
#include "Caisse.h"
//#include "caissevbo.h"
//#include "surface2d.h"
//#include "mur2d.h"
//#include "surface2dv.h"



Scene3D::Scene3D(QWindow *parent) :
    QOpenGLWindow(NoPartialUpdate, parent)
{
    resize(width, height);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(16);
//    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer.setInterval(0);
//    timer.start();

    time.start();

}

Scene3D::~Scene3D()
{
    //delete shaderBasique;
}

void Scene3D::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Escape))
    {
close();
    }
//    qDebug() << "OpenGL Version : " << glGetString <<endl;
//std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
}

void Scene3D::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() <<"mouseMoveEvent"<<endl;

}

void Scene3D::initializeGL()
{
    // init OpenGL
    initializeOpenGLFunctions();
    // GL options
    glClearColor(0.52f, 0.52f, 0.52f, 1.0f);
//    glEnable(GL_DEPTH_TEST| GL_DEPTH_BUFFER_BIT);
    // Enable depth buffer
//    glEnable(GL_DEPTH_TEST);

 //    qDebug() <<"initialize"<<endl;

}

void Scene3D::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            QMatrix4x4 projection;
            QMatrix4x4 modelview;
            // Camera

            projection.perspective(70.0,  800 / 600, 1.0, 100.0);
            modelview.setToIdentity();
            modelview.lookAt(QVector3D(0,3,-7), QVector3D(0, 0, 0), QVector3D(0, 1, 0));


//            Caisse caisse(1.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse2.jpg");
//            Surface2D parTerre(10.0,20 ,"Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse2.jpg");
//            Surface2D parTerre(10.0,20 ,"Shaders/texture.vert", "Shaders/texture.frag", "Textures/brick56x56grs.jpg");
//            Mur2D mur(5.0,10 ,"Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse2.jpg");

            // Déclaration d'un objet Cube
//            Cube cubeV(1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");//:/Textures/crate13.jpg
//            cubeV.charger();
            Caisse caisseV(3.0, "Shaders/texture.vert", "Shaders/texture.frag", ":/Textures/Caisse64x64jpg.jpg");
            caisseV.charger();
////            Surface2DV surfaceV(1.0, "Shaders/lounisShad.vert", "Shaders/lounisShad.frag", "Textures/Caisse56x56.jpg");
//            surfaceV.charger();

//            caisse.afficher(projection, modelview);

            angle += 2.70f;
                    if(angle >= 360.0)
                        angle -= 360.0;
                      modelview.rotate(angle, 0, angle);
//         parTerre.afficher(projection, modelview);
//         mur.afficher(projection, modelview);
//           surfaceV.afficher(projection, modelview);

//         cubeV.afficher(projection, modelview);
         caisseV.afficher(projection, modelview);

//         modelview.translate(0, -4.99f, 0);

//             caisseV.afficher(projection, modelview);
//             parTerre.afficher(projection, modelview);

             //control performances
//             for (int i = 0; i < 1000; ++i) {
//                 modelview.translate(0.1f, 0.1f, 0.1f);
//                 caisseV.afficher(projection, modelview);
//                 for (int j = 0; j < 3; ++j) {
//                     modelview.translate(i, j, 0.0f);
//                     caisseV.afficher(projection, modelview);
//                     qDebug() << "i: " << i << " j: " << j<<endl;

//                 }
//             }

                // ++++++++++ Actualisation de la fenêtre

            // FPS count
            ++frame_count;
            const auto elapsed = time.elapsed();
            if (elapsed >= 1000)
            {
                last_count = frame_count;
                frame_count = 0;
                time.restart();
            }

        //     FPS display

            QPainter painter(this);
            painter.setPen(Qt::blue);
            painter.setFont(QFont("Arial", 15));
            painter.drawText(20, 30, ("FPS: ")+QString::number(last_count));

}

void Scene3D::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

}
