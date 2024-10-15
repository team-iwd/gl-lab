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

static const char *fragmentShaderSrc1 =
    "#version 300 es\n"
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

static const char *fragmentShaderSrc2 =
    "#version 300 es\n"
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

static GLuint vertexShader, fragmentShader1, fragmentShader2,
    shaderProgram1, shaderProgram2;

static GLuint vao1, vao2, vbo1, vbo2, ebo1, ebo2;

static GLint myColor1Location, myColor2Location;

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

        glGenVertexArrays(1, &vao1), glGenVertexArrays(1, &vao2);

        glGenBuffers(1, &vbo1), glGenBuffers(1, &vbo2);
        glGenBuffers(1, &ebo1), glGenBuffers(1, &ebo2);

        glBindVertexArray(vao1);

        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo1);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof vertices,
                         vertices,
                         GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof indices1,
                         indices1,
                         GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void *) 0);

            glEnableVertexAttribArray(0);
        }

        glBindVertexArray(vao2);

        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo2);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof vertices,
                         vertices,
                         GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof indices2,
                         indices2,
                         GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void *) 0);

            glEnableVertexAttribArray(0);
        }

        {
            glUseProgram(shaderProgram1);

            myColor1Location = glGetUniformLocation(shaderProgram1, "myColor1");
            glUniform4f(myColor1Location,
                        GB_TO_RGB01(224.0f, 240.0f, 217.0f, 255.0f));

            glUseProgram(shaderProgram2);

            myColor2Location = glGetUniformLocation(shaderProgram2, "myColor2");
            glUniform4f(myColor2Location,
                        GB_TO_RGB01(184.0f, 216.0f, 190.0f, 255.0f));
        }

        {
            /*
                VBO는 VAO보다 먼저 언바인딩해도 되지만, EBO는 그렇게 하면 안되는 이유?

                ```
                // VAO의 (진짜는 아닌) 대략적인 형태를 C 구조체로 표현한 것
                typedef struct VAO_ {
                    struct {
                        Vector3 *position;  // VBO에 저장된 정점 좌표의 
                                            // 메모리 주소
                        // ...
                    } *attributes;          // 정점 속성 배열
                    GLuint *ebo;            // EBO 배열
                    int attributeCount;     // 정점 속성의 개수
                    int eboLength;          // EBO 배열의 길이
                } VAO;
                ```

                1. VBO는 `glBufferData()`가 실행된 후 VAO와는 전혀 관계없는, 별도의
                   VRAM 영역에 할당되며, `glVertexAttribPointer()`가 호출되기 전까지는
                   VBO의 각 정점 좌표의 VRAM 주소가 VAO에 저장되지 않는다.

                   따라서 VBO를 VAO보다 먼저 언바인딩하더라도 VAO에는 아무런 영향을
                   주지 않는다.

                2. EBO는 VAO 내의 공간에 저장되기 때문에, EBO를 먼저 언바인딩해버리면
                   VAO에 저장되어 있던 EBO의 VRAM 주소가 사라지게 된다. 따라서 VAO를
                   먼저 언바인딩해야 VAO에 영향을 주지 않고 EBO까지 안전하게 
                   언바인딩할 수 있다.
            */

            glBindVertexArray(0U);

            glBindBuffer(GL_ARRAY_BUFFER, 0U);
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);

            glUseProgram(0U);
        }

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
            glUseProgram(0U), glBindVertexArray(0U);
        }

        {
            glUseProgram(shaderProgram1);
        
            glBindVertexArray(vao1);
            glDrawElements(GL_TRIANGLES, sizeof indices1, GL_UNSIGNED_INT, NULL);
        }

        {
            glUseProgram(shaderProgram2);
        
            glBindVertexArray(vao2);
            glDrawElements(GL_TRIANGLES, sizeof indices2, GL_UNSIGNED_INT, NULL);
        }

        /* ======================= [실습 코드] ======================= */
    }

    glfwSwapBuffers(window), glfwPollEvents();
}

static void DeinitExample(void) {
    {
        /* ======================= [실습 코드] ======================= */

        glDeleteVertexArrays(1, &vao1), glDeleteVertexArrays(1, &vao2);

        glDeleteBuffers(1, &vbo1), glDeleteBuffers(1, &vbo2);
        glDeleteBuffers(1, &ebo1), glDeleteBuffers(1, &ebo2);

        glDeleteShader(shaderProgram1), glDeleteShader(shaderProgram2);

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