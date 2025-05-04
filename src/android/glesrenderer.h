#pragma once


#ifndef __APPLE__
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#endif

#include <memory>

#include <math/gamemath.h>
#include <rendering/renderer.h>

using namespace std;
using namespace Math;

class GLESRenderer : virtual public Renderer {
   public:
    GLESRenderer();
    void createFramebuffer() override;
    void destroyFramebuffer() override;
    bool updateInfoAboutWindow() override;

    void prepareFrame() override;
    void showFrame() override;

    void getScreeenSize(int& w, int& h) override;
    void setScreeenSize(int w, int h) override;
    void setScale(float s) override;

    bool initRenderer(ResourceLoader* loader) override;

   protected:

    std::uint32_t program_overlay_id_;
    std::uint32_t overlay_vert_loc_;
    std::uint32_t overlay_tex_loc_;
    std::uint32_t overlay_mat_loc_;

    std::uint32_t program_id_;
    std::uint32_t a_positionHandle_;
    std::uint32_t a_colorHandle_;
    std::uint32_t u_mvpHandle_;

    float scale_;
    Mat44 proj_;

    /* The pixel dimensions of the backbuffer */
    GLint backingWidth_;
    GLint backingHeight_;

    GLuint viewRenderbuffer_, viewFramebuffer_;
    GLuint depthRenderbuffer_;
};

