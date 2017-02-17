
#include <QDebug>
#include <QFileInfo>

#include "texture.h"

// Constructeur

Texture::Texture(QString fichierImage) : m_id(0), pathImage(fichierImage)
//  Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage)

{

}

// Destructeur

Texture::~Texture()

{
    // Destruction de la texture
    glDeleteTextures(1, &m_id);
}

// Méthodes

bool Texture::charger()

{
    initializeOpenGLFunctions();
    qDebug() <<"int ok"<<endl;

    QImage img("Textures.brick001.jpg");
//    m_texture = new QOpenGLTexture(QImage(":/Textures.brick001.jpg"));
    qDebug() <<"img ok"<<endl;

    if(img.format() != QImage::Format_RGB888)
    {
         img.convertToFormat(QImage::Format_RGB888);
         qDebug() <<"format ok"<<endl;

    }
    if(img.isNull()){
        qDebug() <<"img null"<<endl;
        return false;
    }
//    m_texture = new QOpenGLTexture(img);
    qDebug() <<"texture ogl ok"<<endl;

//    QImage prepareFrame(const QImage& frame) {
//        }
//        return frame;
//    }
//    m_texture = new QOpenGLTexture(QImage(":/Textures.brick001.jpg").mirrored());
    // Génération de l'ID
    glGenTextures(1, &m_id);

    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Détermination du nombre de composantes

    int bytesPerPixel(m_texture->depth()/ 8);
    GLenum format(0);//rgb ou rgba
    GLenum internalFormat(0);//rgb ou brg rgba ou bgra

    if(bytesPerPixel == 3)
    {
        format = GL_RGB;
        internalFormat=GL_RGB;
    }
    else if(bytesPerPixel == 4)
    {
        format = GL_RGBA;
        internalFormat=GL_RGBA;
    }
    else
    {
        qDebug() <<"Erreur, format de l'image inconnu"<<endl;

        delete m_texture;
           return false;
    }

//    --- copier les fameux pixels dans la texture: selon fonction ---
//    void glTexImage2D(GLenum target,  GLint level,  GLint internalFormat,
//    GLsizei width,  GLsizei height,  GLint border,  GLenum format,
//            GLenum type,  const GLvoid * data);

    // Copie des pixels


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.bits());
//    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
//                 img.width(), img.height(), 0, format, GL_UNSIGNED_BYTE, img.bits());

    // Application des filtres

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);

    delete m_texture;
    return true;
}

//bool Texture::charger2()

//{
//    GLuint m_texture;
//initializeOpenGLFunctions();
//    QImage image(pathImage);
////image = new QImage(pathImage);
//    image = image.convertToFormat(QImage::Format_ARGB32);

//    glGenTextures(1, &m_texture);
//    glBindTexture(GL_TEXTURE_2D, m_texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
//    glGenerateMipmap(GL_TEXTURE_2D);

//    glEnable(GL_TEXTURE_2D);
//    return true;
//}

GLuint Texture::getID() const

{
    return m_id;
}

void Texture::setFichierImage(const std::string &fichierImage)

{
    m_fichierImage = fichierImage;
}

void Texture::loadTexture(QString textureName)
{
//    GLuint m_texture;
initializeOpenGLFunctions();
    QImage image;
    image.load(textureName);
    image = image.convertToFormat(QImage::Format_ARGB32);
 image = image.mirrored(false,true);
//    glGenTextures(1, &m_texture);
//    glBindTexture(GL_TEXTURE_2D, m_texture);
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 0);

}
