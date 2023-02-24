#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    [[maybe_unused]] [[nodiscard]] GLuint getShader() const
    {
        return m_shader;
    }

    [[maybe_unused]] void compilationMessage()
    {
        if (!m_compilationResult)
            std::cout<< m_compilationInfo<< std::endl;
        std::cout<<"compilation shader success!"<<std::endl;
    }

protected:
    bool m_compilationResult{};
    GLuint m_shader{0};
    std::string m_compilationInfo;

};

class [[maybe_unused]] VertexShader :public Shader
{
public:
    explicit VertexShader(const std::string & path)
    :Shader()
    {
        m_shader = glCreateShader(GL_VERTEX_SHADER);
        auto sources = FileReader::LoadShader(path);
        const GLchar *vertexShaderSources = sources.c_str();
        glShaderSource(m_shader, 1, &vertexShaderSources, nullptr);
        glCompileShader(m_shader);

        GLint status{0};
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint logLength{0};
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLength);
            m_compilationInfo.resize(logLength);
            glGetShaderInfoLog(m_shader, logLength, nullptr, m_compilationInfo.data());
            m_compilationResult = false;
        }
        else
        {
            m_compilationResult = true;
        }
        compilationMessage();
    }

    ~VertexShader() override  = default;
};

class [[maybe_unused]] FragmentShader : public Shader
{
public:
    explicit FragmentShader(const std::string &path)
            : Shader()
    {
        m_shader = glCreateShader(GL_FRAGMENT_SHADER);
        auto sources = FileReader::LoadShader(path);
        const GLchar *fragmentShaderSources = sources.c_str();
        glShaderSource(m_shader, 1, &fragmentShaderSources, nullptr);
        glCompileShader(m_shader);

        GLint status{0};
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint logLength{0};
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLength);
            m_compilationInfo.resize(logLength);
            glGetShaderInfoLog(m_shader, logLength, nullptr, m_compilationInfo.data());
            m_compilationResult = false;
        } else
        {
            m_compilationResult = true;
        }
        compilationMessage();
    }

    ~FragmentShader() override = default;
};


class ShaderProgram
{
public:
    ShaderProgram() = default;
    virtual ~ShaderProgram() =default;

#if  0

// 创建着色器程序对象
GLuint shaderProgram = glCreateProgram();

// 将顶点着色器附加到着色器程序对象上
glAttachShader(shaderProgram, vertexShader);

// 链接着色器程序
glLinkProgram(shaderProgram);

// 使用着色器程序
glUseProgram(shaderProgram);


#endif
};


#endif