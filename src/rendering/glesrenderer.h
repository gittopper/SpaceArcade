//
//  glesrenderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_glesrenderer_h
#define Shader_glesrenderer_h

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

#include "math/gamemath.h"
#include "renderer.h"

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
    int loadShader(GLenum type, const char* source);
    bool compileShader();
    unique_ptr<ResourceLoader> rcLoader_;

    int shaderProgram_;
    int a_positionHandle_;
    int a_colorHandle_;
    int u_mvpHandle_;

    float scale_;
    Mat44 proj_;

    /* The pixel dimensions of the backbuffer */
    GLint backingWidth_;
    GLint backingHeight_;

    GLuint viewRenderbuffer_, viewFramebuffer_;
    GLuint depthRenderbuffer_;
};

#endif
