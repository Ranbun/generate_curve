#ifndef GENERATEBEZIERCURVE_H
#define GENERATEBEZIERCURVE_H

#include <vector>
#include <Vertex.h>

class BezierCurveBuilder
{
public:
    BezierCurveBuilder() = default;
    ~BezierCurveBuilder() = default;

    /**
     * @brief 生成绘制贝塞尔曲线的离散点
     * @param points 传进来的控制点 
     * @return 离散后的结果
    */
    std::vector<Vertex> generate(std::vector<Vertex>& points)
    {
        auto dis = 0.01;

        std::vector<Vertex> resPoints;

        for (auto t = 0.0f; t < 1.0; t += dis)
        {
            auto res = generatePoitnts(points, t);  /// 新生成的曲线绘制的离散点
            resPoints.emplace_back(res);
        }

        return resPoints;
    }
    Vertex generatePoitnts(std::vector<Vertex>& points, float t)
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

        return generatePoitnts(newPoints, t);
    }

};




#endif 