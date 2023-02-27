#ifndef GENERATEBEZIERCURVE_H
#define GENERATEBEZIERCURVE_H

#include <vector>
#include <Vertex.h>

class GeometryBuilder
{
public:
    GeometryBuilder() = default;
    virtual ~GeometryBuilder() = default;
    virtual std::vector<Vertex> generate(const std::vector<Vertex> &points) {return {};}
};

class BezierCurveBuilder: public GeometryBuilder
{
public:
    BezierCurveBuilder()
        : GeometryBuilder()
        , m_gap(0.01)
    {

    }

    ~BezierCurveBuilder() override = default ;

    /**
     * @brief 生成绘制贝塞尔曲线的离散点
     * @param points 传进来的控制点 
     * @return 离散后的结果
    */
    std::vector<Vertex> generate(const std::vector<Vertex>& points) override
    {
        std::vector<Vertex> resPoints;
        for (auto t = 0.0f; t < 1.0;)
        {
            auto res = generatePoints(points, t);  /// 新生成的曲线绘制的离散点
            resPoints.emplace_back(res);
            t = t + m_gap;
        }

        return resPoints;
    }

    /**
     * @brief 设置采样的间隔
     * @param sample 采样间隔
     */
    [[maybe_unused]] void setSample(const float sample)
    {
        m_gap = sample;
    }

private:
    /**
     * @brief 递归计算 采样点
     * @param points 当前阶的控制点
     * @param t 权重
     * @return 线上的点
     */
    Vertex generatePoints(const std::vector<Vertex>& points, float t)
    {
        if (points.size() == 1)
        {
            return points[0];
        }

        std::vector<Vertex> newPoints;
        auto n = points.size() - 1;
        for (int i = 0; i < n; i++)
        {
            Vertex newPoint = Vertex{
                (1.0f - t) * points[i].x() + t * points[i + 1].x(),
                (1.0f - t) * points[i].y() + t * points[i + 1].y(),
                0
            };
            newPoints.emplace_back(newPoint);
        }

        return generatePoints(newPoints, t);
    }

protected:
    float m_gap{0.01};
};

#endif