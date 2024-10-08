/* Includes ================================================================ */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Macros ================================================================== */

#define LOG(level, ...)                                             \
    do {                                                            \
        fprintf(stderr, __FILE__ ": " level ": " __VA_ARGS__ "\n"); \
    } while (0)

#define PANIC(...)                         \
    do {                                   \
        LOG("error", __VA_ARGS__);         \
                                           \
        if (glfwInit()) DeinitExample();   \
                                           \
        exit(1);                           \
    } while (0)

/* User-Defined Macros ===================================================== */

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  800

/* Private Variables ======================================================= */

static GLFWmonitor *glfwMonitor;
static GLFWwindow *glfwWindow;

static bool initialized;

/* Private Function Prototypes ============================================= */

static void InitExample(void);
static void UpdateExample(void);
static void DeinitExample(void);

static void SetViewport(GLFWwindow *glfwWindow, int width, int height);

static void HandleKeyEvents(void);
static void HandleMouseEvents(void);

/* Public Functions ======================================================== */

int main(void) {
    InitExample();

    while (!glfwWindowShouldClose(glfwWindow))
        UpdateExample();

    DeinitExample();

    return 0;
}

/* Private Functions ======================================================= */

static void InitExample(void) {
    if (!glfwInit()) PANIC("failed to initialize GLFW");

    glfwMonitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    glfwWindow = glfwCreateWindow(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              __FILE__,
                              NULL,
                              NULL);

    if (glfwWindow == NULL) PANIC("failed to create window with GLFW");

    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, SetViewport);

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwMonitor);

    int windowX = (videoMode->width - SCREEN_WIDTH) / 2;
    int windowY = (videoMode->height - SCREEN_HEIGHT) / 2;

    glfwSetWindowPos(glfwWindow, windowX, windowY);

    glfwShowWindow(glfwWindow);
}

static void UpdateExample(void) {
    {
        HandleKeyEvents(), HandleMouseEvents();

        /* TODO: ... */

        glfwSwapBuffers(glfwWindow), glfwPollEvents();
    }
}

static void DeinitExample(void) {
    glfwTerminate();
}

/* ========================================================================= */

static void SetViewport(GLFWwindow *glfwWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

/* ========================================================================= */

static void HandleKeyEvents(void) {
    /* TODO: ... */
}

static void HandleMouseEvents(void) {
    /* TODO: ... */
}

/* ========================================================================= */