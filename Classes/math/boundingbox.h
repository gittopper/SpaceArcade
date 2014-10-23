//
//  boundingbox.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__boundingbox__
#define __SpaceArcade__boundingbox__

#include "vector.h"

namespace Math
{

    class BoundingBox2D
    {
    public:
        void merge(const Vector& v);
        BoundingBox2D(const VArray& v);
        BoundingBox2D(float size):vMin(-size/2.,-size/2.),vMax(size/2,size/2){}
        BoundingBox2D(float width, float height):vMin(-width/2.,-height/2.),vMax(width/2.,height/2.){}

        float getXDim() const { return vMax[0] - vMin[0]; }
        float getYDim() const { return vMax[1] - vMin[1]; }
        float getZDim() const { return vMax[2] - vMin[2]; }
        float getMaxDim() const { return max(getXDim(), getYDim()); }
        
        void scale(float s);
        void move(Vector v);
        
        const Vector& getMin() const { return vMin; }
        const Vector& getMax() const { return vMax; }

        BoundingBox2D operator+(const Vector& v) const { return BoundingBox2D(vMin + v, vMax + v);}
        
        bool isInside(const Vector&v) const { return vMin[0] <= v[0] && vMin[1] <= v[1] && vMax[0] >=v[0] && vMax[1] >=v[1];}
        bool isInside(const BoundingBox2D&v) const { return isInside(v.vMin) && isInside(v.vMax);}
        
        bool intersects(const BoundingBox2D&v) const { return isInside(v.vMin) || isInside(v.vMax);}
        
        
        static BoundingBox2D getCube(float s)
        {
            Vector v(s,s,s);
            
            
            return BoundingBox2D(-v,v);
        }
    private:
        BoundingBox2D(Vector a, Vector b):vMin(a),vMax(b){}
        Vector vMin, vMax;
    };
    
}
#endif /* defined(__SpaceArcade__boundingbox__) */
