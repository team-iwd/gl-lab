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

#include <cglm/cglm.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Macro Constants ========================================================= */

#define MAX_COMPILE_LOG_LENGTH 1024

/* Macros ================================================================== */

#define INVERSE_UCHAR_MAX (1.0f / UCHAR_MAX)

#define GB_LOG(level, ...)                                          \
    do {                                                            \
        fprintf(stderr, __FILE__ ": " level ": " __VA_ARGS__ "\n"); \
    } while (0)

#define GB_PANIC(...)                 \
    do {                              \
        GB_LOG("error", __VA_ARGS__); \
                                      \
        exit(1);                      \
    } while (0)

#define GB_TO_RGB01(r, g, b, a)                                              \
    (r) * INVERSE_UCHAR_MAX, (g) *INVERSE_UCHAR_MAX, (b) *INVERSE_UCHAR_MAX, \
        (a) *INVERSE_UCHAR_MAX

/* Public Functions ======================================================== */

GLFWwindow *gbCreateWindow(int width, int height, const char *title);
void gbReleaseWindow(GLFWwindow *window);

/* ========================================================================= */

GLuint gbCreateVertexArray(void);
void gbReleaseVertexArray(GLuint vertexArrayId);
void gbBindVertexArray(GLuint vertexArrayId);
void gbUnbindVertexArray(void);

/* ========================================================================= */

GLuint gbCreateBufferObject(void);
void gbReleaseBufferObject(GLuint bufferObjectId);
void gbUpdateBufferObject(GLenum target,
                          GLuint bufferObjectId,
                          GLsizeiptr size,
                          const void *ptr,
                          GLenum usage);

/* ========================================================================= */

GLuint gbCompileVertexShader(const char *const vertexShaderSrc);
GLuint gbCompileFragmentShader(const char *const fragmentShaderSrc);

/* ========================================================================= */

GLuint gbCreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
void gbReleaseShaderProgram(GLuint shaderProgramId);
void gbBindShaderProgram(GLuint shaderProgramId);
void gbUnbindShaderProgram(void);

// clang-format off

#define gbSetUniform(shaderProgramId, uniformLocation, uniformType, ...)  \
    do {                                                                  \
        gbBindShaderProgram((shaderProgramId));                           \
                                                                          \
        glUniform ## uniformType((uniformLocation), __VA_ARGS__);         \
    } while(0);

// clang-format on

/* ========================================================================= */

void gbSetViewport(GLFWwindow *glfwWindow, int width, int height);

/* ========================================================================= */

double gbGetDeltaTime(void);
void gbUpdateDeltaTime(void);

/* ========================================================================= */

#ifdef __cplusplus
}
#endif

#endif  // `GL_LAB_H`