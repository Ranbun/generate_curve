#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>

#include <Vertex.h>
#include <Shader.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr int WIDGET(){return 800;}
constexpr int HEIGHT(){return 600;}

GLFWwindow * renderWindow{nullptr};
[[maybe_unused]] std::vector<Vertex> controlPoints;

//std::vector<float> vertices;

[[maybe_unused]] GLuint VAO{0};
[[maybe_unused]] GLuint VBO{0};

void processInput(GLFWwindow * window);
void KeyCallBack([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode,
                 [[maybe_unused]] int action, [[maybe_unused]] int mods);
void mouseButtonCallBack(GLFWwindow* window, int button, int action, [[maybe_unused]] int mods);
void mouseCurPosCallBack(GLFWwindow* window, [[maybe_unused]] double xpos, [[maybe_unused]] double ypos);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

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

#if 0
    glfwSetKeyCallback(renderWindow,KeyCallBack);
    glfwSetMouseButtonCallback(renderWindow,mouseButtonCallBack);
    glfwSetCursorPosCallback(renderWindow,mouseCurPosCallBack);
#endif 

    auto vertex   = VertexShader{"./shaders/BezierCurve/vertex.vert"};
    auto fragment = FragmentShader{"./shaders/BezierCurve/fragment.frag"};

    auto program = ShaderProgram();
    program.attachShader(vertex);
    program.attachShader(fragment);
    program.link();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /// load data
#if 0
    vertices.emplace_back(0.000);
    vertices.emplace_back(0.000);
    vertices.emplace_back(0.0);

    vertices.emplace_back(-200);
    vertices.emplace_back(200);
    vertices.emplace_back(0.0);

    vertices.emplace_back(300);
    vertices.emplace_back(300);
    vertices.emplace_back(0.0);
#endif 

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /// position
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3* sizeof (float),nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(renderWindow))
    {

        processInput(renderWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.bind();
        glBindVertexArray(VAO);

#if  0
        glm::mat4 model(1.0f);
        glm::mat4 projection(1.0f);
        glm::mat4 view(1.0f);
        glm::vec3 eye(WIDGET()/2.0f,HEIGHT()/2.0f,-3.0f);
        glm::vec3 center(WIDGET()/2.0f,HEIGHT()/2.0f,0.0f);
        glm::vec3 up(0.0f,1.0f,0.0f);

        view = glm::lookAt(eye,center,up);
        projection = glm::ortho(0.0f,static_cast<float>(WIDGET()),0.0f,static_cast<float>(HEIGHT()),0.1f,100.0f);

        program.setMat4x4("model",model);
        program.setMat4x4("view",view);
        program.setMat4x4("project",projection);
#endif 

        glDrawArrays(GL_TRIANGLES, 0 , 3);

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

void KeyCallBack([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode,
                 [[maybe_unused]] int action, [[maybe_unused]] int mods)
{

}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
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

void mouseCurPosCallBack(GLFWwindow* window, [[maybe_unused]] double xpos, [[maybe_unused]] double ypos)
{
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == 1)
    {
        std::cout<<"mouse cursor callback"<<std::endl;
    }
}

