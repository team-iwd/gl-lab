/* Includes ================================================================ */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl-lab.h"

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

    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress))
        PANIC("failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(glfwWindow, SetViewport);

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwMonitor);

    int windowX = (videoMode->width - SCREEN_WIDTH) / 2;
    int windowY = (videoMode->height - SCREEN_HEIGHT) / 2;

    glfwSetWindowPos(glfwWindow, windowX, windowY);

    glfwShowWindow(glfwWindow);
}

static void UpdateExample(void) {
    HandleKeyEvents(), HandleMouseEvents();

/* ========================================================================= */

    /*
        프레임버퍼 (framebuffer)는 비디오 메모리 (video memory, VRAM)와
        같은 뜻으로, 그래픽 카드 (graphics card)에서 다음으로 그릴 화면의
        픽셀 정보가 저장되는 곳이다.
    */

    g1Color pastelGreen = TO_RGB01(202.0f, 235.0f, 202.0f, 255.0f);

    // 프레임버퍼 초기화에 사용될 색상을 설정한다.
    glClearColor(pastelGreen.r, pastelGreen.g, pastelGreen.b, pastelGreen.a);

    // 프레임 버퍼를 초기화한다.
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: ...

/* ========================================================================= */

    glfwSwapBuffers(glfwWindow), glfwPollEvents();
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