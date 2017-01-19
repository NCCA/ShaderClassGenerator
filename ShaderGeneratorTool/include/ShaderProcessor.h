#ifndef SHADERPROCESSOR_H_
#define SHADERPROCESSOR_H_

#include <iostream>
#include <array>
#include <unordered_map>
#include <vector>
#include <string>
#include <ngl/Types.h>

class ShaderProcessor
{
  public :
    // used to enumerate into array of shaders loaded
    enum class ShaderType {Vertex,Fragment,Geometry,TessEval,TessControl,Compute};
    typedef struct
    {
      GLint loc;
      std::string name;
      std::string typeAsString;
      GLenum type;
    }uniformData;

    ShaderProcessor();
    bool loadShader(const std::string &_path, ShaderType _type);
    void setProgramName(const std::string &_name);
    void createShaderProgram();
    void processUniforms();
    void exportClass(const std::string &_path, bool _abstract);

    const std::unordered_map <std::string, uniformData> &getUniforms() const;
  private :

    typedef struct
    {
      std::string sourcePath;
      bool active=false;
    }Shader;


    void writeHeader(const std::string &_path);
    void writeCPP(const std::string &_path);
    void writePublicMethods(std::ofstream &fileOut);
    void writeImplementation(const std::string &_path);
    void writeShaderStrings(std::ofstream &fileOut);
    void writeCreationMethods(std::ofstream &fileOut);

    void generateStringsFromUniforms();
    void defineFunctionString(const uniformData &_p);
    void defineFunctionBodyString(const uniformData &_p);

    void defineAttributeString(const uniformData &_p);
    void writeParams(GLenum _type,std::string &io_func);
    std::array<Shader,6> m_shaders;
    std::unordered_map <std::string, uniformData> m_registeredUniforms;

    // name of the overall shader
    std::string m_shaderProgramName;
    std::vector<std::string> m_classPublicData;
    std::vector<std::string> m_classPrivateData;
    std::vector<std::string> m_classStaticAttributesCPP;
    std::vector<std::string> m_classShaderFunctionsCPP;


};


#endif
