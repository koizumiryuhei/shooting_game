#include "charge_particle.h"
#include "../../../unit_manager/unit_manager.h"

const int	CChargeParticle::m_width				= 12;
const int	CChargeParticle::m_height				= 12;
const int	CChargeParticle::m_fade_speed			= 8;
const float CChargeParticle::m_move_speed			= 1.75f;
const float CChargeParticle::m_accelerator			= 0.01f;
const float CChargeParticle::m_max_create_length	= 50.0f;

CChargeParticle::
CChargeParticle()
	: IEffect(m_width, m_height)
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

	vivid::Vector2 player = CUnitManager::GetInstance().GetFighter()->GetCenterPosition();
	vivid::Vector2 v = player - position;

	float angle = atan2(v.y, v.x);
	m_Velocity.x = cos(angle) * (m_move_speed * (v.Length() / m_max_create_length));
	m_Velocity.y = sin(angle) * (m_move_speed * (v.Length() / m_max_create_length));
	m_Accelerator.x = cos(angle) * (m_accelerator * (v.Length() / m_max_create_length));
	m_Accelerator.y = sin(angle) * (m_accelerator * (v.Length() / m_max_create_length));
}

void 
CChargeParticle::
Update()
{
	m_Velocity += m_Accelerator;
	m_Position += m_Velocity;

	int alpha = (m_Color & 0xff000000) >> 24;
	alpha -= m_fade_speed;

	if (alpha < 0)
	{
		alpha = 0;
		m_ActiveFlag = false;
	}

	m_Color = (alpha << 24) | (m_Color & 0x00ffffff);
}

void 
CChargeParticle::
Draw()
{
	vivid::DrawTexture("data/charge_particle.png", m_Position, m_Color);
}
