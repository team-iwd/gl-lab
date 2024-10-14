/* Includes ================================================================ */

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

// clang-format off

static const float vertices[] = { 
     0.5f,  0.5f, 
     0.5f, -0.5f, 
    -0.5f, -0.5f,
    -0.5f,  0.5f
};

static const unsigned int indices[] = {
/*
    0, 1, 3,
    1, 2, 3,
*/

    0, 1,
    1, 3,
    3, 0,

    1, 2,
    2, 3,
    3, 1
};

// clang-format on

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

    if (glfwWindow == NULL) 
        GLAB_PANIC("failed to create window with GLFW");

    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress))
        GLAB_PANIC("failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(glfwWindow, SetViewport);

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwMonitor);

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

        glGenVertexArrays(1, &vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof vertices,
                         vertices,
                         GL_STATIC_DRAW);
        }

        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof indices,
                         indices,
                         GL_STATIC_DRAW);
        }

        {
            glVertexAttribPointer(
                0, 2, GL_FLOAT, false, 2 * sizeof(float), (void *) 0);

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

        glDrawElements(GL_LINES,         // `mode`
                       sizeof(indices),  // `count`
                       GL_UNSIGNED_INT,  // `type`
                       NULL              // `indices`
        );

        /* ======================= [실습 코드] ======================= */
    }

    glfwSwapBuffers(glfwWindow), glfwPollEvents();
}

static void DeinitExample(void) {
    {
        /* ======================= [실습 코드] ======================= */

        glDeleteBuffers(1, &vbo), glDeleteBuffers(1, &ebo);

        glDeleteVertexArrays(1, &vao);

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