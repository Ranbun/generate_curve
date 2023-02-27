#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <memory>

#include <Vertex.h>
#include <Shader.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "generateBezierCurve.h"

constexpr int WIDGET(){return 800;}
constexpr int HEIGHT(){return 600;}

GLFWwindow * renderWindow{nullptr};
[[maybe_unused]] std::vector<Vertex> controlPoints;

std::vector<float> vertices;

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

    glfwSetKeyCallback(renderWindow,KeyCallBack);
    glfwSetMouseButtonCallback(renderWindow,mouseButtonCallBack);
    glfwSetCursorPosCallback(renderWindow,mouseCurPosCallBack);

    auto vertex   = std::make_shared<VertexShader>("./shaders/BezierCurve/vertex.vert");
    auto fragment = std::make_shared<FragmentShader>("./shaders/BezierCurve/fragment.frag");

    auto program = ShaderProgram();
    program.attachShader(*vertex);
    program.attachShader(*fragment);
    program.link();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

#if  0
    /// load data
    vertices.emplace_back(400);
    vertices.emplace_back(450);
    vertices.emplace_back(0.0);

    vertices.emplace_back(600);
    vertices.emplace_back(150);
    vertices.emplace_back(0.0);

    vertices.emplace_back(200);
    vertices.emplace_back(150);
    vertices.emplace_back(0.0);
#endif 

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    /// position
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 7 * sizeof (float),nullptr);
    glEnableVertexAttribArray(0);

    ///color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glViewport(0,0,WIDGET(),HEIGHT());

    while(!glfwWindowShouldClose(renderWindow))
    {
        processInput(renderWindow);

        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        program.bind();
        glBindVertexArray(VAO);
        {
            glPointSize(2.0f);

            glm::mat4 model(1.0f);
            glm::mat4 projection(1.0f);
            glm::mat4 view(1.0f);

            float halfWidth = WIDGET() / 2.0f;
            float halfHeight = HEIGHT() / 2.0f;

            glm::vec3 eye(WIDGET() / 2.0f, HEIGHT() / 2.0f, 3.0f);
            glm::vec3 center(WIDGET() / 2.0f, HEIGHT() / 2.0f, 0.0f);
            glm::vec3 up(0.0f, 1.0f, 0.0f);

            view = glm::lookAt(eye, center, up);

            projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 100.0f);

            program.setMat4x4("model", model);
            program.setMat4x4("view", view);
            program.setMat4x4("project", projection);

            glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(renderWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    vertex.reset();
    fragment.reset();

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
    std::cout << "Key Call Back" << std::endl;
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if(action == GLFW_RELEASE)
        {
            double x,y;
            glfwGetCursorPos(window,&x,&y);
            std::cout<<"Mouse Press Pos: <"<<x<<", "<<y<<">"<<std::endl;

            y = HEIGHT() - y;

            auto point = Vertex(x,y,0);
            controlPoints.emplace_back(point);

            vertices.clear();

            auto bezier = BezierCurveBuilder{};

            if (controlPoints.size() < 3)
            {
                return;
            }

            auto res = bezier.generate(controlPoints);
            std::array<float, 4> lineColor{0.0,1.0, 0.0, 1.0f};
            std::array<float, 4> CotrolPointColor{1.0,0.0, 0.0, 1.0f};

            for(auto Point : res)
            {
                vertices.insert(vertices.end(),Point.m_position.begin(), Point.m_position.end());
                vertices.insert(vertices.end(), lineColor.begin(), lineColor.end());
            }

            for (auto Point : controlPoints)
            {
                vertices.insert(vertices.end(), Point.m_position.begin(), Point.m_position.end());
                vertices.insert(vertices.end(), CotrolPointColor.begin(), CotrolPointColor.end());
            }

            glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (float),nullptr,GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof (float), vertices.data());
            glBindBuffer(GL_ARRAY_BUFFER,0);
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

