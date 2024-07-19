#include "boss_homing_bullet.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../unit_manager/unit/unit.h"
#include "../../../../../utility/utility.h"

const int	CBossHomingBullet::m_width = 96;
const int	CBossHomingBullet::m_height = 96;
const float	CBossHomingBullet::m_radius = 48.0f;
const float CBossHomingBullet::m_initail_velocity = 2.0f;
const float CBossHomingBullet::m_accelerator = 0.4f;
const float CBossHomingBullet::m_max_speed = 15.0f;
const int	CBossHomingBullet::m_time_to_standby = 40;
const int	CBossHomingBullet::m_max_time_to_launch = 60;

CBossHomingBullet::
CBossHomingBullet()
	: IBullet(m_width, m_height, m_radius)
	, m_time_to_launch(rand() % m_max_time_to_launch)
	, m_Speed(0.0f)
	, m_Angle(0.0f)
{
}

CBossHomingBullet::
~CBossHomingBullet()
{
}

void 
CBossHomingBullet::
Initialize(UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed)
{
	IBullet::Initialize(category, position, direction, speed);

	m_Speed = speed;
	m_Angle = direction;
	m_TimerToStandby = 0;
	m_TimerToLaunch = 0;
	m_BulletState = BULLET_STATE::BEFORE_STANDBY;
}

void 
CBossHomingBullet::
Update()
{
	switch (m_BulletState)
	{
	case BULLET_STATE::BEFORE_STANDBY:	BeforeStandby();	break;
	case BULLET_STATE::STANDBY:			Standby();			break;
	case BULLET_STATE::LAUNCH:			Launch();			break;
	}

	if (m_Speed > m_max_speed)
		m_Speed = m_max_speed;

	m_Velocity.x = m_Speed * cos(m_Angle);
	m_Velocity.y = m_Speed * sin(m_Angle);

	m_Position += m_Velocity;

	CheckArea();

	m_Rotation = atan2(m_Velocity.y, m_Velocity.x);
}

void 
CBossHomingBullet::
Draw()
{
	vivid::DrawTexture("data/boss_bullet_bloom.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/boss_bullet.png", m_Position, 0xffffffff, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}

void 
CBossHomingBullet::
BeforeStandby()
{
	if (++m_TimerToStandby > m_time_to_standby)
	{
		m_TimerToStandby = 0;
		m_Speed = 0.0f;
		m_BulletState = BULLET_STATE::STANDBY;
	}
}

void 
CBossHomingBullet::
Standby()
{
	if (++m_TimerToLaunch > m_time_to_launch)
	{
		m_TimerToLaunch = 0;
		m_Speed = m_initail_velocity;

		IUnit* unit = CUnitManager::GetInstance().GetFighter();

		if(unit)
		{
			vivid::Vector2 v = unit->GetCenterPosition() - GetCenterPosition();
			m_Angle = atan2(v.y, v.x);
		}

		m_BulletState = BULLET_STATE::LAUNCH;
	}
}

void 
CBossHomingBullet::
Launch()
{
	m_Speed += m_accelerator;
}
