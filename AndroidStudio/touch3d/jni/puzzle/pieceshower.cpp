#include "pieceshower.h"
#include "piece.h"
#include "math.h"

using namespace Visualization;
using namespace Geometry;

namespace
{
void drawSquare(Renderer& renderer, const Vector& shift, const Vector& v1, const Vector& v2,
                const Vector& v3, const Vector& v4, const Vector& n, const Geometry::Vector& color)
{
    std::vector<Geometry::Vector> vertices;
    vertices.push_back(Geometry::Vector(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]));
    vertices.push_back(Geometry::Vector( shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]));
    vertices.push_back(Geometry::Vector(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]));
    vertices.push_back(Geometry::Vector(shift[0] + v4[0], shift[1] + v4[1], shift[2] + v4[2]));
    std::vector<Geometry::Vector> normals;
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    std::vector<std::uint16_t> indices{0, 1, 2, 0, 2, 3};
    std::vector<Geometry::Vector> colors = {color, color, color, color};
    renderer.render(reinterpret_cast<GLfloat*>(vertices.data()), reinterpret_cast<GLfloat*>(normals.data()),
                    reinterpret_cast<GLfloat*>(colors.data()), reinterpret_cast<GLushort*>(indices.data()), 6);
}

void drawTriangle(Renderer& renderer, const Vector& shift, const Vector& v1, const Vector& v2,
                  const Vector& v3, const Vector& n, const Geometry::Vector& color)
{
    std::vector<Geometry::Vector> vertices;
    vertices.push_back(Geometry::Vector(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]));
    vertices.push_back(Geometry::Vector( shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]));
    vertices.push_back(Geometry::Vector(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]));
    std::vector<Geometry::Vector> normals;
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    std::vector<std::uint16_t> indices{0, 1, 2};
    std::vector<Geometry::Vector> colors = {color, color, color, color};
    renderer.render(reinterpret_cast<GLfloat*>(vertices.data()), reinterpret_cast<GLfloat*>(normals.data()),
                    reinterpret_cast<GLfloat*>(colors.data()), reinterpret_cast<GLushort*>(indices.data()), 3);
}
}

void PieceDrawer::draw(Renderer& renderer, const Piece& part, const Geometry::Vector& color) const
{
    VolPartDrawer volPartDrawer;
    for (std::vector<VolPart>::const_iterator it = part.parts.begin(); it != part.parts.end(); ++it)
    {
        volPartDrawer.draw(renderer, *it, color);
    }
}

