#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.

class Shader
{
public:
    // constructor
    Shader() {}

    // sets the current shader as active
    Shader &Use();

    inline constexpr const unsigned int& ID() const { 
        return this->m_ID;
    }

    // compiles the shader from given source code
    // note: geometry source code is optional
    // utility functions
    void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr); 

    void SetFloat(const char *name, float value, bool useShader = false);

    void SetInteger(const char *name, int value, bool useShader = false);

    void SetVector2f(const char *name, float x, float y, bool useShader = false);

    void SetVector2f(const char *name, const glm::vec2 &value, bool useShader = false);

    void SetVector3f(const char *name, float x, float y, float z, bool useShader = false);

    void SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);

    void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);

    void SetVector4f(const char *name, const glm::vec4 &value, bool useShader = false);

    void SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);

private:
    // state
    unsigned int m_ID;

private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif // !_SHADER_H_
