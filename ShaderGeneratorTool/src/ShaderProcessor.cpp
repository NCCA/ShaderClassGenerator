#include "ShaderProcessor.h"
#include <ngl/ShaderLib.h>
#include "ngl/fmt/format.h"
#include "AbstractShaderGenerator.h"
#include <fstream>
#include <algorithm>
#include <regex>
ShaderProcessor::ShaderProcessor()
{

}

bool ShaderProcessor::loadShader(const std::string &_path, ShaderType _type)
{
  Shader s;
  s.sourcePath=_path;
  s.active=true;
  m_shaders[static_cast<size_t>(_type)]=s;
  return true;
}

void ShaderProcessor::setProgramName(const std::string &_name)
{
  m_shaderProgramName=_name;
}


void ShaderProcessor::createShaderProgram()
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->loadShader(m_shaderProgramName,
                     m_shaders[static_cast<size_t>(ShaderType::Vertex)].sourcePath,
                     m_shaders[static_cast<size_t>(ShaderType::Fragment)].sourcePath
      );
  processUniforms();
  generateStringsFromUniforms();

}

void ShaderProcessor::generateStringsFromUniforms()
{
  for(auto p : m_registeredUniforms)
  {
    defineFunctionString(p.second);
  }
}

void ShaderProcessor::defineFunctionString(const uniformData &_p)
{
  std::string func("void set");


  func+=regex_replace(_p.name, std::regex("[.]+"), "_");
  func+='(';
  writeParams(_p.type,func);
  func+="); const";
  m_classPublicData.push_back(func);
}

void ShaderProcessor::writeParams( GLenum _p, std::string &io_func)
{
  switch (_p)
  {
    case GL_FLOAT       : io_func+="GLfloat _1"; break;
    case GL_FLOAT_VEC2 :  io_func+="GLfloat _1, GLfloat _2"; break;
    case GL_FLOAT_VEC3 :  io_func+="GLfloat _1, GLfloat _2, GLfloat _3"; break;
    case GL_FLOAT_VEC4 :  io_func+="GLfloat _1, GLfloat _2, GLfloat _3, GLfloat _4"; break;

    case GL_DOUBLE       : io_func+="GLdouble _1"; break;
    case GL_DOUBLE_VEC2 :  io_func+="GLdouble _1, GLdouble _2"; break;
    case GL_DOUBLE_VEC3 :  io_func+="GLdouble _1, GLdouble _2, GLdouble _3"; break;
    case GL_DOUBLE_VEC4 :  io_func+="GLdouble _1, GLdouble _2, GLdouble _3, GLdouble _4"; break;


    case GL_INT :
    case GL_BOOL :         io_func+="GLint _1"; break;

    case GL_INT_VEC2 :    io_func+="GLint _1, GLint _2"; break;
    case GL_INT_VEC3 :    io_func+="GLint _1, GLint _2, GLint _3"; break;
    case GL_INT_VEC4 :  io_func+="GLint _1, GLint _2, GLint _3, GLint _4"; break;


    case GL_FLOAT_MAT2 :
    case GL_FLOAT_MAT3 :
    case GL_FLOAT_MAT4 :

                          io_func+="const GLfloat *value";
    break;
  }
}

