#pragma once
#include "vector.h"
#include <renderer.h>

namespace Geometry
{
class Piece;
class VolPart;
class PiecesSet;
}

namespace Visualization
{

class PieceDrawer
{
public:
    void draw(Renderer& renderer, const Geometry::Piece& part, const Geometry::Vector& color) const;
};

class PiecesSetShower
{
public:
    void draw(Renderer& renderer, const Geometry::PiecesSet& pieces, const Geometry::Vector& color) const;
private:
    PieceDrawer partDrawer;
};

class VolPartDrawer
{
public:
    void draw(Renderer& renderer, const Geometry::VolPart& v, const Geometry::Vector& color) const;
private:
    class Triangle
    {
    public:
        Triangle(Geometry::Vector vert1, Geometry::Vector vert2, Geometry::Vector vert3, Geometry::Vector ni): v1(vert1), v2(vert2), v3(vert3), n(ni) {}
        Geometry::Vector v1, v2, v3, n;
    };
    class Plane
    {
    public:
        Plane(Geometry::Vector pi, Geometry::Vector ni): p(pi), n(ni) {}
        Geometry::Vector p, n;
    };
};
}
