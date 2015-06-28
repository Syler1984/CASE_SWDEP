#ifndef POINTINTERSECT_H
#define POINTINTERSECT_H


#include <QPoint>

class PointIntersect
{
public:
    PointIntersect();

    static bool isIntersect(const QPoint &pline1, const QPoint &pline2, float height, const QPoint &point);

private:

    struct Point
    {
        Point(){}

        Point(float _x, float _y):
            x(_x),
            y(_y)
        {}

        float x;
        float y;
    };

    static float getAngle(const Point &p0, const Point &p1, const Point &p2);
    static Point rotatePoint(const Point &p0, const Point &p1, float angle);
    static void calcNormPoints(const Point p1, const Point p2, Point &pointRect1, Point &pointRect2, float height);
    static bool isIntersectPolygon(const Point test, Point *polygon4);
};

#endif // POINTINTERSECT_H
