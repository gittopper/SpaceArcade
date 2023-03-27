#pragma once

#include "vector.h"
#include "mat.h"
#include "volpart.h"
#include "bbox.h"
#include "box.h"

namespace Geometry
{

using Bitset = std::vector<bool>;

class Piece
{
public:
    Piece(int n):
        id(n) {}

    Piece& rotate(RotType rot);

    Piece& rotate(Mat rot);

    bool operator == (const Piece& part) const;

    Piece& shift(const Vector& shift);

    Mat getRotationMatrix(const Piece& part) const;

    void addToBBox(BBox& bbox) const;

    BBox getBBox() const;

    Mat getLCS() const;

    Vector getZero() const;

    Piece& centralize();

    Piece copy() const;


    int id;
    std::vector<VolPart> parts;
};

class PiecesSet
{
public:
    Piece& operator[](int i)
    {
        return pieces[i];
    }
    const Piece& operator[](int i) const
    {
        return pieces[i];
    }
    unsigned size() const
    {
        return pieces.size();
    }

    bool operator == (const PiecesSet& vec2) const;
    void rotate(Mat rot);
    void shift(Vector v);
    void order();
    std::vector<Piece> pieces;
};

}
