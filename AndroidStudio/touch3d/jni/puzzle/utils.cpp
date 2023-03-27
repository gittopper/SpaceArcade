#include "utils.h"

#include "print.h"
#include "puzzle55.h"
#include "solver.h"

using namespace Geometry;

PiecesSet generateWoodPuzzles() {
  PiecesSet pieces;

  Piece p1(1);
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 1)));
  p1.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 1, 0), Vector(1, 1, 0)));
  p1.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(0, -1, 1)));
  pieces.pieces.push_back(p1);

  Piece p2(2);
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p2.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(1, 0, 1)));
  p2.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(1, 1, 0), Vector(0, 1, 1)));
  pieces.pieces.push_back(p2);

  Piece p3(3);
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 1)));
  p3.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(1, 0, 1)));
  p3.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 1, 0), Vector(-1, 0, -1)));
  pieces.pieces.push_back(p3);

  Piece p4(4);
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 1)));
  p4.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(0, -1, -1)));
  p4.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 2, 0), Vector(-1, 1, 0)));
  pieces.pieces.push_back(p4);

  Piece p5(5);
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p5.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(0, 1, 1)));
  p5.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 2, 0), Vector(-1, 1, 0)));
  pieces.pieces.push_back(p5);

  Piece p6(6);
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p6.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(1, 0, 1)));
  p6.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 2, 0), Vector(0, 1, 1)));
  pieces.pieces.push_back(p6);

  Piece p7(7);
  p7.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p7.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 1)));
  p7.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(-1, 0, -1)));
  p7.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(1, 1, 0), Vector(0, 1, 1)));
  pieces.pieces.push_back(p7);

  Piece p8(8);
  p8.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p8.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p8.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 0, 1), Vector(1, 0, 1)));
  p8.parts.push_back(
      VolPart(VolPart::VolType::Angle, Vector(0, 1, 1), Vector(0, 1, 1)));
  pieces.pieces.push_back(p8);

  return pieces;
}
PiecesSet generateSomaPuzzles() {
  PiecesSet pieces;

  Piece p1(1);
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 1)));
  pieces.pieces.push_back(p1);

  Piece p2(2);
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 1)));
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  pieces.pieces.push_back(p2);

  Piece p3(3);
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 1)));
  p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  pieces.pieces.push_back(p3);

  Piece p4(4);
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(2, 1, 0)));
  p4.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  pieces.pieces.push_back(p4);

  Piece p5(5);
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p5.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 2, 0)));
  pieces.pieces.push_back(p5);

  Piece p6(6);
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(2, 0, 0)));
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  p6.parts.push_back(VolPart(VolPart::VolType::Full, Vector(2, 1, 0)));
  pieces.pieces.push_back(p6);

  Piece p7(7);
  p7.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 0, 0)));
  p7.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
  p7.parts.push_back(VolPart(VolPart::VolType::Full, Vector(1, 1, 0)));
  pieces.pieces.push_back(p7);

  return pieces;
}

void solve55() {
  std::vector<std::vector<int> > pieces;

  std::vector<int> puzzle1;
  puzzle1.push_back(3);
  puzzle1.push_back(6);
  puzzle1.push_back(8);
  pieces.push_back(puzzle1);

  std::vector<int> puzzle2;
  puzzle2.push_back(0);
  puzzle2.push_back(2);
  puzzle2.push_back(6);
  pieces.push_back(puzzle2);

  std::vector<int> puzzle3;
  puzzle3.push_back(1);
  puzzle3.push_back(3);
  puzzle3.push_back(5);
  pieces.push_back(puzzle3);

  std::vector<int> puzzle4;
  puzzle4.push_back(4);
  puzzle4.push_back(5);
  puzzle4.push_back(6);
  pieces.push_back(puzzle4);

  std::vector<int> puzzle5;
  puzzle5.push_back(2);
  puzzle5.push_back(5);
  puzzle5.push_back(9);
  pieces.push_back(puzzle5);

  std::vector<int> puzzle6;
  puzzle6.push_back(0);
  puzzle6.push_back(6);
  puzzle6.push_back(9);
  pieces.push_back(puzzle6);

  std::vector<int> puzzle7;
  puzzle7.push_back(0);
  puzzle7.push_back(2);
  puzzle7.push_back(9);
  pieces.push_back(puzzle7);

  std::vector<int> puzzle8;
  puzzle8.push_back(0);
  puzzle8.push_back(4);
  puzzle8.push_back(9);
  pieces.push_back(puzzle8);

  Puzzle55 puzzle55(pieces);
  puzzle55.printFigures();
  puzzle55.solve();
}

void printLastSolution(const PiecesSet& sol, Box box) {
  std::cout << "Number of figures is " << sol.size() << ":" << std::endl;
  std::cout << sol << std::endl;

  for (unsigned i = 0; i < sol.size(); i++) {
    std::cout << (i > 0 ? "," : "") << sol[i].id;
  }
  Box filledBox = box;

  for (unsigned i = 0; i < sol.size(); i++) {
    filledBox.add(sol[i].parts);
  }

  std::cout << std::endl << filledBox << std::endl;

  for (unsigned i = 0; i < sol.size(); i++) {
    box.add(sol[i].parts);
    std::cout << box << std::endl;
    box.remove(sol[i].parts);
  }
}
