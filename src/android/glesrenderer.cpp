#include <android/glesrenderer.h>

#define USE_DEPTH_BUFFER 0

namespace {
std::uint32_t loadShader(GLenum type, const char* source) {
    auto shader = glCreateShader(type);
    if (shader == 0) {
        throw std::runtime_error("cannot create shader");
    }

    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        char errorMsg[2048];
        glGetShaderInfoLog(shader, sizeof(errorMsg), NULL, errorMsg);
        glDeleteShader(shader);
        throw std::runtime_error(
            std::string("cannot create shader, error message is ") + errorMsg);
    }

    return shader;
}

std::uint32_t compileProgram(ResourceLoader* loader,
                             const std::string& vertex_shader_name,
                             const std::string& fragment_shader_name) {
    auto vertex_shader_txt = loader->readFile(vertex_shader_name);
    if (vertex_shader_txt.empty()) {
        throw std::runtime_error("cannot read vertex shader");
    }
    vertex_shader_txt.resize(vertex_shader_txt.size() + 1);
    vertex_shader_txt[vertex_shader_txt.size() - 1] = '\0';
    const int vertexShader =
        loadShader(GL_VERTEX_SHADER, vertex_shader_txt.data());
    if (vertexShader == 0) {
        throw std::runtime_error("cannot load vertex shader");
    }

    auto fragment_shader_txt = loader->readFile(fragment_shader_name);
    if (fragment_shader_txt.empty()) {
        throw std::runtime_error("cannot read fragment shader");
    }
    fragment_shader_txt.resize(fragment_shader_txt.size() + 1);
    fragment_shader_txt[fragment_shader_txt.size() - 1] = '\0';
    const int fragmentShader =
        loadShader(GL_FRAGMENT_SHADER, fragment_shader_txt.data());
    if (fragmentShader == 0) {
        throw std::runtime_error("cannot load fragment shader");
    }

    auto program_id = glCreateProgram();
    if (program_id == 0) {
        throw std::runtime_error("cannot create program");
    }
    glAttachShader(program_id, vertexShader);
    glAttachShader(program_id, fragmentShader);
    glLinkProgram(program_id);
    int linked;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
    if (linked == 0) {
        glDeleteProgram(program_id);
        throw std::runtime_error("cannot link program");
    }

    return program_id;
}
}  // namespace

GLESRenderer::GLESRenderer() : scale_(1) {}

bool GLESRenderer::initRenderer(ResourceLoader* loader) {
    program_overlay_id_ =
        compileProgram(loader, "sprite_vs.txt", "sprite_fs.txt");
    glUseProgram(program_overlay_id_);
    overlay_vert_loc_ = glGetAttribLocation(program_overlay_id_, "a_Position");
    overlay_tex_loc_ =
        glGetAttribLocation(program_overlay_id_, "a_Texture");  // texture
    overlay_mat_loc_ =
        glGetUniformLocation(program_overlay_id_, "u_mvpMatrix");  // texture

    program_id_ =
        compileProgram(loader, "vertex_shader.txt", "fragment_shader.txt");
    glUseProgram(program_id_);
    a_positionHandle_ = glGetAttribLocation(program_id_, "a_position");
    a_colorHandle_ = glGetAttribLocation(program_id_, "a_color");

    u_mvpHandle_ = glGetUniformLocation(program_id_, "u_mvpMatrix");

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

    glUseProgram(program_id_);
}

void GLESRenderer::setScale(float s) {
    scale_ = s;
}

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
