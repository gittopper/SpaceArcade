//
//  glesrenderer.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "glesrenderer.h"

#define USE_DEPTH_BUFFER 0

GLESRenderer::GLESRenderer():
scale(1)
{

}

int GLESRenderer::loadShader(GLenum type, const char* source)
{
    const unsigned int shader = glCreateShader(type);
    if (shader == 0)
        return 0;
    
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);
    
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0)
    {
        char errorMsg[2048];
        glGetShaderInfoLog(shader, sizeof(errorMsg), NULL, errorMsg);
        printf("Compile error: %s\n", errorMsg);
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

bool GLESRenderer::initRenderer(ResourceLoader* loader)
{
    unique_ptr<ResourceLoader> tmpLoader(loader);
    rcLoader = std::move(tmpLoader);
    if (!compileShader()) return false;
    glUseProgram(shaderProgram);
    return true;
}

void GLESRenderer::getScreeenSize(int& w, int& h)
{
    w = backingWidth;
    h = backingHeight;
}
void GLESRenderer::setScreeenSize(int& w, int& h)
{
    backingWidth = w;
    backingHeight = h;
}

bool GLESRenderer::compileShader()
{
    unique_ptr<char> vertFile(rcLoader->readFile("vertex_shader.txt"));
    if (!vertFile)
        return false;
    const int vertexShader = loadShader (GL_VERTEX_SHADER, &(*vertFile));
    if (vertexShader == 0)
        return false;
    
    unique_ptr<char> fragFile(rcLoader->readFile("fragment_shader.txt"));
    if (!fragFile)
        return false;
    const int fragmentShader = loadShader (GL_FRAGMENT_SHADER, &(*fragFile));
    if (fragmentShader == 0)
        return false;
    
    shaderProgram = glCreateProgram();
    if (shaderProgram == 0)
        return false;
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if (linked == 0)
    {
        glDeleteProgram(shaderProgram);
        return false;
    }
    
    
    a_positionHandle = glGetAttribLocation(shaderProgram, "a_position");
    a_colorHandle = glGetAttribLocation(shaderProgram, "a_color");
    
    u_mvpHandle = glGetUniformLocation(shaderProgram, "u_mvpMatrix");
    
    
    return true;
}


void GLESRenderer::createFramebuffer()
{
    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
    
}
bool GLESRenderer::updateInfoAboutWindow()
{
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
        return false;
    }
    
    return true;
}

void GLESRenderer::prepareFrame()
{
    float aspect = (float)backingHeight / backingWidth;

    float hs = scale/2;
    
    SetOrtho(proj, -hs, hs,-aspect * hs, aspect*hs, -scale, scale);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glViewport(0, 0, backingWidth, backingHeight);
    
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
}

void GLESRenderer::setScale(float s)
{
    scale = s;
}

void GLESRenderer::showFrame()
{
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
}


void GLESRenderer::destroyFramebuffer()
{
    
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(USE_DEPTH_BUFFER) {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}
