#pragma once

#include "geometry.h"

#include "volumepuzzle.h"
#include "timer.h"

namespace Geometry
{

class Solver
{
public:
    Solver(VolumePuzzle& puzzle);

    void solve();

    void multithread(bool ml = false);
    void stopSolving();
private:
    Timer m_timer;
    VolumePuzzle& m_puzzle;
    int m_dimX, m_dimY, m_dimZ;
    Box m_box;
    bool m_continueToSolve;
    PiecesSet m_solution;
    unsigned m_numPlaced;
    PiecesSet m_pieces;
    unsigned m_allPositionsNumber;
    std::vector<PiecesSet> m_piecesInAllPositions;
    std::vector<std::vector<BBox> > m_piecesBBoxes;
    Bitset m_bs;
    int m_progress;
    bool m_searchAllSollutions;
    unsigned m_maxSol;

    void remove(const Piece& part);
    void place(const Piece& part);
    bool couldPlace(const Piece& part, bool& matched) const;
    bool hasSqueezed(const Piece& part) const;
    bool tryToPlace(const Piece& part);

    bool verifyAlgorithm();

    bool newSolution();
    bool foundNewSolution();
    void recursiveSolve();
};
}
