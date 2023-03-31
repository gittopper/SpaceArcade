#include "solver.h"

#include "pieceshower.h"
#include "utils.h"

namespace Geometry {
Solver::Solver(VolumePuzzle& puzzleInstance)
    : m_continueToSolve(true),
      m_numPlaced(0),
      m_maxSol(0),
      m_progress(0),
      m_searchAllSollutions(true),
      m_puzzle(puzzleInstance),
      m_box(m_puzzle.getEmptyBox()),
      m_dimX(m_puzzle.getXDim()),
      m_dimY(m_puzzle.getYDim()),
      m_dimZ(m_puzzle.getZDim()) {
    m_pieces = m_puzzle.getPieces();
    m_bs.resize(m_pieces.size());
    for (unsigned pn = 0; pn < m_pieces.size(); pn++) {
        m_allPositionsNumber = 0;
        const Piece& piece = m_pieces[pn];
        m_bs[pn] = true;
        Piece copy0 = piece;
        PiecesSet pieceInAllPositions;
        std::vector<BBox> piecesBoxes;
        for (int k = 0; k < 4; k++) {
            copy0.rotate(RotateX);
            auto copy1 = copy0;
            for (int i = 0; i < 4; i++) {
                copy1.rotate(RotateY);

                Piece copy2 = copy1;
                for (int j = 0; j < 4; j++) {
                    BBox box = copy2.rotate(RotateZ).getBBox();
                    copy2.shift(-box.minV);

                    if (m_dimX - box.getXSize() < 1 ||
                        m_dimY - box.getYSize() < 1 ||
                        m_dimZ - box.getZSize() < 1)
                        continue;

                    for (const Piece& p : pieceInAllPositions.pieces) {
                        if (p == copy2) continue;
                    }
                    pieceInAllPositions.pieces.push_back(copy2);
                    piecesBoxes.push_back(box);
                }
            }
        }
        m_allPositionsNumber += pieceInAllPositions.size();
        m_piecesInAllPositions.push_back(pieceInAllPositions);
    }
}

void Solver::remove(const Piece& part) {
    m_box.remove(part.parts);
    m_numPlaced--;
}

void Solver::place(const Piece& part) {
    m_box.add(part.parts);
    m_numPlaced++;
    return;
}

bool Solver::couldPlace(const Piece& part, bool& matched) const {
    matched = true;
    for (unsigned i = 0; i < part.parts.size(); i++) {
        const VolPart& vol = part.parts[i];
        if (!m_box.getVolPart(vol.getCoords()).couldPlace(vol)) {
            return false;
        }

        continue;

        if (matched) {
            continue;
        }
        matched =
            matched || m_box.getVolPart(vol.getCoords()).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() - XSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() + XSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() - YSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() + YSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() - ZSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            m_box.getVolPart(vol.getCoords() + ZSHIFT).shareOneOfSides(vol);
    }

    return true;
}

bool Solver::hasSqueezed(const Piece& part) const {
    return false;
    BBox bbox;
    part.addToBBox(bbox);
    bbox.grow();

    for (int x = bbox.minV[0]; x <= bbox.maxV[0]; x++) {
        for (int y = bbox.minV[1]; y <= bbox.maxV[1]; y++) {
            for (int z = bbox.minV[2]; z <= bbox.maxV[2]; z++) {
                //          if (isSqueezed(box.getVolPart(x, y, z])) return
                //          true;
                BREAK_ON_LINE(m_box.isSqueezed(m_box.getVolPart(x, y, z)) ==
                              m_box.isSqueezedV2(m_box.getVolPart(x, y, z)));
                if (m_box.isSqueezedV2(m_box.getVolPart(x, y, z))) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Solver::tryToPlace(const Piece& part) {
    bool matched;

    if (!couldPlace(part, matched)) {
        return false;
    }

    if (m_numPlaced && !matched) {
        return false;
    }

    place(part);

    //    if (hasSqueezed(part)) {
    //        remove(part);
    //        return false;
    //    }

    return true;
}

bool Solver::verifyAlgorithm() {
    Box tt = m_puzzle.getEmptyBox();

    for (unsigned i = 0; i < m_solution.size(); i++) {
        tt.add(m_solution[i].parts);
    }

    return tt == m_box;
}

bool Solver::foundNewSolution() {
    if (m_puzzle.addSolution(m_solution)) {
        m_maxSol = m_numPlaced;
        return true;
    }

    return false;
}

void Solver::multithread(bool ml) {}

void Solver::stopSolving() { m_continueToSolve = false; }

void Solver::solve() {
    std::cout << "starting to solve puzzle" << std::endl;
    m_timer.start();
    recursiveSolve();
    m_timer.stop();
    std::cout << "solved" << std::endl;
    std::cout << getLogString("finish time: ", m_timer.time()) << std::endl;
}

void Solver::recursiveSolve() {
    BREAK_ON_LINE(verifyAlgorithm());

    if (m_maxSol < m_numPlaced) {
        foundNewSolution();
    }

    if (m_numPlaced == m_pieces.size()) {
        foundNewSolution();
        if (!m_searchAllSollutions) {
            return;
        }
    }
    for (unsigned iPuzzle = 0; iPuzzle < m_pieces.size(); iPuzzle++) {
        if (!m_bs[iPuzzle]) {
            continue;
        }

        m_bs[iPuzzle] = false;

        PiecesSet& allPositions = m_piecesInAllPositions[iPuzzle];
        for (unsigned i = 0; i < allPositions.size(); i++) {
            Piece& curPiece = allPositions[i];
            const BBox& boundaries = curPiece.getBBox();

            int xmax = m_dimX - boundaries.getXSize();
            int ymax = m_dimY - boundaries.getYSize();
            int zmax = m_dimZ - boundaries.getZSize();

            if (m_numPlaced == 0) {
                xmax = std::min(xmax, xmax / 2 + 1);
                ymax = std::min(ymax, ymax / 2 + 1);
                zmax = std::min(zmax, zmax / 2 + 1);
            }

            for (int x = 1; x <= xmax; x++) {
                for (int y = 1; y <= ymax; y++) {
                    for (int z = 1; z <= zmax; z++) {
                        if (!m_continueToSolve) {
                            return;
                        }

                        Vector s(x, y, z);
                        curPiece.shift(s);

                        if (tryToPlace(curPiece)) {
                            m_solution.pieces.push_back(curPiece);
                            recursiveSolve();
                            remove(curPiece);
                            m_solution.pieces.pop_back();
                        }
                        curPiece.shift(-s);
                    }
                }
            }
        }
        m_bs[iPuzzle] = true;

        if (m_numPlaced == 0) {
            return;  // we should find all solutions only for one first figure
        }

        if (m_numPlaced == 1) {
            std::cout << "Progress:"
                      << (float(++m_progress) / m_allPositionsNumber /
                          m_pieces.size())
                      << std::endl;
            std::cout << "Elapsed time:" << m_timer.asString() << std::endl;
        }
    }
}
}  // namespace Geometry
