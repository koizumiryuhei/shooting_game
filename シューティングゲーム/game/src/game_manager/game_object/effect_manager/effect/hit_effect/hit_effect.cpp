#include "hit_effect.h"

const int			CHitEffect::m_width			= 8;
const int			CHitEffect::m_height		= 8;
const int			CHitEffect::m_fade_speed	= 10;
const float			CHitEffect::m_move_speed	= 0.8f;
const std::string	CHitEffect::m_file_name		= "data/hit_particle.png";

CHitEffect::
CHitEffect()
	: IEffect(EFFECT_ID::HIT, m_width, m_height)
{
}

CHitEffect::
~CHitEffect()
{
}

void 
CHitEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);

	float angle = RAND_IN_360;
	m_Velocity.x = cos(angle) * m_move_speed;
	m_Velocity.y = sin(angle) * m_move_speed;
}

void 
CHitEffect::
Update()
{
	m_Position += m_Velocity;

	FadeOut(m_fade_speed);
}

void 
CHitEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
