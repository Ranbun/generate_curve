#include <array>
#include <iostream>

struct Vertex
{
    Vertex(double x, double y, double z)
        : m_position(std::array{x, y, z})
    {

    }

    const double & x()
    {
      return m_position[0];
    }

    void setX(const double & x)
    {
      m_position[0] = x;
    }

    const double & y()
    {
      return m_position[1];
    }

    void setY(const double & y)
    {
      m_position[1] = y;
    }

    const double & z()
    {
      return m_position[2];
    }

    void setZ(const double & z)
    {
      m_position[2] = z;
    }

    std::array<double, 3> m_position;
};