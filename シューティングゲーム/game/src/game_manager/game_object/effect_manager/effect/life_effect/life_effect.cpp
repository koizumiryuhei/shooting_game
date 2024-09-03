#include "life_effect.h"

const int CLifeEffect::m_width = 8;
const int CLifeEffect::m_height = 8;
const int CLifeEffect::m_one_rotation = 360;
const int CLifeEffect::m_max_rotation = 10;
const int CLifeEffect::m_min_rotation = 3;
const float CLifeEffect::m_speed = 0.5f;
const int CLifeEffect::m_fade_speed = 2;

CLifeEffect::CLifeEffect()
	: IEffect(EFFECT_ID::LIFE, m_width, m_height)
{
}

CLifeEffect::~CLifeEffect()
{
}

void CLifeEffect::Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	IEffect::Initialize(position, color, rotation);

	float angle = DEG_TO_RAD(rand() % m_one_rotation);
	m_Velocity.x = cos(angle) * m_speed;
	m_Velocity.y = sin(angle) * m_speed;

	m_RotationSpeed = DEG_TO_RAD((float)(rand() % m_max_rotation + m_min_rotation));
}

void CLifeEffect::Update()
{
	m_Position += m_Velocity;

	m_Rotation += m_RotationSpeed;

	FadeOut(m_fade_speed);
}

void CLifeEffect::Draw()
{
	vivid::DrawTexture("data/life_particle.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
