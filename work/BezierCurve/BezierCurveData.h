#ifndef BEZIERCURVEDATA_H
#define BEZIERCURVEDATA_H

#include <vector>
#include <Vertex.h>
#include <glad/glad.h>

class Data
{
public:
    Data() = default;
    virtual ~Data() = default;

protected:
    std::vector<float> m_renderData;
};


class BezierCurveData : public Data
{
public:
    BezierCurveData()
    : Data()
    {

    }

    void addControlPoint(const Vertex & point)
    {
        m_controlPoints.emplace_back(point);
    }

    void cleanControlPoint()
    {
        m_controlPoints.clear();
    }

    /**
     * @brief 获取控制点
     * @return 当前已经添加的控制点
     */
    const std::vector<Vertex> & controlPoints()
    {
        return m_controlPoints;
    }

    /**
     * @brief 设置绘制的数据
     * @param data 下一次即将绘制的数据
     */
    void setVertices(const std::vector<float> & data)
    {
        m_vertices.insert(m_vertices.end(),data.begin(),data.end());
    }

    const std::vector<float> & vertices()
    {
        return m_vertices;
    }

    void setVBO(GLuint vbo)
    {
        m_VBO = vbo;
    }

    [[nodiscard]] GLuint VBO() const
    {
        return m_VBO;
    }

    void setVAO(GLuint vao)
    {
        m_VAO = vao;
    }

    [[nodiscard]] GLuint VAO() const
    {
        return m_VAO;
    }


protected:
    /**
     * @brief 控制点
     */
    std::vector<Vertex> m_controlPoints;

    /**
     * @brief 顶点数组缓冲
     */
    [[maybe_unused]] GLuint m_VAO{0};

    /**
     * @brief 顶点缓冲
     */
    [[maybe_unused]] GLuint m_VBO{0};

    /**
     * @brief 绘制的数据
     */
    std::vector<float> m_vertices;

};



#endif