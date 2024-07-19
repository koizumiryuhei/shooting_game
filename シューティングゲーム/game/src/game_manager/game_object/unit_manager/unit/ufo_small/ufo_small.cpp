#include "ufo_small.h"
#include "../../../../../utility/utility.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"
#include "../fighter/fighter.h"

const int	CUfoSmall::m_width			= 32;
const int	CUfoSmall::m_height			= 32;
const float CUfoSmall::m_radius			= 16.0f;
const int	CUfoSmall::m_max_life		= 10;
const int	CUfoSmall::m_fire_interval	= 90;
const float CUfoSmall::m_move_speed		= 1.0f;

/*!
 *	コンストラクタ
 */
CUfoSmall::CUfoSmall()
	: IUnit(m_width, m_height, m_radius, m_max_life, UNIT_CATEGORY::UFO, UNIT_ID::UFO_SMALL)
{
}

/*!
 *	デストラクタ
 */
CUfoSmall::~CUfoSmall()
{
}

/*!
 *	初期化
 */
void CUfoSmall::Initialize(const vivid::Vector2& position)
{
	IUnit::Initialize(position);
	m_Velocity.y = m_move_speed;
	m_FireTime = m_fire_interval;
}

/*!
 *	描画
 */
void CUfoSmall::Draw()
{
	const vivid::Rect rect = { 0,0,m_width, m_height };
	const vivid::Vector2 anchor((float)m_width / 2.0f, (float)m_height / 2.0f);
	const vivid::Vector2 scale(1.0f, 1.0f);

	vivid::DrawTexture("data/ufo_small.png", m_Position);
	vivid::DrawTexture("data/ufo_small_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/ufo_small_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
}

/*!
 *	攻撃
 */
void CUfoSmall::Attack()
{
	m_Position += m_Velocity;
	if (--m_FireTime <= 0)
	{
		m_FireTime = m_fire_interval;

		CUnitManager& um = CUnitManager::GetInstance();

		if (um.GetFighter())
		{
			vivid::Vector2 fp = um.GetFighter()->GetPosition();
			const float radius = atan2(fp.y - m_Position.y, fp.x - m_Position.x);
			CBulletManager& bm = CBulletManager::GetInstance();
			bm.Create(m_Category, BULLET_ID::NORMAL, GetCenterPosition(), radius, 2.0f);
		}
	}
}