const static std::unordered_map<GLenum,const char *> GLtypes=
{
  {GL_FLOAT,"float"},
  {GL_FLOAT_VEC2,"vec2"},
  {GL_FLOAT_VEC3,"vec3"},
  {GL_FLOAT_VEC4,"vec4"},
#ifndef USINGIOS_
  {GL_DOUBLE,"double"},
  {GL_DOUBLE_VEC2,"dvec2"},
  {GL_DOUBLE_VEC3,"dvec3"},
  {GL_DOUBLE_VEC4,"dvec4"},
#endif
  {GL_INT,"int"},
  {GL_INT_VEC2,"ivec2"},
  {GL_INT_VEC3,"ivec3"},
  {GL_INT_VEC4,"ivec4"},
  {GL_UNSIGNED_INT,"unsigned int"},
  {GL_UNSIGNED_INT_VEC2,"uvec2"},
  {GL_UNSIGNED_INT_VEC3,"uvec3"},
  {GL_UNSIGNED_INT_VEC4,"uvec4"},
  {GL_BOOL,"bool"},
  {GL_BOOL_VEC2,"bvec2"},
  {GL_BOOL_VEC3,"bvec3"},
  {GL_BOOL_VEC4,"bvec4"},
  {GL_FLOAT_MAT2,"mat2"},
  {GL_FLOAT_MAT3,"mat3"},
  {GL_FLOAT_MAT4,"mat4"},
  {GL_FLOAT_MAT2x3,"mat2x3"},
  {GL_FLOAT_MAT2x4,"mat2x4"},
  {GL_FLOAT_MAT3x2,"mat3x2"},
  {GL_FLOAT_MAT3x4,"mat3x4"},
  {GL_FLOAT_MAT4x2,"mat4x2"},
  {GL_FLOAT_MAT4x3,"mat4x3"},
#ifndef USINGIOS_
  {GL_DOUBLE_MAT2,"dmat2"},
  {GL_DOUBLE_MAT3,"dmat3"},
  {GL_DOUBLE_MAT4,"dmat4"},
  {GL_DOUBLE_MAT2x3,"dmat2x3"},
  {GL_DOUBLE_MAT2x4,"dmat2x4"},
  {GL_DOUBLE_MAT3x2,"dmat3x2"},
  {GL_DOUBLE_MAT3x4,"dmat3x4"},
  {GL_DOUBLE_MAT4x2,"dmat4x2"},
  {GL_DOUBLE_MAT4x3,"dmat4x3"},
  {GL_SAMPLER_1D,"sampler1D"},
  {GL_SAMPLER_1D_SHADOW,"sampler1DShadow"},
  {GL_SAMPLER_1D_ARRAY,"sampler1DArray"},
  {GL_SAMPLER_1D_ARRAY_SHADOW,"sampler1DArrayShadow"},
  {GL_SAMPLER_2D_MULTISAMPLE,"sampler2DMS"},
  {GL_SAMPLER_2D_MULTISAMPLE_ARRAY,"sampler2DMSArray"},
  {GL_SAMPLER_BUFFER,"samplerBuffer"},
  {GL_SAMPLER_2D_RECT,"sampler2DRect"},
  {GL_SAMPLER_2D_RECT_SHADOW,"sampler2DRectShadow"},
  {GL_INT_SAMPLER_1D,"isampler1D"},
  {GL_INT_SAMPLER_1D_ARRAY,"isampler1DArray"},
  {GL_INT_SAMPLER_2D_MULTISAMPLE,"isampler2DMS"},
  {GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"isampler2DMSArray"},
  {GL_INT_SAMPLER_BUFFER,"isamplerBuffer"},
  {GL_INT_SAMPLER_2D_RECT,"isampler2DRect"},
  {GL_UNSIGNED_INT_SAMPLER_1D,"usampler1D"},
  {GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,"usampler2DArray"},
  {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,"usampler2DMS"},
  {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"usampler2DMSArray"},
  {GL_UNSIGNED_INT_SAMPLER_BUFFER,"usamplerBuffer"},
  {GL_UNSIGNED_INT_SAMPLER_2D_RECT,"usampler2DRect"},
  {GL_IMAGE_1D,"image1D"},
  {GL_IMAGE_2D,"image2D"},
  {GL_IMAGE_3D,"image3D"},
  {GL_IMAGE_2D_RECT,"image2DRect"},
  {GL_IMAGE_CUBE,"imageCube"},
  {GL_IMAGE_BUFFER,"imageBuffer"},
  {GL_IMAGE_1D_ARRAY,"image1DArray"},
  {GL_IMAGE_2D_ARRAY,"image2DArray"},
  {GL_IMAGE_2D_MULTISAMPLE,"image2DMS"},
  {GL_IMAGE_2D_MULTISAMPLE_ARRAY,"image2DMSArray"},
  {GL_INT_IMAGE_1D,"iimage1D"},
  {GL_INT_IMAGE_2D,"iimage2D"},
  {GL_INT_IMAGE_3D,"iimage3D"},
  {GL_INT_IMAGE_2D_RECT,"iimage2DRect"},
  {GL_INT_IMAGE_CUBE,"iimageCube"},
  {GL_INT_IMAGE_BUFFER,"iimageBuffer"},
  {GL_INT_IMAGE_1D_ARRAY,"iimage1DArray"},
  {GL_INT_IMAGE_2D_ARRAY,"iimage2DArray"},
  {GL_INT_IMAGE_2D_MULTISAMPLE,"iimage2DMS"},
  {GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"iimage2DMSArray"},
  {GL_UNSIGNED_INT_IMAGE_1D,"uimage1D"},
  {GL_UNSIGNED_INT_IMAGE_2D,"uimage2D"},
  {GL_UNSIGNED_INT_IMAGE_3D,"uimage3D"},
  {GL_UNSIGNED_INT_IMAGE_2D_RECT,"uimage2DRect"},
  {GL_UNSIGNED_INT_IMAGE_CUBE,"uimageCube"},
  {GL_UNSIGNED_INT_IMAGE_BUFFER,"uimageBuffer"},
  {GL_UNSIGNED_INT_IMAGE_1D_ARRAY,"uimage1DArray"},
  {GL_UNSIGNED_INT_IMAGE_2D_ARRAY,"uimage2DArray"},
  {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,"uimage2DMS"},
  {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"uimage2DMSArray"},
  {GL_UNSIGNED_INT_ATOMIC_COUNTER,"atomic_uint"},

#endif
  {GL_SAMPLER_2D,"sampler2D"},
  {GL_SAMPLER_3D,"sampler3D"},
  {GL_SAMPLER_CUBE,"samplerCube"},
  {GL_SAMPLER_2D_SHADOW,"sampler2DShadow"},
  {GL_SAMPLER_2D_ARRAY,"sampler2DArray"},
  {GL_SAMPLER_2D_ARRAY_SHADOW,"sampler2DArrayShadow"},
  {GL_SAMPLER_CUBE_SHADOW,"samplerCubeShadow"},
  {GL_INT_SAMPLER_2D,"isampler2D"},
  {GL_INT_SAMPLER_3D,"isampler3D"},
  {GL_INT_SAMPLER_CUBE,"isamplerCube"},
  {GL_INT_SAMPLER_2D_ARRAY,"isampler2DArray"},
  {GL_UNSIGNED_INT_SAMPLER_2D,"usampler2D"},
  {GL_UNSIGNED_INT_SAMPLER_3D,"usampler3D"},
  {GL_UNSIGNED_INT_SAMPLER_CUBE,"usamplerCube"},
  {GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,"usampler2DArray"}
};



