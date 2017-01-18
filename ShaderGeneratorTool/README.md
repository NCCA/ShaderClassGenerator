#ShaderClassGenerator

```
class AbstractShaderProgram
{
  public :
    AbstractShader();
    static void bind();
    static void unbind();
    static GLint getProgramID() const {return m_id;}
    virtual bool createShaderProgram()=0;
  private :
    static GLint m_id;

};
```
