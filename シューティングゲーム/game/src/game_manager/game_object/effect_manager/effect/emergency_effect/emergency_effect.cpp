#include "emergency_effect.h"

const int			CEmergencyEffect::m_width				= 256;
const int			CEmergencyEffect::m_height				= 64;
const int			CEmergencyEffect::m_warning_width		= 960;
const int			CEmergencyEffect::m_warning_height		= 32;
const int			CEmergencyEffect::m_max_alpha			= 160;
const int			CEmergencyEffect::m_min_alpha			= 0;
const int			CEmergencyEffect::m_fade_speed			= 15;
const int			CEmergencyEffect::m_flash_count			= 20;
const int			CEmergencyEffect::m_max_bg_count		= 2;
const float			CEmergencyEffect::m_scroll_speed		= 5.0f;
const std::string	CEmergencyEffect::m_emergency_file_name = "data/emergency.png";
const std::string	CEmergencyEffect::m_warning_file_name	= "data/warning.png";
const std::string	CEmergencyEffect::m_white_file_name		= "data/white.png";

CEmergencyEffect::
CEmergencyEffect()
	: IEffect(EFFECT_ID::EMERGENCY, m_width, m_height)
	, m_WarningPosition1(nullptr)
	, m_WarningPosition2(nullptr)
{
}

CEmergencyEffect::
~CEmergencyEffect()
{
	delete[] m_WarningPosition1;

	m_WarningPosition1 = nullptr;

	delete[] m_WarningPosition2;

	m_WarningPosition2 = nullptr;
}

void 
CEmergencyEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_emergency_file_name);
	vivid::LoadTexture(m_warning_file_name);
	vivid::LoadTexture(m_white_file_name);

	IEffect::Initialize(position, color, rotation);

	m_Position.x = (float)(vivid::WINDOW_WIDTH - m_width) / 2.0f;
	m_Position.y = (float)(vivid::WINDOW_HEIGHT - m_height) / 2.0f;

	if (!m_WarningPosition1)
		m_WarningPosition1 = new vivid::Vector2[m_max_bg_count];

	if (!m_WarningPosition2)
		m_WarningPosition2 = new vivid::Vector2[m_max_bg_count];

	for (int i = 0; i < m_max_bg_count; ++i)
	{
		m_WarningPosition1[i].x = (float)i * (float)vivid::WINDOW_WIDTH;
		m_WarningPosition2[i].x = (float)i * (float)-vivid::WINDOW_WIDTH;
		m_WarningPosition1[i].y = m_Position.y - m_warning_height;
		m_WarningPosition2[i].y = m_Position.y + m_height;
	}

	m_FadeState = FADE_STATE::FADE_OUT;
	m_FlashCounter = 0;
}

void 
CEmergencyEffect::
Update()
{
	for (int i = 0; i < m_max_bg_count; ++i)
	{
		m_WarningPosition1[i].x -= m_scroll_speed;
		m_WarningPosition2[i].x += m_scroll_speed;

		if (m_WarningPosition1[i].x + vivid::WINDOW_WIDTH < 0.0f)
			m_WarningPosition1[i].x = vivid::WINDOW_WIDTH - m_scroll_speed;

		if (m_WarningPosition2[i].x > vivid::WINDOW_WIDTH)
			m_WarningPosition2[i].x = -vivid::WINDOW_WIDTH + (m_WarningPosition2[i].x - vivid::WINDOW_WIDTH);
	}

	int alpha = (m_Color & 0xff000000) >> 24;

	switch (m_FadeState)
	{
	case FADE_STATE::FADE_IN:
		{
			alpha += m_fade_speed;

			if (alpha > m_max_alpha)
			{
				alpha = m_max_alpha;

				m_FadeState = FADE_STATE::FADE_OUT;
			}

			break;
		}
	case FADE_STATE::FADE_OUT:
		{
			alpha -= m_fade_speed;

			if (alpha < m_min_alpha)
			{
				alpha = m_min_alpha;

				++m_FlashCounter;

				m_FadeState = FADE_STATE::FADE_IN;
			}

			break;
		}
	}

	m_Color = (alpha << 24) | (m_Color & 0x00ffffff);

	if (m_FlashCounter > m_flash_count)
	{
		m_ActiveFlag = false;
	}
}

void 
CEmergencyEffect::
Draw()
{
	vivid::DrawTexture(m_emergency_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);

	vivid::Rect		rect	= { 0,0,m_warning_width, m_warning_height };
	vivid::Vector2	anchor	= { m_warning_width / 2,m_warning_height / 2 };
	vivid::Vector2	scale	= vivid::Vector2::ONE;

	for (int i = 0; i < m_max_bg_count; ++i)
	{
		rect.left	= i * vivid::WINDOW_WIDTH;
		rect.right	= rect.left + vivid::WINDOW_WIDTH;

		vivid::DrawTexture(m_warning_file_name, m_WarningPosition1[i], 0xffffffff, rect, anchor, scale, m_Rotation, vivid::ALPHABLEND::ADD);
		vivid::DrawTexture(m_warning_file_name, m_WarningPosition2[i], 0xffffffff, rect, anchor, scale, m_Rotation, vivid::ALPHABLEND::ADD);
	}

	rect = { 0,0,vivid::WINDOW_WIDTH, vivid::WINDOW_HEIGHT };

	int				alpha = m_Color >> 24;
	unsigned int	color = (alpha << 24) | (0xffff0000 & 0x00ffffff);

	vivid::DrawTexture(m_white_file_name, vivid::Vector2::ZERO, color, rect, anchor, scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
