#pragma once
#include "DataTypes.h"

class VirtualController;
class fw::Mesh;
class fw::Texture;
class fw::ShaderProgram;


class Car : public GameObject
{
public:
	Car(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture);
	~Car();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* pCamera) override;

	void GetIn(VirtualController* controller);
	void GetOut();
	VirtualController* GetController() { return m_pController; }

	void OnKeyEvent(float deltaTime);

protected:
	VirtualController* m_pController = nullptr;
	Vec2 m_UVScale = { 1,1 };
	Vec2 m_UVOffset = { 0,0 };
	Vec2 m_ForwardVector = { 0,0 };

	float m_TurnSpeed = 2.0f;
	float m_MovementSpeed = 15.0f;

};