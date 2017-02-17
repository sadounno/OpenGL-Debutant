#include "cube.h"
#include <cstring>
#include <QOpenGLBuffer>
// Macro utile au VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

Cube::Cube(float taille, const std::string vertexShader, const std::string fragmentShader)
    : m_shader(vertexShader, fragmentShader), m_vboID(0),
      m_tailleVerticesBytes(108 * sizeof(float)),
      m_tailleCouleursBytes(108 * sizeof(float)), m_vaoID(0)

{
    initializeOpenGLFunctions();

    // Chargement du shader
    m_shader.charger();

    // Division du paramètre taille
       taille /= 2;


       float verticesTmp[] = {-taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,     // Face 1
                              -taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,     // Face 1

                              taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,       // Face 2
                              taille, -taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 2

                              -taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,      // Face 3
                              -taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,    // Face 3

                              -taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,        // Face 4
                              -taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,        // Face 4

                              -taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,     // Face 5
                              -taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,     // Face 5

                              -taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 6
                              -taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille};      // Face 6

    // Couleurs temporaires
    float couleursTmp[] = {1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1
                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1

                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2
                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2

                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3
                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3

                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4
                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5
                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 6
                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0};          // Face 6

    // Copie des valeurs dans les tableaux finaux

    for(int i(0); i < 108; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_couleurs[i] = couleursTmp[i];
    }

}

Cube::~Cube()
{
       // Destruction du VBO
        glDeleteBuffers(1, &m_vboID);

        // Destruction du VAO
        glDeleteVertexArrays(1, &m_vaoID);
}

void Cube::afficher(QMatrix4x4 &projection, QMatrix4x4 &modelview)
{
//    m_shader.charger();
     glUseProgram(m_shader.getProgramID());//Activation du shader

//     // Verrouillage du VBO
//     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

//     // Accès aux vertices dans la mémoire vidéo
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//     glEnableVertexAttribArray(0);

//     // Accès aux couleurs dans la mémoire vidéo
//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
//         glEnableVertexAttribArray(1);

//     // Déverrouillage du VBO

//     glBindBuffer(GL_ARRAY_BUFFER, 0);

     // Verrouillage du VAO
     glBindVertexArray(m_vaoID);

     glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(),"projection"),1,GL_FALSE,projection.data());
     glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(),"modelview"),1,GL_FALSE,modelview.data());

     glDrawArrays(GL_TRIANGLES,0,36);//Affichage du premier triangle

     // Déverrouillage du VAO
      glBindVertexArray(0);

//     glDisableVertexAttribArray(2);//Désactivation des tableaux VertexAttribArray
     glDisableVertexAttribArray(1);//Désactivation des tableaux VertexAttribArray
     glDisableVertexAttribArray(0);
     glUseProgram(0);//Désactivation du shader

}

void Cube::charger()
{
    // Destruction d'un éventuel ancien VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);

    // Génération de l'ID
    glGenBuffers(1, &m_vboID);

    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Allocation de la mémoire
    glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);

    // Transfert des données
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_couleurs);

    // Déverrouillage de l'objet
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //-----------VAO
    // Destruction d'un éventuel ancien VAO
      if(glIsVertexArray(m_vaoID) == GL_TRUE)
          glDeleteVertexArrays(1, &m_vaoID);

    // Génération de l'ID du VAO
    glGenVertexArrays(1, &m_vaoID);
    // Verrouillage du VBO
    glBindVertexArray(m_vboID);

    //----------
    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Accès aux vertices dans la mémoire vidéo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Accès aux couleurs dans la mémoire vidéo
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
        glEnableVertexAttribArray(1);

    // Déverrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Deerrouillage du VBO
    glBindVertexArray(0);

}

//void Cube::update(void *donnees, int tailleBytes, int decalage)
//{
//    // Verrouillage du VBO
//    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

//        // Récupération de l'adresse du VBO
//    void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//    // Si l'adresse retournée est nulle alors on arrête le transfert
//    if(adresseVBO == NULL)
//        {
//            std::cout << "Erreur au niveau de la récupération du VBO" << std::endl;
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//            return;
//        }
//        // Mise à jour des données
//        memcpy((char*)adresseVBO + decalage, donnees, tailleBytes);

//        // Annulation du pointeur
//        glUnmapBuffer(GL_ARRAY_BUFFER);
//        adresseVBO = 0;

//        // Déverrouillage du VBO
//        glBindBuffer(GL_ARRAY_BUFFER, 0);

//}
