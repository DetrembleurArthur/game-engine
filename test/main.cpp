#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

// Vertex shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

void checkShaderCompileErrors(GLuint shader) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void checkProgramLinkErrors(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

int main() {
    // Initialiser GLFW
    if (!glfwInit()) {
        std::cerr << "Impossible d'initialiser GLFW" << std::endl;
        return -1;
    }

    // Configurer GLFW pour utiliser OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Créer une fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL);
    if (!window) {
        std::cerr << "Impossible de créer une fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Rendre le contexte de la fenêtre courant
    glfwMakeContextCurrent(window);

    // Initialiser GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Erreur GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    // Définir la taille de la fenêtre
    glViewport(0, 0, 800, 600);

    // Compilation du vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader);

    // Compilation du fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader);

    // Linker les shaders dans un programme
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkErrors(shaderProgram);

    // Supprimer les shaders compilés
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Définir les données du triangle
    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    // Créer un VAO et un VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Lier le VAO
    glBindVertexArray(VAO);

    // Lier le VBO et copier les données des vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Spécifier les attributs des vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Délier le VBO et le VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        // Gérer les événements
        glfwPollEvents();

        // Nettoyer la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        // Utiliser le shader program
        glUseProgram(shaderProgram);

        // Lier le VAO et dessiner le triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Échanger les buffers
        glfwSwapBuffers(window);
    }

    // Nettoyer les ressources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminer GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
