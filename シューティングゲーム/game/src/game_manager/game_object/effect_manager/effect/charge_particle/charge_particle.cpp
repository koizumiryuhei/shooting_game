#include "charge_particle.h"
#include "../../../unit_manager/unit_manager.h"

const int	CChargeParticle::m_width				= 12;
const int	CChargeParticle::m_height				= 12;
const int	CChargeParticle::m_fade_speed			= 8;
const float CChargeParticle::m_move_speed			= 1.75f;
const float CChargeParticle::m_accelerator			= 0.01f;
const float CChargeParticle::m_max_create_length	= 50.0f;
const std::string CChargeParticle::m_file_name		= "data/charge_particle.png";

CChargeParticle::
CChargeParticle()
	: IEffect(EFFECT_ID::CHARGE_PARTICLE, m_width, m_height)
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
	vivid::LoadTexture(m_file_name);

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

	FadeOut(m_fade_speed);
}

void 
CChargeParticle::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color);
}
