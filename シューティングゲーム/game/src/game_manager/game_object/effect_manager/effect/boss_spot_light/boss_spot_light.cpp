#include "boss_spot_light.h"

const int			CBossSpotLight::m_width								= 800;
const int			CBossSpotLight::m_height							= 50;
const int			CBossSpotLight::m_color_table_count					= 4;
const unsigned int	CBossSpotLight::m_color_table[m_color_table_count]	=
{
	0x88cc0000,
	0x8800cc00,
	0x88cc00cc,
	0x88cccc00
};
const std::string CBossSpotLight::m_file_name = "data/boss_spot_light.png";

CBossSpotLight::CBossSpotLight()
	: IEffect(EFFECT_ID::BOSS_SPOT_LIGHT, m_width, m_height)
{
}

CBossSpotLight::~CBossSpotLight()
{
}

void CBossSpotLight::Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	vivid::LoadTexture(m_file_name);

	int col = rand() % m_color_table_count;

	IEffect::Initialize(position, m_color_table[col], rotation);

	m_RotationSpeed = DEG_TO_RAD((float)(rand() % 800 - 400) / 100.0f);
}

void CBossSpotLight::Update()
{
	m_Rotation += m_RotationSpeed;
}

void CBossSpotLight::Draw()
{
	m_Anchor = { 0, m_height / 2 };

	vivid::DrawTexture(m_file_name, m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD );
}
