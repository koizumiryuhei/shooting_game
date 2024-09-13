#include "ufo_middle.h"
#include "../../../../../utility/utility.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"

const int	CUfoMiddle::m_width			= 64;
const int	CUfoMiddle::m_height		= 32;
const float CUfoMiddle::m_radius		= 32.0f;
const int	CUfoMiddle::m_max_life		= 24;
const int	CUfoMiddle::m_fire_interval = 180;
const float CUfoMiddle::m_move_speed	= 1.0f;

/*!
 *	コンストラクタ
 */
CUfoMiddle::
CUfoMiddle()
	: IUnit(m_width, m_height, m_radius, m_max_life, UNIT_CATEGORY::UFO, UNIT_ID::UFO_MIDDLE)
{
}

/*!
 *	デストラクタ
 */
CUfoMiddle::
~CUfoMiddle()
{
}

/*!
 *	初期化
 */
void 
CUfoMiddle::
Initialize(const vivid::Vector2& position)
{
	IUnit::Initialize(position);
	m_Velocity.y = m_move_speed;
	m_FireTime = m_fire_interval;
}

/*!
 *	描画
 */
void 
CUfoMiddle::
Draw()
{
	const vivid::Rect rect = { 0,0,m_width, m_height };
	const vivid::Vector2 anchor((float)m_width / 2.0f, (float)m_height / 2.0f);
	const vivid::Vector2 scale(1.0f, 1.0f);

	vivid::DrawTexture("data/ufo_middle.png", m_Position);
	vivid::DrawTexture("data/ufo_middle_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/ufo_middle_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
}

/*!
 *	攻撃
 */
void 
CUfoMiddle::
Attack()
{
	m_Position += m_Velocity;
	if (--m_FireTime <= 0)
	{
		m_FireTime = m_fire_interval;

		CUnitManager& um = CUnitManager::GetInstance();
		if(um.GetFighter())
		{
			CBulletManager& bm = CBulletManager::GetInstance();
			bm.Create(m_Category, BULLET_ID::HOMING, GetCenterPosition(), DEG_TO_RAD(270.0f), 2.0f);
			bm.Create(m_Category, BULLET_ID::HOMING, GetCenterPosition(), DEG_TO_RAD(260.0f), 2.0f);
			bm.Create(m_Category, BULLET_ID::HOMING, GetCenterPosition(), DEG_TO_RAD(280.0f), 2.0f);
		}
	}
}
