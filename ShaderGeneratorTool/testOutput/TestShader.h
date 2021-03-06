#ifndef TESTSHADER_H_
#define TESTSHADER_H_

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
class TestShader : public AbstractShaderProgram 
{
	public :
		static std::unique_ptr<TestShader> getShader();
		void setlight_quadraticAttenuation(GLfloat _1); const
		void setlight_linearAttenuation(GLfloat _1); const
		void setlight_spotCosInnerCutoff(GLfloat _1); const
		void setlight_specular(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setlight_diffuse(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setlight_ambient(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setMVP(const GLfloat *value); const
		void setlight_constantAttenuation(GLfloat _1); const
		void setlight_spotExponent(GLfloat _1); const
		void setNormalize(GLint _1); const
		void setColour(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setlight_direction(GLfloat _1, GLfloat _2, GLfloat _3); const
		void setmaterial_specular(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setnormalMatrix(const GLfloat *value); const
		void setMV(const GLfloat *value); const
		void setmaterial_shininess(GLfloat _1); const
		void setM(const GLfloat *value); const
		void setmaterial_diffuse(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setviewerPos(GLfloat _1, GLfloat _2, GLfloat _3); const
		void setlight_spotCosCutoff(GLfloat _1); const
		void setmaterial_ambient(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
		void setlight_position(GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4); const
	private :
		TestShader();
		static GLint s_light_quadraticAttenuation;
		static GLint s_light_linearAttenuation;
		static GLint s_light_spotCosInnerCutoff;
		static GLint s_light_specular;
		static GLint s_light_diffuse;
		static GLint s_light_ambient;
		static GLint s_MVP;
		static GLint s_light_constantAttenuation;
		static GLint s_light_spotExponent;
		static GLint s_Normalize;
		static GLint s_Colour;
		static GLint s_light_direction;
		static GLint s_material_specular;
		static GLint s_normalMatrix;
		static GLint s_MV;
		static GLint s_material_shininess;
		static GLint s_M;
		static GLint s_material_diffuse;
		static GLint s_viewerPos;
		static GLint s_light_spotCosCutoff;
		static GLint s_material_ambient;
		static GLint s_light_position;
};
#endif