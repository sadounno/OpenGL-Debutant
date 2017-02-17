#include "Shader.h"

// Constructeurs et Destructeur

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{

}

Shader::Shader(Shader const &shaderACopier)
{
    // Copie des fichiers sources
    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;

    // Chargement du nouveau shader
    charger();
}

Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}

Shader::~Shader()
{
    // Destruction du shader
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}

// Methodes
Shader& Shader::operator=(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;

    // Chargement du nouveau shader
    charger();


    // Retour du pointeur this

    return *this;
}

bool Shader::charger()
{
    initializeOpenGLFunctions();
    // Destruction d'un eventuel ancien Shader

    if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if(glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);

    // Compilation des shaders
    if(!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Creation du programme

    m_programID = glCreateProgram();

    // Association des shaders

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entrees shader

    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");

    // Linkage du programme

    glLinkProgram(m_programID);

    // Verification du linkage

    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

    // S'il y a eu une erreur

    if(erreurLink != GL_TRUE)
    {
        // Recuperation de la taille de l'erreur

        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de memoire

        char *erreur = new char[tailleErreur + 1];

        // Recuperation de l'erreur

        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        // Affichage de l'erreur

        std::cout << erreur << std::endl;

        // Liberation de la memoire et retour du booleen false

        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    }

    // Sinon c'est que tout s'est bien passe

    else
        return true;
}

bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Creation du shader

    shader = glCreateShader(type);

    // Verification du shader

    if(shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    // Flux de lecture

    std::ifstream fichier(fichierSource.c_str());

    // Test d'ouverture

    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);

        return false;
    }

    // Strings permettant de lire le code source

    std::string ligne;
    std::string codeSource;

    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';

    // Fermeture du fichier

    fichier.close();

    // Recuperation de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource.c_str();

    // Envoi du code source au shader

    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compilation du shader

    glCompileShader(shader);

    // Verification de la compilation

    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // Recuperation de la taille de l'erreur

        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de memoire

        char *erreur = new char[tailleErreur + 1];

        // Recuperation de l'erreur

        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        // Affichage de l'erreur

        std::cout << erreur << std::endl;

        // Liberation de la memoire et retour du booleen false

        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }

    // Sinon c'est que tout s'est bien passe

    else
        return true;
}

// Getter

GLuint Shader::getProgramID() const
{
    return m_programID;
}
