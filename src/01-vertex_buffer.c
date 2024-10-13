/* Includes ================================================================ */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "gl-lab.h"

/* User-Defined Macros ===================================================== */

// clang-format off

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  800

// clang-format on

/* Constants =============================================================== */

static const char *vertexShaderSrc =
    "#version 320 es\n"
    "layout (location = 0) in vec3 aPosition;\n"
    "void main() {\n"
    "    gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);\n"
    "}\0";

static const char *fragmentShaderSrc =
    "#version 320 es\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/* Private Variables ======================================================= */

static GLFWmonitor *glfwMonitor;
static GLFWwindow *glfwWindow;

static unsigned int vertexShader, fragmentShader, shaderProgram;
static unsigned int vao, vbo, ebo;

/* Private Function Prototypes ============================================= */

static void InitExample(void);
static void UpdateExample(void);
static void DeinitExample(void);

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
    if (!glfwInit()) GLAB_PANIC("failed to initialize GLFW");

    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    glfwMonitor = glfwGetPrimaryMonitor();

    glfwWindow = glfwCreateWindow(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              __FILE__,
                              NULL,
                              NULL);

    if (glfwWindow == NULL) GLAB_PANIC("failed to create window with GLFW");

    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress))
        GLAB_PANIC("failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(glfwWindow, SetViewport);

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwMonitor);

    int windowX = (videoMode->width - SCREEN_WIDTH) / 2;
    int windowY = (videoMode->height - SCREEN_HEIGHT) / 2;

    glfwSetWindowPos(glfwWindow, windowX, windowY);

    glfwShowWindow(glfwWindow);

    {
        // 정점 셰이더를 컴파일한다.
        vertexShader = CompileVertexShader(vertexShaderSrc);

        // 프래그먼트 셰이더를 컴파일한다.
        fragmentShader = CompileFragmentShader(fragmentShaderSrc);

        // 셰이더 프로그램을 빌드한다.
        shaderProgram = LinkShaderProgram(vertexShader, fragmentShader);
    }

    {
        /* ======================= [실습 코드] ======================= */

        // 삼각형의 정점 좌표를 NDC 범위 내에 정의한다.
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  // #0
            0.5f,  -0.5f, 0.0f,  // #1
            0.0f,  0.5f,  0.0f   // #2
        };

        // 정점 셰이더가 정점 좌표 배열을 어떻게 읽을지를 지정하기 위해
        // VAO 1개를 생성하고, `vao` 변수에 VAO의 ID를 저장한다.
        glGenVertexArrays(1, &vao);

        // 정점 좌표 배열을 VRAM에 보내기 위해 VBO 1개를 생성하고,
        // `vbo` 변수에 Buffer Object의 ID를 저장한다.
        glGenBuffers(1, &vbo);

        // 각 정점 좌표의 비디오 메모리 주소, 그리고 좌표에 대한 속성이
        // `vao`가 가리키는 곳에 저장될 것임을 OpenGL 컨텍스트에 알린다.
        glBindVertexArray(vao);

        {
            // `vbo`가 가리키는 곳에 정점 좌표들이
            // 저장될 것임을 OpenGL 컨텍스트에 알린다.
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            // 정점 좌표가 저장된 배열을 VRAM으로 보낸다.
            glBufferData(GL_ARRAY_BUFFER,
                        sizeof vertices,
                        vertices,
                        GL_STATIC_DRAW);
        }

        {
            /*
                아래 문장은 정점 셰이더의 0번 위치 (`layout (location = 0)`)에 대한
                입력이 어떻게 들어갈지를 지정하는데, 두 번째와 세 번째 인자는 
                "0번 위치에 있는 정점의 자료형 (`vec3`)은 3개의 `float`으로 
                이루어져 있다"를 뜻하고,

                다섯 번째 인자 ('stride')는 "3개의 `float`으로 이루어진 정점 좌표 
                1개를 읽은 후, 그 다음 정점 좌표를 읽기 위해서는 시작 지점에서 
                `3 * sizeof(float)` 만큼 이동해야 한다"는 것을 뜻하며, 마지막 
                인자 ('offset')은 시작 지점을 결정한다. 
                
                (따라서 인덱스가 `i`인 정점 좌표의 시작 지점은 `offset + (i * stride)`,
                예를 들면 `vertices`에서 첫 번째 좌표는 `vertices + (0 + (0 * stride))`
                에서 시작하고, 두 번째 좌표는 `vertices + (0 + (1 * stride))`에서 시작)
            */
            glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

            // `vao`가 가리키는 속성 정보를 정점 셰이더의 0번 위치에 넘겨준다.
            glEnableVertexAttribArray(0);
        }

        // 셰이더 프로그램을 활성화한다.
        glUseProgram(shaderProgram);

        /* ======================= [실습 코드] ======================= */
    }
}

static void UpdateExample(void) {
    HandleKeyEvents(), HandleMouseEvents();

    {
        /* ======================= [실습 코드] ======================= */

        /*
            프레임버퍼 (framebuffer)는 비디오 메모리 (video memory, VRAM)와
            같은 뜻으로, 그래픽 카드 (graphics card)에서 다음으로 그릴 화면의
            픽셀 정보가 저장되는 곳이다.
        */

        // 프레임버퍼 초기화에 사용될 색상을 설정한다.
        glClearColor(GLAB_TO_RGB01(202.0f, 235.0f, 202.0f, 255.0f));

        // 프레임 버퍼를 초기화한다.
        glClear(GL_COLOR_BUFFER_BIT);

        // 게임 화면에 삼각형을 그리기 위해 `vao`를 이용한다.
        glBindVertexArray(vao);

        // 정점 배열의 첫 번째 정점부터 세 번째 정점까지, 총 3개 정점으로 삼각형을 그린다.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* ======================= [실습 코드] ======================= */
    }

    glfwSwapBuffers(glfwWindow), glfwPollEvents();
}

static void DeinitExample(void) {
    {
        /* ======================= [실습 코드] ======================= */

        glDeleteVertexArrays(1, &vao), glDeleteBuffers(1, &vbo);

        glDeleteProgram(shaderProgram);

        /* ======================= [실습 코드] ======================= */
    }

    glfwTerminate();
}

/* ========================================================================= */

static void HandleKeyEvents(void) {
    /* TODO: ... */
}

static void HandleMouseEvents(void) {
    /* TODO: ... */
}

/* ========================================================================= */