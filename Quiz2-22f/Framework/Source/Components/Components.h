#pragma once

#include "Math/Vector.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Utility/ShaderProgram.h"

namespace fw {

    class BaseComponent
    {
    public:
        BaseComponent() { }
        virtual ~BaseComponent() { }

    };


    class Transform : public BaseComponent
    {
    public:
        vec2 Position = { 0,0 };
        vec2 Scale = { 1,1 };
        float Rotation = 0.0f;

        Transform() {}
        Transform(vec2 position, vec2 scale, float rotation) : Position(position), Scale(scale), Rotation(rotation) {}
        virtual ~Transform() {}
    };


    class Renderable : public BaseComponent
    {
    public:
        Mesh* pMesh = nullptr;
        Texture* pTexture = nullptr;
        ShaderProgram* pShaderProgram = nullptr;

        Renderable() {}
        Renderable(Mesh* pMesh, Texture* pTexture, ShaderProgram* pShaderProgram) : pMesh(pMesh), pTexture(pTexture), pShaderProgram(pShaderProgram) {}
        virtual ~Renderable() {}

    };

}