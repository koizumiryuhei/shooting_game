#include "charge_effect.h"

const int	CChargeEffect::m_width			= 36;
const int	CChargeEffect::m_height			= 36;
const int	CChargeEffect::m_fade_speed		= 30;
const float CChargeEffect::m_scale_speed	= 0.1f;

CChargeEffect::
CChargeEffect()
	: IEffect(m_width, m_height)
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
	IEffect::Initialize(position, color, rotation);
}

void 
CChargeEffect::
Update()
{
	m_Scale.x += m_scale_speed;
	m_Scale.y += m_scale_speed;
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
CChargeEffect::
Draw()
{
	vivid::DrawTexture("data/charge_effect.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
