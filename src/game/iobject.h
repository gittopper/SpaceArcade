//
//  iboject.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef _IObject_h_
#define _IObject_h_

#include <set>

#include "igame.h"
#include "math/gamemath.h"
#include "math/mathutils.h"
#include "regressvisitor.h"

using namespace Math;
using namespace std;

#define GAME_OBJECT(o) \
    virtual const char* name() { return #o; }

namespace Game {
class IObject;

typedef set<IObject*> ObjectsSet;
//    typedef vector<float> FArray;

class IObject : public RegressVisitor {
   public:
    IObject();

    virtual ~IObject();

    GAME_OBJECT(IObject)

    void move(const Vector& shift);

    void rotate(const Mat& rot);

    void scale(float s);

    void addChild(IObject* child);

    IObject* getParent() const { return parent_; }
    const ObjectsSet& getChildren() const { return children_; }

    void removeChild(IObject* child);
    void removeChildren();

    Mat getTransform() const { return rot_ * radius_; }
    const Vector& getShift() const { return shift_; }

    const float getMass() const { return mass_; }
    Vector& getV() { return velocity_; }

    VArray& getPoints() { return points_; }
    VArray& getDrawPoints() { return drawPoints_; }
    V4Array& getColors() { return colors_; }
    // should be defined for the implementation only

    virtual void accept(Visitor& v) = 0;

    void visitAll(Visitor& v);

    void getProcessedPoints(VArray& result) {
        applyTransformsToPoints(result, points_, getTransform(), shift_);
    }
    void normalize();

    bool intersects(IObject* other);
    bool contains(IObject* other);
    BoundingBox2D& getBBox() { return box_; }

    bool shouldBeRemoved;

    static IGame* game;
    void cacheDrawPoints();

   protected:
    Mat rot_;
    Vector shift_;
    float radius_;
    BoundingBox2D box_;

    float mass_;
    Vector velocity_;

    IObject* parent_;
    ObjectsSet children_;

    Vector color_;

    VArray points_, drawPoints_;
    V4Array colors_;
};

void removePostponed(IObject* obj);
}  // namespace Game
#endif
