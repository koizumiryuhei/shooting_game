#include "charge_particle.h"
#include "../../../unit_manager/unit_manager.h"

const int	CChargeParticle::m_width = 36;
const int	CChargeParticle::m_height = 36;
const int	CChargeParticle::m_fade_speed = 30;
const float CChargeParticle::m_move_speed = 1.2f;
const float CChargeParticle::m_accelerator = 0.1f;
const float CChargeParticle::m_max_accelerator = 3.0f;

CChargeParticle::
CChargeParticle()
{
}

CChargeParticle::
~CChargeParticle()
{
}

void 
CChargeParticle::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	IEffect::Initialize(position, color, rotation);
	m_PlayerPosition = CUnitManager::GetInstance().GetFighter()->GetCenterPosition();
	vivid::Vector2 v = m_PlayerPosition - position;

	float angle = atan2(v.y, v.y);
	m_Velocity.x = cos(angle) * m_move_speed;
	m_Velocity.y = sin(angle) * m_move_speed;
}

void 
CChargeParticle::
Update()
{
	m_Velocity.x += m_accelerator;
	m_Velocity.y += m_accelerator;

	if (m_Velocity.x > m_max_accelerator)
	{
		m_Velocity.x = m_max_accelerator;
		m_Velocity.y = m_max_accelerator;
	}

	m_Position += m_Velocity;

	vivid::Vector2 v = m_PlayerPosition - m_Position;
	float length = sqrt(v.x * v.x + v.y * v.y);

	if (length < 0.5f)
		m_ActiveFlag = false;
}

void 
CChargeParticle::
Draw()
{
}
