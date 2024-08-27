#include "boss_spot_light.h"

const int CBossSpotLight::m_width	= 800;
const int CBossSpotLight::m_height	= 50;

CBossSpotLight::CBossSpotLight()
	: IEffect(m_width, m_height)
{
}

CBossSpotLight::~CBossSpotLight()
{
}

void CBossSpotLight::Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	IEffect::Initialize(position, color, rotation);

	m_RotationSpeed = DEG_TO_RAD((float)(rand() % 200 - 100) / 100.0f);
}

void CBossSpotLight::Update()
{
	m_Rotation += m_RotationSpeed;
}

void CBossSpotLight::Draw()
{
	m_Anchor = { 0, m_height / 2 };

	vivid::DrawTexture("data/boss_spot_light.png", m_Position, m_Color, m_Rect, m_Anchor, m_Rotation);
}
