//
//  rendererfactory.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "rendererfactory.h"
#include "glesspacegamerenderer.h"

namespace Game
{
    SpaceGameRenderer* RendererFactory::getGLESRenderer()
    {
        static GLESSpaceGameRenderer renderer;
        return &renderer;
    }
}
