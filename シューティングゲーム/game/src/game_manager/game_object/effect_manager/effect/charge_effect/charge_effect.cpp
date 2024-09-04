#include "charge_effect.h"

const int	CChargeEffect::m_width			= 36;
const int	CChargeEffect::m_height			= 36;
const int	CChargeEffect::m_fade_speed		= 30;
const float CChargeEffect::m_scale_speed	= 0.1f;
const std::string CChargeEffect::m_file_name = "data/charge_effect.png";

CChargeEffect::
CChargeEffect()
	: IEffect(EFFECT_ID::CHARGE_EFFECT, m_width, m_height)
{
}

CChargeEffect::
~CChargeEffect()
{
}

void 
CChargeEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);
}

void 
CChargeEffect::
Update()
{
	m_Scale.x += m_scale_speed;
	m_Scale.y += m_scale_speed;
	
	FadeOut(m_fade_speed);
}

void 
CChargeEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
