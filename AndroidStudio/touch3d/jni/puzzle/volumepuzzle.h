#ifndef volumepuzzle_h__
#define volumepuzzle_h__

#include "piece.h"
#include <mutex>

namespace Geometry
{

class VolumePuzzle
{
public:
    VolumePuzzle(int xDim, int yDim, int zDim, const PiecesSet pieces);

    int getXDim() const;
    int getYDim() const;
    int getZDim() const;

    Box getEmptyBox() const;
    const PiecesSet& getPieces() const;

    //true - new solution
    //false - there already exists the same solution
    bool addSolution(const PiecesSet& sol);
    int numFoundSolutions() const;
    void getSolution(PiecesSet& sol, int i) const;

    virtual ~VolumePuzzle() {}

    virtual void addedSolution() {}
protected:

    std::vector<PiecesSet> solutions;
    std::vector<PiecesSet> normalizedSolutions;
    int dimX, dimY, dimZ;
    mutable std::mutex  lock;
//  mutable examples::MutexLock  lock;
    PiecesSet pieces;
private:
    VolumePuzzle(const VolumePuzzle&);
};

}

#endif // volumepuzzle_h__
