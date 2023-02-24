#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <FileReader.h>

class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    [[maybe_unused]] [[nodiscard]] GLuint getShader() const
    {
        return m_shader;
    }

protected:
    [[maybe_unused]] void compilationMessage()
    {
        if (!m_compilationResult)
            std::cerr<< m_compilationInfo<< std::endl;
        std::cout << "compilation shader success!" << std::endl;
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

class [[maybe_unused]] ShaderProgram
{
public:
    ShaderProgram()
    {
        m_program = glCreateProgram();
    }
    virtual ~ShaderProgram() =default;

    [[maybe_unused]] void link()
    {
        glLinkProgram(m_program);

        auto status = 0;
        glGetProgramiv(m_program,GL_LINK_STATUS,&status);

        if(status == GL_FALSE)
        {
            GLint logLength{0};
            glGetProgramiv(m_program,GL_INFO_LOG_LENGTH,&logLength);
            m_linkInfo.resize(logLength);
            glGetProgramInfoLog(m_program,logLength,nullptr,m_linkInfo.data());
        }
        else
        {
            m_linkStatus = true;
        }
        linkMessage();
    }

    [[maybe_unused]] void attachShader(const Shader& shader) const
    {
        glAttachShader(m_program, shader.getShader());
    }

    [[maybe_unused]] void bind() const
    {
        glUseProgram(m_program);
    }

private:
    void linkMessage()
    {
        if(!m_linkStatus)
            std::cerr <<m_linkInfo<<std::endl;
        else
            std::cout<<"Link Success!"<<std::endl;
    }

protected:
    GLuint  m_program{0};
    std::string m_linkInfo;
    bool m_linkStatus{false};
};


#endif