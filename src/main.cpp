#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "RenderGraphics/ShaderFunc.h"
#include "Resources/ResourceManager.h"

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


int gl_mainGUIW_sizeY = 600;
int gl_mainGUIW_sizeX = 600;

void glfwMainGUISizeCallBack(GLFWwindow* window, int width, int height) 
{
    gl_mainGUIW_sizeY = height;
    gl_mainGUIW_sizeX = width;
    // показываем GL, где мы будем делать отрисовку окна
    glViewport(0, 0, gl_mainGUIW_sizeX, gl_mainGUIW_sizeY);
}


int main(int argc, char ** argv)
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

    /* Make the window's context current */
    glfwMakeContextCurrent(mainGUIW);

    if (!gladLoadGL())
    {
		std::cout << "Error initialize of librirary" << std::endl;   
		return -1; 	
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGl version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);
    
    {
        ResourceManager resourceManager(argv[0]);
        auto ptrDefaultShaderProgram = resourceManager.loadShader("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!ptrDefaultShaderProgram)
        {
          std::cerr << "Cant create shader program: " << "DefaultShader" << std::endl;
          return -1;
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
            ptrDefaultShaderProgram->useMainFunc();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* меняет буффер с фронта и бэка, который рендериться на экране */
            glfwSwapBuffers(mainGUIW);

            // обработка всех событий начиная от нажатия клавиш до измене. курсора
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}