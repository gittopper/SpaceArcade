//
//  glesspacegamerenderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#ifndef __SpaceArcade__glesspacegamerenderer__
#define __SpaceArcade__glesspacegamerenderer__

#include "game/objects/gameobjects.h"
#include "glesrenderer.h"
#include "spacegamerenderer.h"

namespace Game {
class GLESSpaceGameRenderer : virtual public SpaceGameRenderer,
                              virtual public GLESRenderer {
   public:
    void visit(IObject&);

   protected:
    void drawGameObject(IObject& obj) const;
    void setPosition(const Mat& m, const Vector& v) const;
    void drawArray(VArray& points, V4Array& colors) const;
};
}  // namespace Game

#endif /* defined(__SpaceArcade__glesspacegamerenderer__) */
