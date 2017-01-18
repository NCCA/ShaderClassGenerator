
#ifndef ABSTRACTSHADERPROGRAM_H_
#define ABSTRACTSHADERPROGRAM_H_

#if defined (__linux__) || defined (WIN32)
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif
#ifdef __APPLE__
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
#endif



class AbstractShaderProgram
{
public :
  ~AbstractShaderProgram();

  static void bind();

  static void unbind();

  static GLuint getProgramID()  {return s_id;}
 protected:
  virtual bool createShaderProgram()=0;
  AbstractShaderProgram();
  void checkCompilationError(GLuint _id);
  void checkLinkerError();
  void link();
  void createShader(GLenum _type, const char * _source);
  static GLuint s_id;
};



#endif


