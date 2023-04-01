//
//  glesrenderer.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "glesrenderer.h"

#define USE_DEPTH_BUFFER 0

GLESRenderer::GLESRenderer() : scale_(1) {}

int GLESRenderer::loadShader(GLenum type, const char* source) {
    const unsigned int shader = glCreateShader(type);
    if (shader == 0) return 0;

    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        char errorMsg[2048];
        glGetShaderInfoLog(shader, sizeof(errorMsg), NULL, errorMsg);
        printf("Compile error: %s\n", errorMsg);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

bool GLESRenderer::initRenderer(ResourceLoader* loader) {
    unique_ptr<ResourceLoader> tmpLoader(loader);
    rcLoader_ = std::move(tmpLoader);
    if (!compileShader()) return false;
    glUseProgram(shaderProgram_);
    return true;
}

void GLESRenderer::getScreeenSize(int& w, int& h) {
    w = backingWidth_;
    h = backingHeight_;
}
void GLESRenderer::setScreeenSize(int w, int h) {
    backingWidth_ = w;
    backingHeight_ = h;
}

bool GLESRenderer::compileShader() {
    unique_ptr<char> vertFile(rcLoader_->readFile("vertex_shader.txt"));
    if (!vertFile) return false;
    const int vertexShader = loadShader(GL_VERTEX_SHADER, &(*vertFile));
    if (vertexShader == 0) return false;

    unique_ptr<char> fragFile(rcLoader_->readFile("fragment_shader.txt"));
    if (!fragFile) return false;
    const int fragmentShader = loadShader(GL_FRAGMENT_SHADER, &(*fragFile));
    if (fragmentShader == 0) return false;

    shaderProgram_ = glCreateProgram();
    if (shaderProgram_ == 0) return false;

    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    glLinkProgram(shaderProgram_);
    int linked;
    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &linked);
    if (linked == 0) {
        glDeleteProgram(shaderProgram_);
        return false;
    }

    a_positionHandle_ = glGetAttribLocation(shaderProgram_, "a_position");
    a_colorHandle_ = glGetAttribLocation(shaderProgram_, "a_color");

    u_mvpHandle_ = glGetUniformLocation(shaderProgram_, "u_mvpMatrix");

    return true;
}

void GLESRenderer::createFramebuffer() {
    glGenFramebuffers(1, &viewFramebuffer_);
    glGenRenderbuffers(1, &viewRenderbuffer_);

    glBindFramebuffer(GL_FRAMEBUFFER_OES, viewFramebuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER_OES, viewRenderbuffer_);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
                              GL_RENDERBUFFER_OES, viewRenderbuffer_);
}
bool GLESRenderer::updateInfoAboutWindow() {
    glGetRenderbufferParameteriv(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES,
                                 &backingWidth_);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER_OES,
                                 GL_RENDERBUFFER_HEIGHT_OES, &backingHeight_);

    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffers(1, &depthRenderbuffer_);
        glBindRenderbuffer(GL_RENDERBUFFER_OES, depthRenderbuffer_);
        glRenderbufferStorage(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES,
                              backingWidth_, backingHeight_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES,
                                  GL_RENDERBUFFER_OES, depthRenderbuffer_);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER_OES) !=
        GL_FRAMEBUFFER_COMPLETE_OES) {
        return false;
    }

    return true;
}

void GLESRenderer::prepareFrame() {
    float aspect = (float)backingHeight_ / backingWidth_;

    float hs = scale_ / 2;

    SetOrtho(proj_, -hs, hs, -aspect * hs, aspect * hs, -scale_, scale_);

    glBindFramebuffer(GL_FRAMEBUFFER_OES, viewFramebuffer_);
    glViewport(0, 0, backingWidth_, backingHeight_);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLESRenderer::setScale(float s) { scale_ = s; }

void GLESRenderer::showFrame() {
    glBindRenderbuffer(GL_RENDERBUFFER_OES, viewRenderbuffer_);
}

void GLESRenderer::destroyFramebuffer() {
    glDeleteFramebuffers(1, &viewFramebuffer_);
    viewFramebuffer_ = 0;
    glDeleteRenderbuffers(1, &viewRenderbuffer_);
    viewRenderbuffer_ = 0;

    if (USE_DEPTH_BUFFER) {
        glDeleteRenderbuffers(1, &depthRenderbuffer_);
        depthRenderbuffer_ = 0;
    }
}
