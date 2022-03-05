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

#include "renderer.h"
#include "math/gamemath.h"
#include <memory>

using namespace std;
using namespace Math;

class GLESRenderer:virtual public Renderer
{
public:
    GLESRenderer();
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
    int loadShader(GLenum type, const char* source);
    bool compileShader();
    unique_ptr<ResourceLoader> rcLoader;
    
    int shaderProgram;
    int a_positionHandle;
    int a_colorHandle;
    int u_mvpHandle;
    
    float scale;
    Mat44 proj;

    /* The pixel dimensions of the backbuffer */
    GLint backingWidth;
    GLint backingHeight;
    
    GLuint viewRenderbuffer, viewFramebuffer;
    GLuint depthRenderbuffer;
};

#endif
