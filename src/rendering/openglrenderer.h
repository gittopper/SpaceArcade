#pragma once

#include "spacegamerenderer.h"
#include "game/objects/gameobjects.h"

namespace Game
{
    class OpenGLRenderer:public SpaceGameRenderer
    {
    public:
        OpenGLRenderer();
        void visit(IObject&);
        void createFramebuffer();
        void destroyFramebuffer();
        bool updateInfoAboutWindow();

        void prepareFrame();
        void showFrame();

        void getScreeenSize(int& w, int& h);
        void setScreeenSize(int& w, int& h);
        void setScale(float s);

        bool initRenderer(ResourceLoader* loader);
    protected:
        void drawGameObject(IObject& obj) const;
        int width = 500;
        int height = 500;
    };
}
