#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLTexture>
#include <QtGui/QOpenGLFunctions>


class Texture:protected QOpenGLFunctions

{

public:

    Texture(QString fichierImage);

    ~Texture();

    bool charger();

    GLuint getID() const;

    void setFichierImage(const std::string &fichierImage);
    void loadTexture(QString textureName);

private:

    GLuint m_id;

    std::string m_fichierImage;
    QString pathImage;

    QOpenGLTexture *m_texture;

};

#endif // TEXTURE_H
