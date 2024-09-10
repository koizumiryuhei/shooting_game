#include "homing_bullet.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../unit_manager/unit/unit.h"
#include "../../../../../utility/utility.h"
#include "../../../effect_manager/effect_manager.h"

const int	CHomingBullet::m_width				= 32;
const int	CHomingBullet::m_height				= 16;
const float	CHomingBullet::m_radius				= 8.0f;
const float CHomingBullet::m_accelerator		= 0.06f;
const float CHomingBullet::m_max_speed			= 10.0f;
const float	CHomingBullet::m_homing_angle		= 3.8f;
const int	CHomingBullet::m_max_homing_time	= 80;
const int	CHomingBullet::m_effect_interval	= 5;

CHomingBullet::CHomingBullet()
	: IBullet(m_width, m_height, m_radius)
	, m_Speed(0.0f)
	, m_Angle(0.0f)
	, m_HomingTime(m_max_homing_time)
	, m_EffectTimer(0)
{
}

CHomingBullet::~CHomingBullet()
{
}

void CHomingBullet::Initialize(UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed)
{
	IBullet::Initialize(category, position, direction, speed);

	m_Speed			= speed;
	m_Angle			= direction;
	m_HomingTime	= m_max_homing_time;
	m_EffectTimer	= 0;
}

void CHomingBullet::Update()
{
	m_Speed += m_accelerator;
	if (--m_HomingTime > 0)
	{
		IUnit* unit = CUnitManager::GetInstance().FindNearUnit(this);
		if (unit)
		{
			vivid::Vector2 v = unit->GetCenterPosition() - GetCenterPosition();
			float dir = vivid::Vector2::Cross(v, m_Velocity);
			if (dir > 0.0f)
				m_Angle -= DEG_TO_RAD(m_homing_angle);
			else
				m_Angle += DEG_TO_RAD(m_homing_angle);
		}
	}

	if (m_Speed > m_max_speed)
		m_Speed = m_max_speed;

	m_Velocity.x = m_Speed * cos(m_Angle);
	m_Velocity.y = m_Speed * sin(m_Angle);

	m_Position += m_Velocity;

	CheckArea();

	m_Rotation = atan2(m_Velocity.y, m_Velocity.x);

	if (++m_EffectTimer > m_effect_interval)
	{
		m_EffectTimer = 0;

		CEffectManager::GetInstance().Create(EFFECT_ID::HOMING, m_Position, m_Color, m_Rotation);
	}
}

void CHomingBullet::Draw()
{
	vivid::DrawTexture("data/homing_bullet_bloom.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/homing_bullet.png", m_Position, 0xffffffff, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
