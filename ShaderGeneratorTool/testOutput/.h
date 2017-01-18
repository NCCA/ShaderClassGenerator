#ifndef _H_
#define _H_

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
class  : public AbstractShaderProgram 
#endif