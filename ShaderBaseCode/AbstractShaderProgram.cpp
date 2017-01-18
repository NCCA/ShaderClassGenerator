
#include "AbstractShaderProgram.h"
#include <memory>
#include <iostream>

GLuint AbstractShaderProgram::s_id=0;

AbstractShaderProgram::~AbstractShaderProgram()
{
 std::cerr<<"removeing shader\n";
 unbind();
 glDeleteProgram(s_id);
}
void AbstractShaderProgram::bind()
{
glUseProgram(s_id);
}

void AbstractShaderProgram::unbind()
{
glUseProgram(0);
}
AbstractShaderProgram::AbstractShaderProgram()
{
if(s_id ==0)
 s_id=glCreateProgram();
}

void AbstractShaderProgram::createShader(GLenum _type, const char * _source)
{
 // create a Vertex shader object
 GLuint shaderID=glCreateShader(_type);
 // attatch the shader source we need to convert to GL format
 glShaderSource(shaderID,1,&_source,NULL);
 // now compile the shader
 glCompileShader(shaderID);
 std::cerr<<"compiling  shader\n";
 checkCompilationError(shaderID);
 glAttachShader(s_id,shaderID);
 glDeleteShader(shaderID);

}

void AbstractShaderProgram::checkCompilationError(GLuint _id)
{
 GLint infologLength = 0;
 GLint charsWritten  = 0;

 glGetShaderiv(_id, GL_INFO_LOG_LENGTH,&infologLength);
 if(infologLength > 0)
 {
   std::unique_ptr<char []> infoLog(new char[infologLength]);
   glGetShaderInfoLog(_id, infologLength, &charsWritten, infoLog.get());

   std::cerr<<infoLog.get()<<'\n';

 }
}

void AbstractShaderProgram::checkLinkerError()
{
 GLint infologLength = 0;

 glGetProgramiv(s_id,GL_INFO_LOG_LENGTH,&infologLength);

 if(infologLength > 0)
 {
   std::unique_ptr<char []> infoLog ( new char[infologLength]);
   GLint charsWritten  = 0;

   glGetProgramInfoLog(s_id, infologLength, &charsWritten, infoLog.get());

   std::cerr<<infoLog.get()<<'\n';

   glGetProgramiv(s_id, GL_LINK_STATUS,&infologLength);
   if( infologLength == GL_FALSE)
   {
     std::cerr<<"Program link failed exiting \n";
     exit(EXIT_FAILURE);
   }
 }
}

void AbstractShaderProgram::link()
{
 glLinkProgram(s_id);
 checkLinkerError();
}


