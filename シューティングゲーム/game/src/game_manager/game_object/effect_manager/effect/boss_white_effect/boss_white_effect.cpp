#include "boss_white_effect.h"

const int			CBossWhiteEffect::m_width				= 384;
const int			CBossWhiteEffect::m_height				= 252;
const int			CBossWhiteEffect::m_max_alpha			= 255;
const int			CBossWhiteEffect::m_min_alpha			= 0;
const int			CBossWhiteEffect::m_flash_interval		= 35;
const int			CBossWhiteEffect::m_dec_flash_interval	= 3;
const std::string	CBossWhiteEffect::m_file_name			= "data/boss_white.png";

CBossWhiteEffect::
CBossWhiteEffect()
	: IEffect(EFFECT_ID::BOSS_WHITE_EFFECT, m_width, m_height)
{
}

CBossWhiteEffect::
~CBossWhiteEffect()
{
}

void 
CBossWhiteEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	IEffect::Initialize(position, color, rotation);

	m_FadeState		= FADE_STATE::FADE_OUT;
	m_FlashTimer	= 0;
	m_FlashCounter	= 0;
}

void 
CBossWhiteEffect::
Update()
{
	int flash_interval = m_flash_interval - m_dec_flash_interval * m_FlashCounter;

	if (flash_interval < 2)
		flash_interval = 2;

	if (++m_FlashTimer <= flash_interval)return;

	m_FlashTimer = 0;

	int alpha = (m_Color & 0xff000000) >> 24;

	switch (m_FadeState)
	{
	case FADE_STATE::FADE_IN:
		{
			alpha = m_max_alpha;

			m_FadeState = FADE_STATE::FADE_OUT;

			break;
		}
	case FADE_STATE::FADE_OUT:
		{
			alpha = m_min_alpha;

			m_FadeState = FADE_STATE::FADE_IN;

			break;
		}
	}

	m_Color = (alpha << 24) | (m_Color & 0x00ffffff);

	++m_FlashCounter;
}

void 
CBossWhiteEffect::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color);
}
