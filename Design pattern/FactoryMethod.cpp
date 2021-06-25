#include <iostream>
#include <cmath>

struct Point
{
    float x;
    float y;

    Point(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

class Shape
{
public:
    enum ShapeType
    {
        RECTANGLE = 0,
        SQUARE,
        TRIANGLE,
        CIRCLE
    };
    virtual float get_area() = 0;
    virtual void set_geometry(Point p1, Point p2, Point p3) {}
    virtual void set_geometry(Point p, float radius) {}
};

class Rectangle : public Shape
{
public:
    Rectangle() {}

    void set_geometry(Point p1, Point p2, Point p3) override
    {
        m_p1 = p1;
        m_p2 = p2;
        m_p3 = p3;
        m_p4 = Point(p1.x - (p2.x - p3.x), p1.y - (p2.y - p3.y));
        m_width = sqrt((m_p1.x - m_p2.x) * (m_p1.x - m_p2.x) + (m_p1.y - m_p2.y) * (m_p1.y - m_p2.y));
        m_height = sqrt((m_p1.x - m_p4.x) * (m_p1.x - m_p4.x) + (m_p1.y - m_p4.y) * (m_p1.y - m_p4.y));
    }

    float get_area() override
    {
        return m_height * m_width;
    }

private:
    Point m_p1, m_p2, m_p3, m_p4;
    float m_width, m_height;
};

class Circle : public Shape
{
public:
    Circle() {}

    void set_geometry(Point p, float radius) override
    {
        m_center = p;
        m_radius = radius;
    }

    float get_area() override
    {
        return M_PI * m_radius * m_radius;
    }

private:
    Point m_center;
    float m_radius;
};

class Factory
{
public:
    static Shape *get_shape(Shape::ShapeType type)
    {
        if (Shape::RECTANGLE == type)
        {
            return new Rectangle();
        }
        else if (Shape::CIRCLE == type)
        {
            return new Circle();
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    Shape *rect = Factory::get_shape(Shape::RECTANGLE);
    rect->set_geometry(Point(0, 0), Point(1, 0), Point(1, 1));
    std::cout << "rect: " << rect->get_area() << std::endl;

    Shape *circle = Factory::get_shape(Shape::CIRCLE);
    circle->set_geometry(Point(0, 0), 1);
    std::cout << "circle: " << circle->get_area() << std::endl;

    return 0;
}