#include "homing_effect.h"

const int CHomingEffect::m_width		= 32;
const int CHomingEffect::m_height		= 16;
const int CHomingEffect::m_max_alpha	= 160;
const int CHomingEffect::m_fade_speed	= 10;
const std::string CHomingEffect::m_file_name = "data/homing_bullet_bloom.png";

CHomingEffect::
CHomingEffect()
	: IEffect(EFFECT_ID::HOMING, m_width, m_height)
{
}

CHomingEffect::
~CHomingEffect()
{
}

void CHomingEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	int alpha = (color & 0xff000000) >> 24;

	alpha = m_max_alpha;

	color = (alpha << 24) | (color & 0x00ffffff);

	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);
}

void CHomingEffect::
Update()
{
	FadeOut(m_fade_speed);
}

void CHomingEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
