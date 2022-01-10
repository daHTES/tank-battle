#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mainGUIW))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* меняет буффер с фронта и бэка, который рендериться на экране */
        glfwSwapBuffers(mainGUIW);

        // обработка всех событий начиная от нажатия клавиш до измене. курсора
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}