//
//  object3d.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "iobject.h"

namespace Game
{
    IObject::IObject():
    parent(NULL),
    radius(1.),
    box(1.),
    shouldBeRemoved(false)
    {
    }

    
    void IObject::move(const Vector& s)
   	 {
        shift += s;
        box.move(s);
    }

    void IObject::rotate(const Mat& r)
    {
        rot = r * rot;
    }

    
    void IObject::scale(float s)
    {
        radius *= s;
        box.move(-shift);
        box.scale(s);
        box.move(shift);
    }


    void IObject::addChild(IObject* child)
    {
        child->parent = this;
        children.insert(child);
    }
    
    void IObject::removeChild(IObject* child)
    {
        children.erase(child);
        delete child;
    }
    void IObject::removeChildren()
    {
        for(set<IObject*>::iterator it = children.begin(); it != children.end(); it ++)
        {
            (*it)->removeChildren();
            delete (*it);
        }
        children.clear();
    }
    IObject::~IObject()
    {
        removeChildren();
    }
    
    void IObject::visitAll(Visitor& v)
    {
        const char* objName = name();
        accept(v);
        
        const ObjectsSet& children = getChildren();
        for(ObjectsSet::iterator it = children.begin();it != children.end();it++)
        {
            (*it)->visitAll(v);
        }
    }

    bool IObject::intersects(IObject* other)
    {
        return getBBox().intersects(other->getBBox()) || other->getBBox().intersects(getBBox());
    }
    
    bool IObject::contains(IObject* other)
    {
        return getBBox().isInside(other->getBBox());
    }

    void IObject::normalize()
    {
        centralize(points);
        Math::scale(points, 1./maxRadius(points));
        cacheDrawPoints();
        radius = 1.;
    }
    void IObject::cacheDrawPoints()
    {
        drawPoints.clear();
        drawPoints.push_back(centerMass(points));
        drawPoints.insert(drawPoints.end(), points.begin(), points.end());
        colors = generateArray(Vector4(color[0], color[1], color[2], 1), (int) drawPoints.size());
    }
    IGame* IObject::game = NULL;

    void removePostponed(IObject* obj)
    {
        ObjectsSet s;

        for(ObjectsSet::const_iterator it = obj->getChildren().begin();it != obj->getChildren().end();it++)
        {
            if((*it)->shouldBeRemoved)
            {
                s.insert(*it);
            }
        }
        for(ObjectsSet::const_iterator it = s.begin();it != s.end();it++)
        {
            (*it)->getParent()->removeChild(*it);
        }
    }
}