//
//  iboject.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//


#ifndef _IObject_h_
#define _IObject_h_


#include "math/gamemath.h"
#include <set>
#include "regressvisitor.h"
#include "math/mathutils.h"
#include "igame.h"

using namespace Math;
using namespace std;

#define GAME_OBJECT(o) virtual const char* name(){return #o;}

namespace Game
{
    class IObject;
    
    
    typedef set<IObject*> ObjectsSet;
//    typedef vector<float> FArray;
    
    class IObject:public RegressVisitor
    {
    public:
        IObject();
        
        virtual ~IObject();
    
        GAME_OBJECT(IObject)
        
        void move(const Vector& shift);

        void rotate(const Mat& rot);
    
        void scale(float s);
    
        void addChild(IObject* child);

        IObject* getParent() const { return parent;}
        const ObjectsSet& getChildren() const { return children;}

        void removeChild(IObject* child);
        void removeChildren();
    
        Mat getTransform() const { return rot * radius;}
        const Vector& getShift() const { return shift;}
        
        const float getMass() const { return mass;}
        Vector& getV() { return velocity;}
        
        VArray& getPoints() { return points;}
        VArray& getDrawPoints() { return drawPoints;}
        V4Array& getColors() { return colors;}
        //should be defined for the implementation only
        
        virtual void accept(Visitor& v) = 0;
        
        void visitAll(Visitor& v);
        
        void getProcessedPoints(VArray& result) { applyTransformsToPoints(result, points, getTransform(), shift);}
        void normalize();
        
        bool intersects(IObject* other);
        bool contains(IObject* other);
        BoundingBox2D& getBBox()
        {
            return box;
        }
        
        
        bool shouldBeRemoved;

        
        static IGame* game;
        void cacheDrawPoints();
    protected:

        Mat rot;
        Vector shift;
        float radius;
        BoundingBox2D box;
        
        float mass;
        Vector velocity;

        IObject* parent;
        ObjectsSet children;
        
        Vector color;
        
        VArray points, drawPoints;
        V4Array colors;
        
    };
    
    
    void removePostponed(IObject* obj);
}
#endif
