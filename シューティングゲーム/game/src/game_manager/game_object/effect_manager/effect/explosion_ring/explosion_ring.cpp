#include "explosion_ring.h"

const int			CExplosionRing::m_width				= 64;
const int			CExplosionRing::m_height			= 32;
const int			CExplosionRing::m_fade_speed		= 12;
const float			CExplosionRing::m_scale_speed		= 0.28f;
const std::string	CExplosionRing::m_file_name			= "data/explosion_ring.png";
const std::string	CExplosionRing::m_bloom_file_name	= "data/explosion_ring_bloom.png";

CExplosionRing::
CExplosionRing()
	: IEffect(EFFECT_ID::EXPLOSION_RING, m_width, m_height)
{
}

CExplosionRing::
~CExplosionRing()
{
}

void 
CExplosionRing::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);
	vivid::LoadTexture(m_bloom_file_name);

	IEffect::Initialize(position, color, rotation);

	m_Position -= m_Anchor;
}

void 
CExplosionRing::
Update()
{
	m_Scale.x += m_scale_speed;
	m_Scale.y += m_scale_speed / 2.0f;

	FadeOut(m_fade_speed);
}

void 
CExplosionRing::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture(m_bloom_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
