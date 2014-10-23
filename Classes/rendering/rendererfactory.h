//
//  rendererfactory.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#ifndef __SpaceArcade__rendererfactory__
#define __SpaceArcade__rendererfactory__

#include "spacegamerenderer.h"

namespace Game
{
    
    class RendererFactory
    {
    public:
        static SpaceGameRenderer* getGLESRenderer();
    };
    
}
#endif /* defined(__SpaceArcade__rendererfactory__) */
