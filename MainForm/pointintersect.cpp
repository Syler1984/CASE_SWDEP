#include "pointintersect.h"

#include "cmath"

PointIntersect::PointIntersect()
{
}

bool PointIntersect::isIntersect(const QPoint &pline1, const QPoint &pline2, float height, const QPoint &point)
{
    Point rect[4];

    Point p1(pline1.x(), pline1.y());
    Point p2(pline2.x(), pline2.y());

    Point enter(point.x(), point.y());

    calcNormPoints(p1, p2, rect[0], rect[1], height);
    calcNormPoints(p2, p1, rect[2], rect[3], height);

    return isIntersectPolygon(enter, rect);
}

float PointIntersect::getAngle(const Point &p0, const Point &p1, const Point &p2)
{
    const float ap1 = sqrtf((p1.x - p0.x)*(p1.x - p0.x) + (p1.y - p0.y)*(p1.y - p0.y));
    const float ap2 = sqrtf((p2.x - p0.x)*(p2.x - p0.x) + (p2.y - p0.y)*(p2.y - p0.y));

    return acosf(((p1.x - p0.x)*(p2.x - p0.x) + (p1.y - p0.y)*(p2.y - p0.y))/ (ap1*ap2) );
}

PointIntersect::Point PointIntersect::rotatePoint(const PointIntersect::Point &p0, const PointIntersect::Point &p1, float angle)
{
    return Point(cos(angle) * (p1.x - p0.x) - sin(angle) * (p1.y - p0.y) + p0.x,
                 cos(angle) * (p1.y - p0.y) - sin(angle) * (p1.x - p0.x) + p0.y);
}

void PointIntersect::calcNormPoints(const Point p1, const Point p2, Point &pointRect1, Point &pointRect2, float height)
{
    float angle = getAngle(p1, Point(p1.x + 1, p1.y), p2);

    if (p1.y > p2.y)
        angle = -angle;

    Point startPoint1 = rotatePoint(p1, Point(p1.x + height/2, p1.y), angle);

    pointRect1 = rotatePoint(p1, startPoint1, 3.14 / 2.);
    pointRect2 = rotatePoint(p1, startPoint1, -3.14 / 2.);
}

bool PointIntersect::isIntersectPolygon(const Point test, PointIntersect::Point *polygon4)
{
    static const int q_patt[2][2] = { { 0, 1 }, { 3, 2 } };

        Point pred_pt = polygon4[3];
        pred_pt.x -= test.x;
        pred_pt.y -= test.y;

        int pred_q = q_patt[pred_pt.y < 0][pred_pt.x < 0];

        int w = 0;

        for (int i=0;i<4;i++)
        {
            Point cur_pt = polygon4[i];

            cur_pt.x -= test.x;
            cur_pt.y -= test.y;

            int q = q_patt[cur_pt.y < 0][cur_pt.x < 0];

            switch (q - pred_q)
            {
            case -3:++w; break;
            case 3:--w; break;
            case -2:if (pred_pt.x*cur_pt.y >= pred_pt.y*cur_pt.x) ++w; break;
            case 2:if (!(pred_pt.x*cur_pt.y >= pred_pt.y*cur_pt.x)) --w; break;
            }

            pred_pt = cur_pt;
            pred_q = q;

        }

        return w != 0;
}
