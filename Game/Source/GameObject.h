#pragma once
#include "Vec2.h"

class fw::Mesh;
class fw::ShaderProgram;

enum class MeshType
{
	ExistingMesh,
	TriangleFilled,
	TriangleLines,
	SquareFilled,
	SquareLines
};

class GameObject
{
public:
	GameObject(fw::Mesh* pMesh, fw::ShaderProgram* shaderProgram, fw::Vec2 position, float timeElapsed, fw::Vec2 resolution, float color[], int size);
	~GameObject();
	void Update();
	void Draw();

	//void AddVertTriangle();
	//void AddRandomVert();
	//void ClearVerts();
	//void RemoveVerts(int numRemoved);


protected:
	float m_TimeElapsed = 0.0f;
	fw::Vec2 m_Resolution = { 0,0 };
	static const int m_ColorArraySize = 4;
	float m_Color[m_ColorArraySize] = {0,0,0,0};
	fw::Vec2 m_Position = { 0, 0 };
	fw::Vec2 m_Scale = { 1.0f,1.0f };
	float m_Angle = 0.0f;
	fw::Mesh* m_Mesh = nullptr;
	fw::ShaderProgram* m_ShaderProgram = nullptr;

	int m_NumVerts = 0;
	GLenum m_PrimType = 0;

	std::vector<fw::VertexFormat> points;
};