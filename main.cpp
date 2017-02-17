//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

#include <QGuiApplication>
    #include "scene3d.h"


int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    Scene3D window;
    window.resize(800,600);
    window.show();
    return app.exec();

}