void VolPartDrawer::draw(Renderer& renderer, const Geometry::VolPart& v, const Geometry::Vector& color) const
{
    Vector verts[8];
    verts[0] = Vector(0, 0, 0);
    verts[1] = Vector(1, 0, 0);
    verts[2] = Vector(1, 1, 0);
    verts[3] = Vector(0, 1, 0);

    verts[4] = Vector(0, 0, 1);
    verts[5] = Vector(1, 0, 1);
    verts[6] = Vector(1, 1, 1);
    verts[7] = Vector(0, 1, 1);

    if (v.type() == VolPart::VolType::Empty) return;
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(1, 0, 0)) > 0)
    {
        drawSquare(renderer, v.getCoords(), verts[0], verts[3], verts[7], verts[4], Vector(-1.0, 0.0, 0.0), color);
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(1, 0, 0)) < 0)
    {
        drawSquare(renderer, v.getCoords(), verts[1], verts[5], verts[6], verts[2], Vector(1.0, 0.0, 0.0), color);
    }
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 1, 0)) > 0)
    {
        drawSquare(renderer, v.getCoords(), verts[0], verts[4], verts[5], verts[1], Vector(0.0, -1.0, 0.0), color);
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 1, 0)) < 0)
    {
        drawSquare(renderer, v.getCoords(), verts[3], verts[2], verts[6], verts[7], Vector(0.0, 1.0, 0.0), color);
    }
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 0, 1)) > 0)
    {
        drawSquare(renderer, v.getCoords(), verts[0], verts[1], verts[2], verts[3], Vector(0.0, 0.0, -1.0), color);
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 0, 1)) < 0)
    {
        drawSquare(renderer, v.getCoords(), verts[4], verts[7], verts[6], verts[5], Vector(0.0, 0.0, 1.0), color);
    }
    if (v.type() == VolPart::VolType::Angle)
    {
        ////////////////////////////////
        float s2 = sqrt(1 / 2.);
        const Vector& dir = v.getDir();
        if (dot(dir, Vector(1, 1, 0)) == 2)
        {
            drawSquare(renderer, v.getCoords(), verts[5], verts[7], verts[3], verts[1], Vector(s2, s2, 0.0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(0, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 1), Vector(0, 1, 1), Vector(0, 0, 1), Vector(0, 0, 1), color);
        }
        if (dot(dir, Vector(1, 1, 0)) == -2)
        {
            drawSquare(renderer, v.getCoords(), verts[1], verts[3], verts[7], verts[5], Vector(-s2, -s2, 0.0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(0, 1, 0), Vector(1, 1, 0), Vector(0, 0, -1), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 1), Vector(1, 1, 1), Vector(0, 1, 1), Vector(0, 0, 1), color);
        }
        if (dir[0] == 1 && dir[1] == -1)
        {
            drawSquare(renderer, v.getCoords(), verts[4], verts[6], verts[2], verts[0], Vector(s2, -s2, 0.0), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 0), Vector(0, 1, 0), Vector(1, 1, 0), Vector(0, 0, -1), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 1), Vector(1, 1, 1), Vector(0, 1, 1), Vector(0, 0, 1), color);
        }
        if (dir[0] == -1 && dir[1] == 1)
        {
            drawSquare(renderer, v.getCoords(), verts[0], verts[2], verts[6], verts[4], Vector(-s2, s2, 0.0), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 0), Vector(1, 1, 0), Vector(1, 0, 0), Vector(0, 0, -1), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 1), Vector(1, 0, 1), Vector(1, 1, 1), Vector(0, 0, 1), color);
        }
        ////////////////////////////////
        if (dot(dir, Vector(1, 0, 1)) == 2)
        {
            drawSquare(renderer, v.getCoords(), verts[4], verts[7], verts[2], verts[1], Vector(s2, 0.0, s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 1), Vector(0, 0, 0), Vector(1, 0, 0), Vector(0, -1, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 1, 1), Vector(1, 1, 0), Vector(0, 1, 0), Vector(0, 1, 0), color);
        }
        if (dot(dir, Vector(1, 0, 1)) == -2)
        {
            drawSquare(renderer, v.getCoords(), verts[1], verts[2], verts[7], verts[4], Vector(-s2, 0.0, -s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(1, 0, 1), Vector(0, 0, 1), Vector(0, -1, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 1, 0), Vector(0, 1, 1), Vector(1, 1, 1), Vector(0, 1, 0), color);
        }
        if (dir[0] == 1 && dir[2] == -1)
        {
            drawSquare(renderer, v.getCoords(), verts[0], verts[5], verts[6], verts[3], Vector(s2, 0.0, -s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 1), Vector(0, 0, 1), Vector(0, 0, 0), Vector(0, -1, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 1, 1), Vector(0, 1, 0), Vector(0, 1, 1), Vector(0, 1, 0), color);
        }
        if (dir[0] == -1 && dir[2] == 1)
        {
            drawSquare(renderer, v.getCoords(), verts[3], verts[6], verts[5], verts[0], Vector(-s2, 0.0, s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(1, 0, 1), Vector(0, 0, 0), Vector(0, -1, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 1, 0), Vector(0, 1, 0), Vector(1, 1, 1), Vector(0, 1, 0), color);
        }
        ////////////////////////////////
        if (dot(dir, Vector(0, 1, 1)) == 2)
        {
            drawSquare(renderer, v.getCoords(), verts[3], verts[2], verts[5], verts[4], Vector(0.0, s2, s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), Vector(-1, 0, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 0), Vector(1, 0, 1), Vector(1, 0, 0), color);
        }
        if (dot(dir, Vector(0, 1, 1)) == -2)
        {
            drawSquare(renderer, v.getCoords(), verts[4], verts[5], verts[2], verts[3], Vector(0.0, -s2, -s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 1), Vector(0, 1, 1), Vector(0, 1, 0), Vector(-1, 0, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 1), Vector(1, 1, 0), Vector(1, 1, 1), Vector(1, 0, 0), color);
        }
        if (dir[1] == 1 && dir[2] == -1)
        {
            drawSquare(renderer, v.getCoords(), verts[1], verts[6], verts[7], verts[0], Vector(0.0, s2, -s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 1), Vector(-1, 0, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 1), Vector(1, 0, 1), Vector(1, 0, 0), color);
        }
        if (dir[1] == -1 && dir[2] == 1)
        {
            drawSquare(renderer, v.getCoords(), verts[0], verts[7], verts[6], verts[1], Vector(0.0, -s2, s2), color);
            drawTriangle(renderer, v.getCoords(), Vector(0, 0, 0), Vector(0, 1, 1), Vector(0, 1, 0), Vector(-1, 0, 0), color);
            drawTriangle(renderer, v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 0), Vector(1, 1, 1), Vector(1, 0, 0), color);
        }
    }
}


void PiecesSetShower::draw(Renderer& renderer, const Geometry::PiecesSet& pieces, const Geometry::Vector& color) const
{
    for (int i = 0; i < pieces.pieces.size(); i++)
    {
        Piece p = pieces.pieces[i];
        partDrawer.draw(renderer,p, color);
    }
}

