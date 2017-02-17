#ifndef CUBE_H
#define CUBE_H

#include <QMatrix4x4>
#include <QtGui/QOpenGLFunctions_3_2_Core>
#include "Shader.h"
#include "texture.h"

class Cube:protected QOpenGLFunctions_3_2_Core
{
public:

    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();
   void afficher(QMatrix4x4 &projection, QMatrix4x4 &modelview);
   void charger();
   void updateVBO(void *donnees, int tailleBytes, int decalage);

protected:

    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];

    GLuint m_vboID;
    int m_tailleVerticesBytes;
    int m_tailleCouleursBytes;
    GLuint m_vaoID;

};
#endif // CUBE_H
