#include "fighter_option.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../../../utility/utility.h"

const int	CFighterOption::m_width			= 16;
const int	CFighterOption::m_height		= 16;
const float CFighterOption::m_radius		= 8;
const float	CFighterOption::m_move_speed	= 2.0f;
const float	CFighterOption::m_follow_angle	= 2.5f;

CFighterOption::
CFighterOption()
	: IUnit(m_width, m_height, m_radius, 0, UNIT_CATEGORY::FIGHTER, UNIT_ID::FIGHTER)
	, m_FollowTarget(nullptr)
{
}

CFighterOption::
~CFighterOption()
{
}

void 
CFighterOption::
Initialize(const vivid::Vector2& pos)
{
	IUnit::Initialize(pos);

	m_Position.x = rand() % (vivid::WINDOW_WIDTH - m_width) + m_width;

	m_Angle = DEG_TO_RAD(270.0f);
}

void 
CFighterOption::
Update()
{
	IUnit::Update();
}

void 
CFighterOption::
Draw()
{
	vivid::Rect rect		= { 0,0,m_width,m_height };
	vivid::Vector2 anchor	= { (float)m_width / 2.0f, (float)m_height / 2.0f };
	vivid::Vector2 scale	= vivid::Vector2::ONE;

	vivid::DrawTexture("data\\fighter_option.png", m_Position);
	vivid::DrawTexture("data\\fighter_option_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data\\fighter_option_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
}

void 
CFighterOption::
Finalize()
{
}

void 
CFighterOption::
Fire()
{
	CBulletManager::GetInstance().Create(m_Category, BULLET_ID::NORMAL, m_Position + vivid::Vector2(m_width / 2.0f, 0.0f), DEG_TO_RAD(270.0f), 10.0f);
}

void
CFighterOption::
Appear(void)
{
    m_Position.y -= m_move_speed;

	if (m_Position.y < (float)vivid::WINDOW_HEIGHT)
		m_UnitState = UNIT_STATE::ATTACK;
}

void 
CFighterOption::
Attack(void)
{
	if (m_FollowTarget)
	{
		vivid::Vector2 v = m_FollowTarget->GetCenterPosition() - GetCenterPosition();
		float dir = vivid::Vector2::Cross(v, m_Velocity);
		if (dir > 0.0f)
			m_Angle -= DEG_TO_RAD(m_follow_angle);
		else
			m_Angle += DEG_TO_RAD(m_follow_angle);
	}

	m_Velocity.x = cos(m_Angle) * m_move_speed;
	m_Velocity.y = sin(m_Angle) * m_move_speed;

	m_Position += m_Velocity;
}

void 
CFighterOption::
Dead(void)
{
}
