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

protected:
    /**
     * @brief 控制点
     */
    std::vector<Vertex> m_controlPoints;

    /**
     * @brief 顶点数组缓冲
     */
    [[maybe_unused]] GLuint VAO{0};

    /**
     * @brief 顶点缓冲
     */
    [[maybe_unused]] GLuint VBO{0};

    /**
     * @brief 绘制的数据
     */
    std::vector<float> vertices;

};


#endif