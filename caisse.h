#ifndef CAISSE_H
#define CAISSE_H


#include "cube.h"
#include "Texture.h"
#include <QString>

class Caisse : public Cube
{
public:
    Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, const QString texture);

    ~Caisse();

    void afficher(QMatrix4x4 &projection, QMatrix4x4 &modelview);
    void charger();
private:
    Texture m_texture;
    float m_coordTexture[72];
    int m_tailleCoordTextureBytes;
};

#endif // CAISSEVBO_H
