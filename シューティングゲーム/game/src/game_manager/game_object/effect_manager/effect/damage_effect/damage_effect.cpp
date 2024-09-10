#include "damage_effect.h"

const int			CDamageEffect::m_width		= 480;
const int			CDamageEffect::m_height		= 640;
const int			CDamageEffect::m_fade_speed = 10;
const std::string	CDamageEffect::m_file_name	= "data/white.png";

CDamageEffect::
CDamageEffect()
	: IEffect(EFFECT_ID::DAMAGE, m_width, m_height)
{
}

CDamageEffect::
~CDamageEffect()
{
}

void 
CDamageEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);
}

void 
CDamageEffect::
Update()
{
	FadeOut(m_fade_speed);
}

void 
CDamageEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
