/* Includes ================================================================ */

#include "gl-lab.h"

/* User-Defined Macros ===================================================== */

// clang-format off

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  800

// clang-format on

/* Constants =============================================================== */

static const char *vertexShaderSrc =
    "#version 300 es\n"
    "\n"
    "layout (location = 0) in vec3 aPosition;\n"
    "\n"
    "uniform vec3 myPosition;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(myPosition.x + aPosition.x, \n"
    "        myPosition.y + aPosition.y, \n"
    "        myPosition.z + aPosition.z, \n"
    "        1.0f); \n"
    "}\0";

static const char *fragmentShaderSrc = 
    "#version 300 es\n"
    "\n"
    "precision highp float;"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "uniform vec4 myColor;\n"
    "\n"
    "void main() {\n"
    "    fragColor = myColor;\n"
    "}\0";

// clang-format off

static const float vertices[] = { 
     0.5f,  0.5f, 
     0.5f, -0.5f, 
    -0.5f, -0.5f,
    -0.5f,  0.5f
};

static const unsigned int indices[] = {
    0, 1, 3
};

// clang-format on

/* Private Variables ======================================================= */

static GLFWmonitor *glfwMonitor;
static GLFWwindow *glfwWindow;

static float myPosition[3] = {
    0.0f,  // `x`
    0.0f,  // `y`
    0.0f   // `z`
};

static GLuint vertexShader, fragmentShader, shaderProgram;

static GLuint vao, vbo, ebo;

static GLint myPositionLocation, myColorLocation;

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

        {
            myPositionLocation = glGetUniformLocation(shaderProgram,
                                                      "myPosition");
            myColorLocation = glGetUniformLocation(shaderProgram, "myColor");
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
            float colorValue = fabs(sin(glfwGetTime()));

            glUniform4f(myColorLocation, colorValue, colorValue, 1.0f, 1.0f);
        }

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);

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
    bool keyPressed = false;

    float movementSpeed = 0.1f * GetDeltaTime();

    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
        keyPressed = !keyPressed, myPosition[0] -= movementSpeed;
    else if (glfwGetKey(glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
        keyPressed = !keyPressed, myPosition[0] += movementSpeed;

    // 키보드 방향키 입력에 따라 삼각형의 위치를 변경한다.
    if (keyPressed)
        glUniform3f(myPositionLocation,
                        myPosition[0],
                        myPosition[1],
                        myPosition[2]);
}

static void HandleMouseEvents(void) {
    /* TODO: ... */
}

/* ========================================================================= */