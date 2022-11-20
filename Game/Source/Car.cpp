#include "Framework.h"
#include "VirtualController.h"
#include "GameObject.h"
#include "Car.h"


Car::Car(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture) 
{
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_pTexture = pTexture;
	m_Angle = 0.0f;
}

Car::~Car()
{

}

void Car::Update(float deltaTime)
{
	//Calculating the Direction the Car is facing
	m_ForwardVector = { cosf(m_Angle / 180.0f * 3.14159f), sinf(m_Angle / 180.0f * 3.14159f) };
}

void Car::Draw(Camera* pCamera)
{
	if (!m_IsActive)
		return;

	m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_UVScale, m_UVOffset);
}

void Car::GetIn(VirtualController* controller)
{
	m_pController = controller;
}

void Car::GetOut()
{
	m_pController = nullptr;
}

void Car::OnKeyEvent(float deltaTime)
{
	if (m_pController != nullptr)
	{
		//Turn the Car
		if (m_pController->IsHeld(VirtualController::Action::Right)) // D or Right Arrow
		{
			m_Angle -= m_TurnSpeed;
		}
		else if (m_pController->IsHeld(VirtualController::Action::Left)) // A or Left arrow
		{
			m_Angle += m_TurnSpeed;
		}

		//Moving the Car forward and backward
		if (m_pController->IsHeld(VirtualController::Action::Up)) // W or Up arrow
		{
			Vec2 velocity = m_ForwardVector * m_MovementSpeed;
			m_Position += velocity * deltaTime;
		}
		else if (m_pController->IsHeld(VirtualController::Action::Down)) // S or Down arrow
		{
			m_Position -= m_ForwardVector * (m_MovementSpeed * deltaTime);
		}

		//Get out of the Car
		if (m_pController->WasNewlyPressed(VirtualController::Action::Interact)) // E
		{
			GetOut();
		}
	}
}
