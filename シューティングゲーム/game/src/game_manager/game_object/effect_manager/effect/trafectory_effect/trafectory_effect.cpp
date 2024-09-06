#include "trafectory_effect.h"

const int			CTrafectoryEffect::m_width		= 36;
const int			CTrafectoryEffect::m_height		= 36;
const int			CTrafectoryEffect::m_max_alpha	= 180;
const int			CTrafectoryEffect::m_fade_speed = 5;
const std::string	CTrafectoryEffect::m_file_name	= "data/fighter_light_bloom.png";

CTrafectoryEffect::
CTrafectoryEffect()
	: IEffect(EFFECT_ID::TRAFECTORY, m_width, m_height)
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
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);
}

void 
CTrafectoryEffect::
Update()
{
	FadeOut(m_fade_speed);
}

void 
CTrafectoryEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
