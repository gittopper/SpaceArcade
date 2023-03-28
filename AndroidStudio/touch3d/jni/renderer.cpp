#include "renderer.h"

static const char  glVertexShader[] = R"(
attribute vec4 vertexPosition;
attribute vec3 vertexColour;
/* [Add a vertex normal attribute.] */
attribute vec3 vertexNormal;
/* [Add a vertex normal attribute.] */
varying vec3 fragColour;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
/* [Setup scene vectors.] */
    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    fragColour = vec3(0.0);
/* [Setup scene vectors.] */

/* [Calculate the diffuse component.] */
    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexDiffuseReflectionConstant = vertexColour;
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    fragColour += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;
/* [Calculate the diffuse component.] */

/* [Calculate the ambient component.] */
    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);
    vec3 vertexAmbientReflectionConstant = vertexColour;
    fragColour += vertexAmbientReflectionConstant * ambientLightIntensity;
/* [Calculate the ambient component.] */

/* [Calculate the specular component.] */
    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    //fragColour += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;
/* [Calculate the specular component.] */

    /* Make sure the fragment colour is between 0 and 1. */
    clamp(fragColour, 0.0, 1.0);

    gl_Position = projection * modelView * vertexPosition;
}
)";
/* [vertexShader] */

/* [vertexShader] */
/*
static const char  glVertexShader[] = R"(
    attribute vec4 vertexPosition;
    attribute vec3 vertexColour;
    varying vec3 fragColour;
    uniform mat4 projection;
    uniform mat4 modelView;
    void main()
    {
        gl_Position = projection * modelView * vertexPosition;
        fragColour = vertexColour;
    }
)";
*/
/* [vertexShader] */

/* [fragmentShader] */
static const char  glFragmentShader[] = R"(
    precision mediump float;
    varying vec3 fragColour;
    void main()
    {
        gl_FragColor = vec4(fragColour, 1.0);
    }
)";
/* [fragmentShader] */

GLuint Renderer::loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0)
            {
                char * logBuffer = (char*) malloc(infoLen);

                if (logBuffer != NULL)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint Renderer::createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0)
    {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program != 0)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if(linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength > 0)
            {
                char* logBuffer = (char*) malloc(bufLength);

                if (logBuffer != NULL)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                    LOGE("Could not link program:\n%s\n", logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

void Renderer::setup() {
    simpleCubeProgram = createProgram(glVertexShader, glFragmentShader);

    if (simpleCubeProgram == 0)
    {
        LOGE ("Could not create program");
    }
    glUseProgram(simpleCubeProgram);

    vertexLocation = glGetAttribLocation(simpleCubeProgram, "vertexPosition");
    vertexColourLocation = glGetAttribLocation(simpleCubeProgram, "vertexColour");
    projectionLocation = glGetUniformLocation(simpleCubeProgram, "projection");
    vertexNormalLocation = glGetAttribLocation(simpleCubeProgram, "vertexNormal");
    modelViewLocation = glGetUniformLocation(simpleCubeProgram, "modelView");
}

void Renderer::setSize(int width, int height) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    camera_.setup(width, height);
}
void Renderer::startFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera_.render();
}

void Renderer::render(GLfloat* vertices, GLfloat*normals, GLfloat* colors, GLushort* indices, int size)
{
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(vertexColourLocation);
    glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glEnableVertexAttribArray(vertexNormalLocation);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, camera_.projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, camera_.modelViewMatrix);

    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, indices);
}
