#include "boss_explosion_ring.h"

const int			CBossExplosionRing::m_width				= 384;
const int			CBossExplosionRing::m_height			= 192;
const int			CBossExplosionRing::m_fade_speed		= 7;
const float			CBossExplosionRing::m_scale_speed		= 0.2f;
const std::string	CBossExplosionRing::m_file_name			= "data/boss_explosion_ring.png";
const std::string	CBossExplosionRing::m_bloom_file_name	= "data/boss_explosion_ring_bloom.png";

CBossExplosionRing::
CBossExplosionRing()
	: IEffect(EFFECT_ID::EXPLOSION_RING, m_width, m_height)
{
}

CBossExplosionRing::
~CBossExplosionRing()
{
}

void
CBossExplosionRing::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);
	vivid::LoadTexture(m_bloom_file_name);

	IEffect::Initialize(position, color, rotation);

	m_Position -= m_Anchor;
}

void
CBossExplosionRing::
Update()
{
	m_Scale.x += m_scale_speed;
	m_Scale.y += m_scale_speed / 2.0f;

	FadeOut(m_fade_speed);
}

void
CBossExplosionRing::
Draw()
{
	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture(m_bloom_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}