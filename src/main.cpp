#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "RenderGraphics/ShaderFunc.h"

GLfloat point[] =
{
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colorPoint[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

int gl_mainGUIW_sizeY = 600;
int gl_mainGUIW_sizeX = 600;

void glfwMainGUISizeCallBack(GLFWwindow* window, int width, int height) 
{
    gl_mainGUIW_sizeY = height;
    gl_mainGUIW_sizeX = width;
    // показываем GL, где мы будем делать отрисовку окна
    glViewport(0, 0, gl_mainGUIW_sizeX, gl_mainGUIW_sizeY);
}

void glfwCallBackClickOnButton(GLFWwindow* window, int key, int action, int mode) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "The functions of glfwInit not init" << std::endl;
        return -1;
    }
      // минимальная версия GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // core file от GL; для совместимости разных версий GL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow*  mainGUIW = glfwCreateWindow(gl_mainGUIW_sizeY, gl_mainGUIW_sizeX, "MainWindow", nullptr, nullptr);
    if (!mainGUIW)
    {
        std::cout << "MainWindow is not to create" << std::endl;;
        glfwTerminate();
        return -1;
    }
    // отрисовка окна через функцию
    glfwSetWindowSizeCallback(mainGUIW, glfwMainGUISizeCallBack);
    //glfwSetKeyCallback(mainGUIW, glfwCallBackClickOnButton);

    /* Make the window's context current */
    glfwMakeContextCurrent(mainGUIW);

    if (!gladLoadGL())
    {
		std::cout << "Error initialize of librirary" << std::endl;   
		return -1; 	
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGl version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 1, 0, 1);


    // Создаем Шейдера черещ Интерфейс
    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);
    Renderer::ShaderFunc ShaderFunc(vertexShader, fragmentShader);
    if (ShaderFunc.funcCheckOnGoodCompile()) 
    {
        std::cerr << "Cant create shader program " << std::endl;
    }

    // Передача в видеокарту vertex
    GLuint point_vbo = 0;
    glGenBuffers(1, &point_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);



    // Передача в видеокарту vertex
    GLuint color_fbo = 0;
    glGenBuffers(1, &color_fbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_fbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorPoint), colorPoint, GL_STATIC_DRAW);



    // Указываем что делать видоекарте с этими данными
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0); // текущая позиция для массива 
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, color_fbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mainGUIW))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Отрисовка фигур
        ShaderFunc.useMainFunc();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* меняет буффер с фронта и бэка, который рендериться на экране */
        glfwSwapBuffers(mainGUIW);

        // обработка всех событий начиная от нажатия клавиш до измене. курсора
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}