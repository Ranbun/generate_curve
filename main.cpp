#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>


constexpr int WIDGET(){return 800;}
constexpr int HEIGHT(){return 600;}

GLFWwindow * renderWindow{nullptr};

void processInput(GLFWwindow * window);
void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
void mouseCurPosCallBack(GLFWwindow* window, double xpos, double ypos);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    renderWindow = glfwCreateWindow(WIDGET(),HEIGHT(),"Bezier curve window", nullptr,nullptr);
    if(!renderWindow)
    {
        glfwTerminate();
        throw std::runtime_error("Create GLFW Window Error!");
    }

    glfwMakeContextCurrent(renderWindow);

    /**
     * @brief 加载函数
     */
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Load ProcAddress Error!");
    }

    glfwSetKeyCallback(renderWindow,KeyCallBack);
    glfwSetMouseButtonCallback(renderWindow,mouseButtonCallBack);
    glfwSetCursorPosCallback(renderWindow,mouseCurPosCallBack);

    while(!glfwWindowShouldClose(renderWindow))
    {
        processInput(renderWindow);

        glfwSwapBuffers(renderWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    glfwDestroyWindow(renderWindow);
    return 0;
}


void processInput(GLFWwindow * window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if(action == GLFW_PRESS)
        {
            double x,y;
            glfwGetCursorPos(window,&x,&y);
            std::cout<<"Mouse Press Pos: <"<<x<<", "<<y<<">"<<std::endl;
        }
    }
}

void mouseCurPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == 1)
    {
        std::cout<<"mouse cursor callback"<<std::endl;
    }
}

