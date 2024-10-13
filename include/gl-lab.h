/* ========================================================================= */

#ifndef GL_LAB_H
#define GL_LAB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================ */

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Macro Constants ========================================================= */

#define MAX_COMPILE_LOG_LENGTH  1024

/* Macros ================================================================== */

#define INVERSE_UCHAR_MAX  (1.0f / UCHAR_MAX)

#define GLAB_LOG(level, ...)                                        \
    do {                                                            \
        fprintf(stderr, __FILE__ ": " level ": " __VA_ARGS__ "\n"); \
    } while (0)

#define GLAB_PANIC(...)                    \
    do {                                   \
        GLAB_LOG("error", __VA_ARGS__);    \
                                           \
        exit(1);                           \
    } while (0)

#define GLAB_TO_RGB01(r, g, b, a)  \
    (r) * INVERSE_UCHAR_MAX,       \
    (g) * INVERSE_UCHAR_MAX,       \
    (b) * INVERSE_UCHAR_MAX,       \
    (a) * INVERSE_UCHAR_MAX        \

/* Public Functions ======================================================== */

GLuint CompileVertexShader(const char *const vertexShaderSrc);
GLuint CompileFragmentShader(const char *const fragmentShaderSrc);
GLuint LinkShaderProgram(GLuint vertexShader, GLuint fragmentShader);

/* ========================================================================= */

void SetViewport(GLFWwindow *glfwWindow, int width, int height);

/* ========================================================================= */

double GetDeltaTime(void);
void UpdateDeltaTime(void);

/* ========================================================================= */

#ifdef __cplusplus
}
#endif

#endif // `GL_LAB_H`