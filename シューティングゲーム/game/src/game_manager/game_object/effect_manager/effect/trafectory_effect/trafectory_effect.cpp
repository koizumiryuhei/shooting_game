#include "trafectory_effect.h"

const int CTrafectoryEffect::m_width = 36;
const int CTrafectoryEffect::m_height = 36;
const int CTrafectoryEffect::m_fade_speed = 5;

CTrafectoryEffect::
CTrafectoryEffect()
	: IEffect(m_width, m_height)
{
}

CTrafectoryEffect::
~CTrafectoryEffect()
{
}

void 
CTrafectoryEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	IEffect::Initialize(position, color, rotation);
}

void 
CTrafectoryEffect::
Update()
{
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
CTrafectoryEffect::
Draw()
{
	vivid::DrawTexture("data\\fighter_light_bloom.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
