#include "destory_effect.h"

const int			CDestroyEffect::m_width			= 16;
const int			CDestroyEffect::m_height		= 16;
const int			CDestroyEffect::m_fade_speed	= 4;
const float			CDestroyEffect::m_move_speed	= 0.72f;
const std::string	CDestroyEffect::m_file_name		= "data/destory_particle.png";
const int			CDestroyEffect::m_color_count	= 4;
const int			CDestroyEffect::m_color_pallet[m_color_count] =
{
	0xffff4444,
	0xff44ff44,
	0xffff44ff,
	0xffffff44
};

CDestroyEffect::
CDestroyEffect()
	: IEffect(EFFECT_ID::DESTORY, m_width, m_height)
{
}

CDestroyEffect::
~CDestroyEffect()
{
}

void 
CDestroyEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);

	m_Color = m_color_pallet[rand() % m_color_count];

	m_Position.x -= (float)(m_width / 2);
	m_Position.y -= (float)(m_height / 2);

	float angle	= RAND_IN_360;
	m_Velocity.x = cos(angle) * m_move_speed;
	m_Velocity.y = sin(angle) * m_move_speed;

	int scale	= rand() % 7 + 3;
	m_Scale.x	= (float)scale;
	m_Scale.y	= (float)scale;
	m_Width		= m_width * m_Scale.x;
	m_Height	= m_height * m_Scale.y;
}

void 
CDestroyEffect::
Update()
{
	m_Position += m_Velocity;

	FadeOut(m_fade_speed);
}

void 
CDestroyEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
