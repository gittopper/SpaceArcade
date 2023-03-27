#pragma once
#include "geometry.h"
#include "solver.h"

Geometry::PiecesSet generateWoodPuzzles();

Geometry::PiecesSet generateSomaPuzzles();

void printLastSolution(const Geometry::PiecesSet& sol, Geometry::Box box);

void solve55();
