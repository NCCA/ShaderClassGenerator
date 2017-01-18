#ifndef BASICSHADER_H_
#define BASICSHADER_H_

#if defined (__linux__) || defined (WIN32)
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif

#include "AbstractShaderProgram.h"
#include <memory>
#include <iostream>


// new BasicShader
class BasicShader : public AbstractShaderProgram
{
  public :
    static std::unique_ptr<BasicShader> getShader();
    static void setBaseColour(GLfloat _1, GLfloat _2, GLfloat _3);

  private :
    BasicShader();
    virtual bool createShaderProgram();
    static GLint s_baseColour;
};

#endif
