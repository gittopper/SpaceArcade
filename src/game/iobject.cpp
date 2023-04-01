//
//  object3d.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "iobject.h"

namespace Game {
IObject::IObject()
    : parent_(nullptr), radius_(1.), box_(1.), shouldBeRemoved(false) {}

void IObject::move(const Vector& s) {
    shift_ += s;
    box_.move(s);
}

void IObject::rotate(const Mat& r) { rot_ = r * rot_; }

void IObject::scale(float s) {
    radius_ *= s;
    box_.move(-shift_);
    box_.scale(s);
    box_.move(shift_);
}

void IObject::addChild(IObject* child) {
    child->parent_ = this;
    children_.insert(child);
}

void IObject::removeChild(IObject* child) {
    children_.erase(child);
    delete child;
}
void IObject::removeChildren() {
    for (set<IObject*>::iterator it = children_.begin(); it != children_.end();
         it++) {
        (*it)->removeChildren();
        delete (*it);
    }
    children_.clear();
}
IObject::~IObject() { removeChildren(); }

void IObject::visitAll(Visitor& v) {
    const char* objName = name();
    accept(v);

    const ObjectsSet& children = getChildren();
    for (ObjectsSet::iterator it = children.begin(); it != children.end();
         it++) {
        (*it)->visitAll(v);
    }
}

bool IObject::intersects(IObject* other) {
    return getBBox().intersects(other->getBBox()) ||
           other->getBBox().intersects(getBBox());
}

float IObject::distance(IObject* other) {
    return std::max(this->getBBox().dist(other->getBBox()),
                    other->getBBox().dist(this->getBBox()));
}

bool IObject::contains(IObject* other) {
    return getBBox().isInside(other->getBBox());
}

void IObject::normalize() {
    centralize(points_);
    Math::scale(points_, 1. / maxRadius(points_));
    cacheDrawPoints();
    radius_ = 1.;
}
void IObject::cacheDrawPoints() {
    drawPoints_.clear();
    drawPoints_.push_back(centerMass(points_));
    drawPoints_.insert(drawPoints_.end(), points_.begin(), points_.end());
    colors_ = generateArray(Vector4(color_[0], color_[1], color_[2], 1),
                            (int)drawPoints_.size());
}
IGame* IObject::game = nullptr;

void removePostponed(IObject* obj) {
    ObjectsSet s;

    for (ObjectsSet::const_iterator it = obj->getChildren().begin();
         it != obj->getChildren().end(); it++) {
        if ((*it)->shouldBeRemoved) {
            s.insert(*it);
        }
    }
    for (ObjectsSet::const_iterator it = s.begin(); it != s.end(); it++) {
        (*it)->getParent()->removeChild(*it);
    }
}
}  // namespace Game
