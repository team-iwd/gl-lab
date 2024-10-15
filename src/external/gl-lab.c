/* Includes ================================================================ */

#include "gl-lab.h"

/* Private Variables ======================================================= */

static char compileLog[MAX_COMPILE_LOG_LENGTH];

static double deltaTime, elapsedTime;

/* Public Functions ======================================================== */

GLFWwindow *gbCreateWindow(int width, int height, const char *title) {
    if (width <= 0 || height <= 0 || title == NULL) return NULL;

    GLFWwindow *glfwWindow = NULL;

    if (!glfwInit()) GB_PANIC("failed to initialize GLFW");

    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    GLFWmonitor *glfwMonitor = glfwGetPrimaryMonitor();

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (glfwWindow == NULL) GB_PANIC("failed to create window with GLFW");

    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress))
        GB_PANIC("failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(glfwWindow, gbSetViewport);

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwMonitor);

    int windowX = (videoMode->width - width) / 2;
    int windowY = (videoMode->height - height) / 2;

    glfwSetWindowPos(glfwWindow, windowX, windowY);

    glfwShowWindow(glfwWindow);

    return glfwWindow;
}

void gbReleaseWindow(GLFWwindow *window) {
    if (window == NULL) return;

    glfwDestroyWindow(window);

    glfwTerminate();
}

/* ========================================================================= */

GLuint gbCreateVertexArray(void) {
    GLuint vertexArrayId = 0U;

    glGenVertexArrays(1, &vertexArrayId);

    return vertexArrayId;
}

void gbReleaseVertexArray(GLuint vertexArrayId) {
    glDeleteVertexArrays(1, &vertexArrayId);
}

void gbBindVertexArray(GLuint vertexArrayId) {
    glBindVertexArray(vertexArrayId);
}

void gbUnbindVertexArray(void) {
    glBindVertexArray(0U);

    glBindBuffer(GL_ARRAY_BUFFER, 0U);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);
}

/* ========================================================================= */

GLuint gbCreateBufferObject(void) {
    GLuint bufferObjectId = 0U;

    glGenBuffers(1, &bufferObjectId);

    return bufferObjectId;
}

void gbReleaseBufferObject(GLuint bufferObjectId) {
    glDeleteBuffers(1, &bufferObjectId);
}

void gbUpdateBufferObject(GLenum target,
                          GLuint bufferObjectId,
                          GLsizeiptr size,
                          const void *ptr,
                          GLenum usage) {
    glBindBuffer(target, bufferObjectId);
    glBufferData(target, size, ptr, usage);
}

/* ========================================================================= */

GLuint gbCompileVertexShader(const char *const vertexShaderSrc) {
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);

    glCompileShader(vertexShaderId);

    {
        int success = 0;

        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShaderId,
                               sizeof compileLog,
                               NULL,
                               compileLog);

            fprintf(stderr, __FILE__ ": [SHADER] %s", compileLog);

            GB_PANIC("failed to compile vertex shader");
        }
    }

    return vertexShaderId;
}

GLuint gbCompileFragmentShader(const char *const fragmentShaderSrc) {
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);

    glCompileShader(fragmentShaderId);

    {
        int success = 0;

        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShaderId,
                               sizeof compileLog,
                               NULL,
                               compileLog);

            fprintf(stderr, __FILE__ ": [SHADER] %s", compileLog);

            GB_PANIC("failed to compile fragment shader");
        }
    }

    return fragmentShaderId;
}

/* ========================================================================= */

GLuint gbCreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId) {
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);

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

            GB_PANIC("failed to link shader program");
        }
    }

    glDeleteShader(vertexShaderId), glDeleteShader(fragmentShaderId);

    return shaderProgram;
}

void gbReleaseShaderProgram(GLuint shaderProgramId) {
    glDeleteShader(shaderProgramId);
}

void gbBindShaderProgram(GLuint shaderProgramId) {
    glUseProgram(shaderProgramId);
}

void gbUnbindShaderProgram(void) {
    glUseProgram(0U);
}

/* ========================================================================= */

void gbSetViewport(GLFWwindow *glfwWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

/* ========================================================================= */

double gbGetDeltaTime(void) {
    return deltaTime;
}

void gbUpdateDeltaTime(void) {
    double currentTime = glfwGetTime();

    deltaTime = currentTime - elapsedTime;
    elapsedTime = currentTime;
}

/* ========================================================================= */