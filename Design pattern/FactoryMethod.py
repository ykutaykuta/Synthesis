from abc import ABCMeta, abstractmethod
from math import hypot, pi

from multipledispatch import dispatch


class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)


class Shape(metaclass=ABCMeta):
    RECTANGLE = 0
    CIRCLE = 1
    TRIANGLE = 2
    SQUARE = 3

    @abstractmethod
    def get_area(self) -> float:
        pass

    @dispatch(Point, Point, Point)
    @abstractmethod
    def set_geometry(self, p1: Point, p2: Point, p3: Point):
        pass

    @dispatch(Point, float)
    @abstractmethod
    def set_geometry(self, p: Point, r: float):
        pass


class Rectangle(Shape):
    def __init__(self):
        self.p1 = Point()
        self.p2 = Point()
        self.p3 = Point()
        self.p4 = Point()
        self.width = 0
        self.height = 0

    def set_geometry(self, p1: Point, p2: Point, p3: Point):
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        self.p4 = Point(p1 - (p2 - p3))
        p = p1 - p2
        self.width = hypot(p.x, p.y)
        p = p2 - p3
        self.height = hypot(p.x, p.y)

    def get_area(self) -> float:
        return self.width * self.height


class Circle(Shape):
    def __init__(self):
        self.center = Point()
        self.radius = 0

    def set_geometry(self, p: Point, r: float):
        self.center = p
        self.radius = r

    def get_area(self) -> float:
        return pi * self.radius * self.radius


class Factory:
    @staticmethod
    def get_shape(shapeType):
        if shapeType == Shape.RECTANGLE:
            return Rectangle()
        elif shapeType == Shape.CIRCLE:
            return Circle()
        else:
            return None


if __name__ == "__main__":
    rect = Factory.get_shape(Shape.RECTANGLE)
    rect.set_geometry(Point(0, 0), Point(1, 0), Point(1, 1))
    print("rect: {}".format(rect.get_area()))

    circle = Factory.get_shape(Circle.CIRCLE)
    circle.set_geometry(Point(0, 0), 1)
    print("circle: {}".format(circle.get_area()))
