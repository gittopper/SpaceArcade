#pragma once

#include "geometry.h"
#include "timer.h"
#include "volumepuzzle.h"

namespace Geometry {

struct Data {
    Data(const Geometry::Box& box) : m_box(box) {}
    Bitset m_bs;
    Box m_box;
    unsigned m_numPlaced;
    PiecesSet m_solution;
};
class Solver {
   public:
    Solver(VolumePuzzle& puzzle);

    void solve();

    void multithread(bool ml = false);
    void stopSolving();

   private:
    Timer m_timer;
    VolumePuzzle& m_puzzle;
    int m_dimX, m_dimY, m_dimZ;
    bool m_continueToSolve;
    PiecesSet m_pieces;
    unsigned m_allPositionsNumber;
    std::vector<PiecesSet> m_piecesInAllPositions;
    int m_progress;
    bool m_searchAllSollutions;
    unsigned m_maxSol;

    void remove(Data& data, const Piece& part);
    void place(Data& data, const Piece& part);
    bool couldPlace(Data& data, const Piece& part, bool& matched) const;
    bool hasSqueezed(Data& data, const Piece& part) const;
    bool tryToPlace(Data& data, const Piece& part);

    bool verifyAlgorithm(Data& data);

    bool newSolution();
    bool foundNewSolution(Data& data);
    void recursiveSolve(Data& data);
};
}  // namespace Geometry
