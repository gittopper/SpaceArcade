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
#include <rendering/spacegamerenderer.h>

namespace Game {
class GLESSpaceGameRenderer : virtual public SpaceGameRenderer,
                              virtual public GLESRenderer {
   public:
    void visit(IObject&) override;

   protected:
    void drawGameObject(IObject& obj) const;
    void setPosition(const Mat& m, const Vector& v) const;
    void drawArray(VArray& points, V4Array& colors) const;
    void drawSprite(
            int x, int y, int w, int h, int pixel_size, const RGBAPixel* sprite) override;
};
}  // namespace Game

#endif /* defined(__SpaceArcade__glesspacegamerenderer__) */
