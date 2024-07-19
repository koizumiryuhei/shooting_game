#include "ufo_large.h"
#include "../../../../../utility/utility.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"

const int	CUfoLarge::m_width			= 64;
const int	CUfoLarge::m_height			= 42;
const float CUfoLarge::m_radius			= 32.0f;
const int	CUfoLarge::m_max_life		= 30;
const int	CUfoLarge::m_fire_interval	= 120;
const float CUfoLarge::m_move_speed		= 1.0f;

/*!
 *	コンストラクタ
 */
CUfoLarge::
CUfoLarge()
	: IUnit(m_width, m_height, m_radius, m_max_life, UNIT_CATEGORY::UFO, UNIT_ID::UFO_LARGE)
{
}

/*!
 *	デストラクタ
 */
CUfoLarge::
~CUfoLarge()
{
}

/*!
 *	初期化
 */
void
CUfoLarge::
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
CUfoLarge::
Draw()
{
	const vivid::Rect rect = { 0,0,m_width, m_height };
	const vivid::Vector2 anchor((float)m_width / 2.0f, (float)m_height / 2.0f);
	const vivid::Vector2 scale(1.0f, 1.0f);

	vivid::DrawTexture("data/ufo_large.png", m_Position);
	vivid::DrawTexture("data/ufo_large_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/ufo_large_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
}

/*!
 *	攻撃
 */
void
CUfoLarge::
Attack()
{
	m_Position += m_Velocity;
	if (--m_FireTime <= 0)
	{
		m_FireTime = m_fire_interval;

		CUnitManager& um = CUnitManager::GetInstance();
		if(um.GetFighter())
		{
			const int bc = 9;
			const float radius = 360.0f / (float)bc;
			CBulletManager& bm = CBulletManager::GetInstance();
			for (int i = 0; i < bc; ++i)
			{
				bm.Create(m_Category, BULLET_ID::NORMAL, GetCenterPosition(), (i * radius) * 3.14f / 180.0f, 2.0f);
			}
		}
	}
}
