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
    "void main() {\n"
    "    gl_Position = vec4(aPosition, 1.0f); \n"
    "}\0";

static const char *fragmentShaderSrc1 = "#version 300 es\n"
                                        "\n"
                                        "precision highp float;"
                                        "\n"
                                        "out vec4 fragColor;\n"
                                        "\n"
                                        "uniform vec4 myColor1;\n"
                                        "\n"
                                        "void main() {\n"
                                        "    fragColor = myColor1;\n"
                                        "}\0";

static const char *fragmentShaderSrc2 = "#version 300 es\n"
                                        "\n"
                                        "precision highp float;"
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

static GLFWwindow *window;

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

    while (!glfwWindowShouldClose(window))
        UpdateExample();

    DeinitExample();

    return 0;
}

/* Private Functions ======================================================= */

static void InitExample(void) {
    window = gbCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, __FILE__);

    {
        vertexShader = gbCompileVertexShader(vertexShaderSrc);

        fragmentShader1 = gbCompileFragmentShader(fragmentShaderSrc1);
        fragmentShader2 = gbCompileFragmentShader(fragmentShaderSrc2);

        shaderProgram1 = gbCreateShaderProgram(vertexShader, fragmentShader1);
        shaderProgram2 = gbCreateShaderProgram(vertexShader, fragmentShader2);
    }

    {
        /* ======================= [실습 코드] ======================= */

        vao1 = gbCreateVertexArray(), vao2 = gbCreateVertexArray();

        vbo1 = gbCreateBufferObject(), vbo2 = gbCreateBufferObject();
        ebo1 = gbCreateBufferObject(), ebo2 = gbCreateBufferObject();

        gbBindVertexArray(vao1);
        {
            gbUpdateBufferObject(GL_ARRAY_BUFFER,
                                 vbo1,
                                 sizeof vertices,
                                 vertices,
                                 GL_STATIC_DRAW);

            gbUpdateBufferObject(GL_ELEMENT_ARRAY_BUFFER,
                                 ebo1,
                                 sizeof indices1,
                                 indices1,
                                 GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void *) 0);

            glEnableVertexAttribArray(0);
        }

        gbBindVertexArray(vao2);
        {
            gbUpdateBufferObject(GL_ARRAY_BUFFER,
                                 vbo2,
                                 sizeof vertices,
                                 vertices,
                                 GL_STATIC_DRAW);

            gbUpdateBufferObject(GL_ELEMENT_ARRAY_BUFFER,
                                 ebo2,
                                 sizeof indices2,
                                 indices2,
                                 GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void *) 0);

            glEnableVertexAttribArray(0);
        }

        {
            myColor1Location = glGetUniformLocation(shaderProgram1, "myColor1");
            myColor2Location = glGetUniformLocation(shaderProgram2, "myColor2");

            gbSetUniform(shaderProgram1,
                         myColor1Location,
                         4f,
                         GB_TO_RGB01(224.0f, 240.0f, 217.0f, 255.0f));

            gbSetUniform(shaderProgram2,
                         myColor2Location,
                         4f,
                         GB_TO_RGB01(184.0f, 216.0f, 190.0f, 255.0f));
        }

        gbUnbindVertexArray(), gbUnbindShaderProgram();

        /* ======================= [실습 코드] ======================= */
    }
}

static void UpdateExample(void) {
    HandleKeyEvents(), HandleMouseEvents();

    {
        /* ======================= [실습 코드] ======================= */

        glClearColor(GB_TO_RGB01(202.0f, 235.0f, 202.0f, 255.0f));

        glClear(GL_COLOR_BUFFER_BIT);

        {
            gbBindShaderProgram(shaderProgram1), gbBindVertexArray(vao1);

            glDrawElements(GL_TRIANGLES,
                           sizeof indices1,
                           GL_UNSIGNED_INT,
                           NULL);
        }

        {
            gbBindShaderProgram(shaderProgram2), gbBindVertexArray(vao2);

            glDrawElements(GL_TRIANGLES,
                           sizeof indices2,
                           GL_UNSIGNED_INT,
                           NULL);
        }

        /* ======================= [실습 코드] ======================= */
    }

    glfwSwapBuffers(window), glfwPollEvents();
}

static void DeinitExample(void) {
    {
        /* ======================= [실습 코드] ======================= */

        gbReleaseVertexArray(vao1), gbReleaseVertexArray(vao2);

        gbReleaseBufferObject(vbo1), gbReleaseBufferObject(vbo2);
        gbReleaseBufferObject(ebo1), gbReleaseBufferObject(ebo2);

        gbReleaseShaderProgram(shaderProgram1),
            gbReleaseShaderProgram(shaderProgram2);

        /* ======================= [실습 코드] ======================= */
    }

    gbReleaseWindow(window);
}

/* ========================================================================= */

static void HandleKeyEvents(void) {
    /* TODO: ... */
}

static void HandleMouseEvents(void) {
    /* TODO: ... */
}

/* ========================================================================= */