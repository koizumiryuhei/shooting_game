#include "boss_destory_effect.h"

const int			CBossDestroyEffect::m_width			= 16;
const int			CBossDestroyEffect::m_height		= 16;
const int			CBossDestroyEffect::m_fade_speed	= 4;
const float			CBossDestroyEffect::m_move_speed	= 4.0f;
const std::string	CBossDestroyEffect::m_file_name		= "data/destory_particle.png";
const int			CBossDestroyEffect::m_color_count	= 4;
const int			CBossDestroyEffect::m_color_pallet[m_color_count] =
{
	0xffff4444,
	0xff44ff44,
	0xffff44ff,
	0xffffff44
};

CBossDestroyEffect::
CBossDestroyEffect()
	: IEffect(EFFECT_ID::BOSS_DESTORY, m_width, m_height)
{
}

CBossDestroyEffect::
~CBossDestroyEffect()
{
}

void 
CBossDestroyEffect::
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

	int scale	= rand() % 15 + 10;
	m_Scale.x	= (float)scale;
	m_Scale.y	= (float)scale;
	m_Width		= m_width * m_Scale.x;
	m_Height	= m_height * m_Scale.y;
}

void 
CBossDestroyEffect::
Update()
{
	m_Position += m_Velocity;

	FadeOut(m_fade_speed);
}

void 
CBossDestroyEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
