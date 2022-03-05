//
//  renderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef __SpaceArcade__renderer__
#define __SpaceArcade__renderer__

#include <string>
#include "resourceloader.h"

using namespace std;

class Renderer
{
public:
    virtual bool initRenderer(ResourceLoader* loader) = 0;
    
    virtual void createFramebuffer() = 0;
    virtual void destroyFramebuffer() = 0;
    virtual bool updateInfoAboutWindow() = 0;
    
    virtual void prepareFrame() = 0;
    virtual void showFrame() = 0;

    virtual void getScreeenSize(int& w, int& h) = 0;
    virtual void setScreeenSize(int& w, int& h) = 0;
    virtual void setScale(float s) = 0;
    
    virtual ~Renderer(){}
};
#endif /* defined(__SpaceArcade__renderer__) */