void ShaderProcessor::processUniforms()
{
  ngl::ShaderLib *shaders= ngl::ShaderLib::instance();

  GLuint programID=shaders->getProgramID(m_shaderProgramName );
  GLint nUniforms;
  glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &nUniforms);
  // could use this with better OpenGL version
  // glGetProgramInterfaceiv(i, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

  char name[256];
  uniformData data;
  for (GLint i=0; i<nUniforms; ++i)
  {
    GLenum type = GL_ZERO;
    GLsizei nameLen=0;
    GLint num=0;
    glGetActiveUniform( programID, i, sizeof(name)-1, &nameLen, &num, &type, name );
    // two options we either have an array or single value
    // if not array
    if(num == 1)
    {
      data.name=name;
      data.loc=glGetUniformLocation(programID,name);
      data.type=type;
      std::string typeAsString;
      auto value=GLtypes.find(type);
      if(value !=GLtypes.end())
      {
        typeAsString=value->second;
      }
      else
      {
        typeAsString="unknown type";
      }
      data.typeAsString=typeAsString;
      m_registeredUniforms[name]=data;
    }
    else
    {
      std::string uniform(name);
      std::string baseName=uniform.substr(0, uniform.find("["));
      // nvidia returns uniform[0], ATI uniform, best way is to split on [
      for(int i=0; i<num; ++i)
      {
        std::string name=fmt::format("{0}[{1}]", baseName , i) ;

        data.name=name;
        data.loc=glGetUniformLocation(programID,name.c_str());
        data.type=type;
        m_registeredUniforms[name]=data;
      }
    }
  }
}

const std::unordered_map <std::string, ShaderProcessor::uniformData> &ShaderProcessor::getUniforms() const
{
  return m_registeredUniforms;
}

void ShaderProcessor::exportClass(const std::string &_path, bool _abstract)
{
  if(_abstract == true)
  {
    std::ofstream fileOut(_path+"/AbstractShaderProgram.h");
    if (!fileOut.is_open())
    {
      std::cerr <<"Could not open File : "<<_path<<"/AbstractShaderProgram.h"<<" for writing \n";
      exit(EXIT_FAILURE);
    }
    fileOut << ExportData::AbstractShaderProgramHeader()<<'\n';
    fileOut.close();

    fileOut.open(_path+"/AbstractShaderProgram.cpp");
    if (!fileOut.is_open())
    {
      std::cerr <<"Could not open File : "<<_path<<"/AbstractShaderProgram.cpp"<<" for writing \n";
      exit(EXIT_FAILURE);
    }
    fileOut << ExportData::AbstractShaderProgramCPP()<<'\n';
    fileOut.close();
  }

  writeHeader(_path);
}


void ShaderProcessor::writeHeader(const std::string &_path)
{
  std::cerr<<"m_shaderProgname is "<<m_shaderProgramName<<'\n';
  std::cerr<<"File is "<<_path+'/'+m_shaderProgramName+".h"<<'\n';
  std::ofstream fileOut(_path+'/'+m_shaderProgramName+".h" );
  if (!fileOut.is_open())
  {
    std::cerr <<"Could not open File : "<<_path+'/'+m_shaderProgramName+".h"<<" for writing \n";
    exit(EXIT_FAILURE);
  }
  // convert name to upper for include guard
  std::string current=m_shaderProgramName;
  std::transform(std::begin(current),std::end(current), std::begin(current),::toupper);
  std::cout<<m_shaderProgramName<<" "<<current<<"\n";
  fileOut <<"#ifndef "<< current <<"_H_\n";
  fileOut <<"#define "<< current <<"_H_\n";
  // write include headers
  fileOut <<ExportData::derivedShaderBaseCode();

  fileOut<<"class "<< m_shaderProgramName <<" : public AbstractShaderProgram \n";
  fileOut<<"{\n";
  fileOut<<"\tpublic :\n";
  fileOut<<"\t\tstatic std::unique_ptr<"<<m_shaderProgramName<<"> getShader();\n";
  // now write pre-constructed methods
  writePublicMethods(fileOut);
  fileOut<<"\tprivate :\n";
  fileOut<<"\t\t"<<m_shaderProgramName<<"();\n";
  // now write pre-constructed attributes
  // writePrivateAttributes(fileout);
  // end class definition
  fileOut<<"};\n";
  // end include guard
  fileOut<<"#endif";
  fileOut.close();

}

void ShaderProcessor::writePublicMethods(std::ofstream &_fileOut)
{
  for(auto p : m_classPublicData)
    _fileOut<<"\t\t"<<p<<'\n';
}



