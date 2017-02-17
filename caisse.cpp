#include "caisse.h"

// Macro utile au VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

Caisse::Caisse(float taille, const std::string vertexShader, const std::string fragmentShader, const QString texture)
    : Cube(taille, vertexShader, fragmentShader),
      m_texture(texture),
      m_tailleCoordTextureBytes(72 * sizeof(float))

    {
    // Chargement de la texture
    m_texture.loadTexture(texture);
    // Coordonnées de texture temporaires
float t = 1;
    float coordTextureTmp[] = {0, 0,   t, 0,   t, t,     // Face 1
                               0, 0,   0, t,   t, t,     // Face 1

                               0, 0,   t, 0,   t, t,     // Face 2
                               0, 0,   0, t,   t, t,     // Face 2

                               0, 0,   t, 0,   t, t,     // Face 3
                               0, 0,   0, t,   t, t,     // Face 3

                               0, 0,   t, 0,   t, t,     // Face 4
                               0, 0,   0, t,   t, t,     // Face 4

                               0, 0,   t, 0,   t, t,     // Face 5
                               0, 0,   0, t,   t, t,     // Face 5

                               0, 0,   t, 0,   t, t,     // Face 6
                               0, 0,   0, t,   t, t};    // Face 6

    // Copie des valeurs dans le tableau final
    for(int i (0); i < 72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}


Caisse::~Caisse()
{
    // Destruction du VBO
     glDeleteBuffers(1, &m_vboID);

     // Destruction du VAO
     glDeleteVertexArrays(1, &m_vaoID);

}

void Caisse::afficher(QMatrix4x4 &projection, QMatrix4x4 &modelview)
{
//    m_shader.charger();
    glUseProgram(m_shader.getProgramID());//Activation du shader

    // Verrouillage du VAO
    glBindVertexArray(m_vaoID);

    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(),"projection"),1,GL_FALSE,projection.data());
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(),"modelview"),1,GL_FALSE,modelview.data());

//    QMatrix4x4 projectionmodelview;
//    projectionmodelview = projection * modelview;
//    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(),"projectionmodelview"),1,GL_FALSE,projectionmodelview.data());

    // Verrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, m_texture.getID());

    glDrawArrays(GL_TRIANGLES,0,36);//Affichage du premier triangle

    // Déverrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Verrouillage du VAO
    glBindVertexArray(0);

    glUseProgram(0);//Désactivation du shader

}

void Caisse::charger()
{
    // Destruction d'un éventuel ancien VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);

    // Génération de l'ID
    glGenBuffers(1, &m_vboID);

    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        // Allocation de la mémoire vidéo
        glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCoordTextureBytes, 0, GL_STATIC_DRAW);

        // Transfert des données
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCoordTextureBytes, m_coordTexture);

    // Déverrouillage de l'objet
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //--------VAO
    // Destruction d'un éventuel ancien VAO
        if(glIsVertexArray(m_vaoID) == GL_TRUE)
            glDeleteVertexArrays(1, &m_vaoID);

        // Génération de l'ID du VAO
        glGenVertexArrays(1, &m_vaoID);

        // Verrouillage du VAO
        glBindVertexArray(m_vaoID);

            // -----code des attrib vbo
        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

            // Accès aux vertices dans la mémoire vidéo
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            // Accès aux coordonnées de texture dans la mémoire vidéo
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
            glEnableVertexAttribArray(2);

        // Déverrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

//---fin du code des atrib

        // Déverrouillage du VAO
        glBindVertexArray(0);
}
