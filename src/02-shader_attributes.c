/* Includes ================================================================ */

#include "gl-lab.h"

/* User-Defined Macros ===================================================== */

// clang-format off

#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           800

#define MAX_COMPILE_LOG_LENGTH  1024

// clang-format on

/* Constants =============================================================== */

static const char *vertexShaderSrc =
    "#version 300 es\n"
    "\n"
    "layout (location = 0) in vec3 aPosition;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);\n"
    "}\0";

static const char *fragmentShaderSrc =
    "#version 300 es\n"
    "\n"
    "precision highp float;"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main() {\n"
    "    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/* Private Variables ======================================================= */

static GLFWmonitor *glfwMonitor;
static GLFWwindow *glfwWindow;

static GLuint vertexShader, fragmentShader, shaderProgram;

static GLuint vao, vbo, ebo;

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    glfwMonitor = glfwGetPrimaryMonitor();

    glfwWindow = glfwCreateWindow(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              __FILE__,
                              NULL,
                              NULL);

    if (glfwWindow == NULL) 
        GLAB_PANIC("failed to create window with GLFW");

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
        vertexShader = CompileVertexShader(vertexShaderSrc);
        fragmentShader = CompileFragmentShader(fragmentShaderSrc);

        shaderProgram = LinkShaderProgram(vertexShader, fragmentShader);
    }

    {
        /* ======================= [실습 코드] ======================= */

        float vertices[] = {
            FLT_MAX, -0.5f, -0.5f, FLT_MAX,  // #0
            FLT_MAX, 0.5f,  -0.5f, FLT_MAX,  // #1
            FLT_MAX, 0.0f,  0.5f,  FLT_MAX   // #2
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                        sizeof vertices,
                        vertices,
                        GL_STATIC_DRAW);
        }

        {
            // `vertices[i] = (offset + (i * stride));`
            // `&vertices[i]`에서부터 시작해서 딱 `size`개만 읽음
            glVertexAttribPointer(
                0,                      // `location`
                2,                      // `size`
                GL_FLOAT,               // `type`
                GL_FALSE,               // `normalized`
                4 * sizeof(float),      // `stride`
                (void *) sizeof(float)  // `offset`
            );

            glEnableVertexAttribArray(0);
        }

        glUseProgram(shaderProgram);

        /* ======================= [실습 코드] ======================= */
    }
}

static void UpdateExample(void) {
    HandleKeyEvents(), HandleMouseEvents();

    {
        /* ======================= [실습 코드] ======================= */

        glClearColor(GLAB_TO_RGB01(202.0f, 235.0f, 202.0f, 255.0f));

        glClear(GL_COLOR_BUFFER_BIT);

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