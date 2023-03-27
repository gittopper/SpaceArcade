#include "piece.h"

#include <algorithm>

namespace Geometry {
Piece& Piece::rotate(RotType rot) {
  for (auto& part : parts) {
    part.rotate(rot);
  }
  return *this;
}
Piece& Piece::rotate(Mat rot) {
  for (auto& part : parts) {
    part.rotate(rot);
  }
  return *this;
}
bool Piece::operator==(const Piece& part) const { return parts == part.parts; }
Piece& Piece::shift(const Vector& shift) {
  for (auto& part : parts) {
    part.shift(shift);
  }
  return *this;
}
Mat Piece::getLCS() const {
  Vector x = parts[1].getCoords() - parts[0].getCoords();
  Vector y = parts[2].getCoords() - parts[0].getCoords();
  return Mat(x, y, x.cross(y));
}

Vector Piece::getZero() const { return parts[0].getCoords(); }

void Piece::addToBBox(BBox& bbox) const {
  for (auto& part : parts) {
    bbox.merge(part.getCoords());
  }
}
BBox Piece::getBBox() const {
  BBox box;
  addToBBox(box);
  return box;
}

Piece& Piece::centralize() {
  BBox box(getBBox());
  shift(-box.minV);
  return *this;
}
Piece Piece::copy() const { return Piece(*this); }

Mat Piece::getRotationMatrix(const Piece& part) const {
  Mat rot1 = getLCS();
  Mat rot2 = part.getLCS();

  Mat invRot1 = rot1.inverse();
  Mat res = rot2 * invRot1;
  BREAK_ON_LINE(res.det() == 1);
  return res;
}

bool PiecesSet::operator==(const PiecesSet& set) const {
  if (pieces.size() != set.pieces.size()) return false;
  for (unsigned i = 0; i < pieces.size(); i++) {
    if (pieces[i].id != set.pieces[i].id) return false;
  }

  Mat res = pieces[0].getRotationMatrix(set.pieces[0]);

  Vector prevShift = -pieces[0].getZero();
  Vector shift = set.pieces[0].getZero();

  bool theSame = true;

  for (unsigned i = 0; i < set.pieces.size(); i++) {
    Piece p = pieces[i];

    p.shift(prevShift);
    p.rotate(res);
    p.shift(shift);
    theSame = p == set.pieces[i];
    if (!theSame) break;
  }

  return theSame;
}

void PiecesSet::rotate(Mat rot) {
  for (std::vector<Piece>::iterator it = pieces.begin(); it != pieces.end();
       ++it) {
    (*it).rotate(rot);
  }
}

bool compNumbers(Piece i, Piece j) { return i.id < j.id; }

void PiecesSet::order() {
  std::sort(pieces.begin(), pieces.end(), compNumbers);
}

void PiecesSet::shift(Vector v) {
  for (std::vector<Piece>::iterator it = pieces.begin(); it != pieces.end();
       ++it) {
    (*it).shift(v);
  }
}

}  // namespace Geometry
