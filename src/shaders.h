
#pragma once
#include "gl_api.h"
#include "python_api.h"

#include <vector>
#include <string>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

#define SHADER_BINDINGS \
    {"build_shader", (PyCFunction)BuildShader, METH_FASTCALL, NULL}, \
    {"activate_shader", (PyCFunction)ActivateShader, METH_FASTCALL, NULL}, \
    {"shader_attrs", (PyCFunction)GetShaderAttrs, METH_FASTCALL, NULL}, \
    {"shader_uniform_blocks", (PyCFunction)GetShaderUniformBlocks, METH_FASTCALL, NULL},




class ShaderStage
{
public:
    ShaderStage(const string ShaderSource, const GLenum ShaderType);
    ~ShaderStage();
    GLuint ShaderId;
    GLenum ShaderType;
    size_t ShaderHash;
    string ErrorString;
    bool bIsValid;
};




struct Attribute
{
    string Name;
    GLenum Type;
    GLint Slot;
    GLint Size;
};




struct UniformEntry
{
    string Name;
    GLenum Type;
    GLint ArraySize;
    GLint BlockOffset;
    GLint BlockArrayStride;
    GLint BlockMatrixStride;
};




struct UniformBlock
{
    string Name;
    GLuint ProgramId;
    GLuint BlockIndex;
    GLuint BufferSize;
    vector<UniformEntry> Uniforms;
};




class ShaderProgram
{
public:
    ShaderProgram(const string VertexSource, const string FragmentSource);
    ~ShaderProgram();
    GLuint ProgramId;
    string ErrorString;
    bool bIsValid;

    shared_ptr<ShaderStage> VertexShader;
    shared_ptr<ShaderStage> FragmentShader;

    vector<Attribute> Attributes;
    vector<UniformBlock> UniformBlocks;

private:
    void GatherAttributes();
    void GatherUniforms();
    vector<GLint> ResourceQuery(GLenum Interface, GLuint ResourceIndex, GLenum Query, GLsizei ItemCount);
    vector<GLint> ResourceQuery(GLenum Interface, GLuint ResourceIndex, vector<GLenum> Query);
    GLint ResourceQuery(GLenum Interface, GLuint ResourceIndex, const GLenum Query);
    GLint InterfaceProperty(GLenum Interface, GLenum Property);
    string ResourceName(GLenum Interface, GLuint ResourceIndex);
};



PYTHON_API(BuildShader);
PYTHON_API(ActivateShader);
PYTHON_API(GetShaderAttrs);
PYTHON_API(GetShaderUniformBlocks);
