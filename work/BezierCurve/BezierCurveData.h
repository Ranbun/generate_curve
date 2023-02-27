#ifndef BEZIERCURVEDATA_H
#define BEZIERCURVEDATA_H

#include <vector>

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

protected:

//    std::vector<Vertex> m_cont


};


#endif