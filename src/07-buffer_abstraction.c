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
    "\n"
    "layout (location = 0) in vec3 aPosition;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(aPosition, 1.0f); \n"
    "}\0";

static const char *fragmentShaderSrc1 =
    "#version 320 es\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "uniform vec4 myColor1;\n"
    "\n"
    "void main() {\n"
    "    fragColor = myColor1;\n"
    "}\0";

static const char *fragmentShaderSrc2 =
    "#version 320 es\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "uniform vec4 myColor2;\n"
    "\n"
    "void main() {\n"
    "    fragColor = myColor2;\n"
    "}\0";

// clang-format off

static const float vertices[] = { 
     0.5f,  0.5f, 
     0.5f, -0.5f, 
    -0.5f, -0.5f,
    -0.5f,  0.5f
};

static const unsigned int indices1[] = {
    0, 1, 3
};

static const unsigned int indices2[] = {
    1, 2, 3
};

// clang-format on

/* Private Variables ======================================================= */

static GLFWmonitor *glfwMonitor;
static GLFWwindow *glfwWindow;

static unsigned int vertexShader, fragmentShader1, fragmentShader2,
    shaderProgram1, shaderProgram2;

static unsigned int vao1, vao2, vbo1, vbo2, ebo1, ebo2;

static int myColor1Location, myColor2Location;

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

    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwMonitor);

    int windowX = (videoMode->width - SCREEN_WIDTH) / 2;
    int windowY = (videoMode->height - SCREEN_HEIGHT) / 2;

    glfwSetWindowPos(glfwWindow, windowX, windowY);

    glfwShowWindow(glfwWindow);

    {
        vertexShader = CompileVertexShader(vertexShaderSrc);

        fragmentShader1 = CompileFragmentShader(fragmentShaderSrc1);
        fragmentShader2 = CompileFragmentShader(fragmentShaderSrc2);

        shaderProgram1 = LinkShaderProgram(vertexShader, fragmentShader1);
        shaderProgram2 = LinkShaderProgram(vertexShader, fragmentShader2);
    }

    {
        /* ======================= [실습 코드] ======================= */

        // TODO: ...

        {
            glUseProgram(shaderProgram1);

            myColor1Location = glGetUniformLocation(shaderProgram1, "myColor1");
            glUniform4f(myColor1Location, GLAB_TO_RGB01(224.0f, 240.0f, 217.0f, 255.0f));

            glUseProgram(shaderProgram2);

            myColor2Location = glGetUniformLocation(shaderProgram2, "myColor2");
            glUniform4f(myColor2Location, GLAB_TO_RGB01(184.0f, 216.0f, 190.0f, 255.0f));
        }

        {
            // TODO: ...
        }

        /* ======================= [실습 코드] ======================= */
    }
}

static void UpdateExample(void) {
    HandleKeyEvents(), HandleMouseEvents(), UpdateDeltaTime();

    {
        /* ======================= [실습 코드] ======================= */

        glClearColor(GLAB_TO_RGB01(202.0f, 235.0f, 202.0f, 255.0f));

        glClear(GL_COLOR_BUFFER_BIT);

        {
            // TODO: ...
        }

        {
            // TODO: ...
        }

        /* ======================= [실습 코드] ======================= */
    }

    glfwSwapBuffers(glfwWindow), glfwPollEvents();
}

static void DeinitExample(void) {
    {
        /* ======================= [실습 코드] ======================= */

        // TODO: ...

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