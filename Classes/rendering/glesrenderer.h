//
//  glesrenderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_glesrenderer_h
#define Shader_glesrenderer_h

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>

#include "renderer.h"
#include "gamemath.h"

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
    void setScale(float s);
    
    bool initRenderer();
    
    void setResourcesPath(string path);
protected:
    bool readFile(uint8_t* buffer, int bufferSize, string filename);
    int loadShader(GLenum type, const uint8_t* source);
    bool compileShader();
    
    int shaderProgram;
    int a_positionHandle;
    int a_colorHandle;
    int u_mvpHandle;
    
    float scale;
    Mat44 proj;
    string resourcesPath;

    /* The pixel dimensions of the backbuffer */
    GLint backingWidth;
    GLint backingHeight;
    
    GLuint viewRenderbuffer, viewFramebuffer;
    GLuint depthRenderbuffer;
};

#endif
