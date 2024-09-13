#include "aura_effect.h"

const int			CAuraEffect::m_width		= 384;
const int			CAuraEffect::m_height		= 384;
const int			CAuraEffect::m_fade_speed	= 2;
const float			CAuraEffect::m_move_speed	= 0.8f;
const std::string	CAuraEffect::m_file_name	= "data/aura_effect.png";

CAuraEffect::
CAuraEffect()
	: IEffect(EFFECT_ID::AURA, m_width, m_height)
{
}

CAuraEffect::
~CAuraEffect()
{
}

void 
CAuraEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	int maxX = position.x + m_width / 3;
	int maxY = position.y + m_height / 3;
	int minX = position.x - m_width / 3;
	int minY = position.y - m_height / 6;

	float x = (float)(rand() % maxX + minX);
	float y = (float)(rand() % maxY + minY);

	IEffect::Initialize(position, color, rotation);

	m_Position.x = x;
	m_Position.y = y;
}

void 
CAuraEffect::
Update()
{
	m_Position.y -= m_move_speed;

	FadeOut(m_fade_speed);
}

void 
CAuraEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
