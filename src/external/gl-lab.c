/* Includes ================================================================ */

#include "gl-lab.h"

/* Private Variables ======================================================= */

static char compileLog[MAX_COMPILE_LOG_LENGTH];

static double deltaTime, elapsedTime;

/* Public Functions ======================================================== */

GLuint CompileVertexShader(const char *const vertexShaderSrc) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);

    glCompileShader(vertexShader);

    {
        int success = 0;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader,
                               sizeof compileLog,
                               NULL,
                               compileLog);

            fprintf(stderr, __FILE__ ": [SHADER] %s", compileLog);

            GLAB_PANIC("failed to compile vertex shader");
        }
    }

    return vertexShader;
}

GLuint CompileFragmentShader(const char *const fragmentShaderSrc) {
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);

    glCompileShader(fragmentShader);

    {
        int success = 0;

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShader,
                               sizeof compileLog,
                               NULL,
                               compileLog);

            fprintf(stderr, __FILE__ ": [SHADER] %s", compileLog);

            GLAB_PANIC("failed to compile fragment shader");
        }
    }

    return fragmentShader;
}

GLuint LinkShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    {
        int success = 0;

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shaderProgram,
                                sizeof compileLog,
                                NULL,
                                compileLog);

            fprintf(stderr, __FILE__ ": [SHADER] %s", compileLog);

            GLAB_PANIC("failed to link shader program");
        }
    }

    glDeleteShader(vertexShader), glDeleteShader(fragmentShader);

    return shaderProgram;
}

/* ========================================================================= */

void SetViewport(GLFWwindow *glfwWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

/* ========================================================================= */

double GetDeltaTime(void) {
    return deltaTime;
}

void UpdateDeltaTime(void) {
    double currentTime = glfwGetTime();

    deltaTime = currentTime - elapsedTime;
    elapsedTime = currentTime;
}

/* ========================================================================= */