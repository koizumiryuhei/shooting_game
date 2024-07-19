#include "boss_bullet.h"

const int	CBossBullet::m_width	= 96;
const int	CBossBullet::m_height	= 96;
const float CBossBullet::m_radius	= 48.0f;

CBossBullet::
CBossBullet()
	: IBullet(m_width, m_height, m_radius)
{
}

CBossBullet::
~CBossBullet()
{
}

void 
CBossBullet::
Draw()
{
	vivid::DrawTexture("data\\boss_bullet_bloom.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data\\boss_bullet.png", m_Position, 0xffffffff, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
