#pragma once

#include "Math/Vector.h"

namespace fw {

class ShaderProgram;
class Texture;
class Transform;

struct VertexFormat
{
    vec2 pos;
    unsigned char r, g, b, a;
    vec2 uv;
};

class Mesh
{
public:
    Mesh(std::vector<VertexFormat>& verts, int primType);
    virtual ~Mesh();

    void Draw(ShaderProgram* pShader, fw::Texture* pTexture, Transform* pTransform, float aspectRatio);

protected:
    GLuint m_VBO;
    int m_NumVerts;
    int m_PrimitiveType;
};

}