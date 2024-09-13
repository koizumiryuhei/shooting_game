#include "ufo_boss.h"
#include "../../../../../utility/utility.h"
#include "../../../game_object.h"
#include "../../../scene_manager/scene_manager.h"
#include "../../../scene_manager/scene/game_main/game_main.h"

const int	CUfoBoss::m_width				= 384;
const int	CUfoBoss::m_height				= 252;
const float CUfoBoss::m_radius				= 126.0f;
const int	CUfoBoss::m_max_life			= 1999;
const int	CUfoBoss::m_random_interval		= 15;
const int	CUfoBoss::m_cercle_interval		= 240;
const float CUfoBoss::m_move_speed			= 1.0f;
const float CUfoBoss::m_move_switch_point	= 0.0f;
const int	CUfoBoss::m_spot_light_interval = 5;
const int	CUfoBoss::m_creat_aura_interval = 8;
const int	CUfoBoss::m_delete_time			= 6 * 60;

/*!
 *	コンストラクタ
 */
CUfoBoss::
CUfoBoss()
	: IUnit(m_width, m_height, m_radius, m_max_life, UNIT_CATEGORY::UFO, UNIT_ID::UFO_BOSS)
{
}

/*!
 *	デストラクタ
 */
CUfoBoss::
~CUfoBoss()
{
}

/*!
 *	初期化
 */
void
CUfoBoss::
Initialize(const vivid::Vector2& position)
{
	IUnit::Initialize(position);
	m_Velocity.x = m_move_speed;
	m_Velocity.y = m_move_speed;
	m_FireTime = m_random_interval;
	m_SpotLightTimer = 0;
	m_SpotLightCount = 0;
	m_CreatAuraTimer = 0;
	m_DeleteTimer = 0;
	m_AttackPattern = ATTACK_PATTERN::RANDOM;

	CEffectManager::GetInstance().Create(EFFECT_ID::EMERGENCY, vivid::Vector2::ZERO, 0xffffffff, 0.0f);
}

/*!
 *	描画
 */
void
CUfoBoss::
Draw()
{
	const vivid::Rect rect = { 0,0,m_width, m_height };
	const vivid::Vector2 anchor((float)m_width / 2.0f, (float)m_height / 2.0f);
	const vivid::Vector2 scale(1.0f, 1.0f);

	vivid::DrawTexture("data/boss.png", m_Position);
	vivid::DrawTexture("data/boss_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
	vivid::DrawTexture("data/boss_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD);
}

/*!
 *	攻撃
 */
void
CUfoBoss::
Attack()
{
	if (++m_CreatAuraTimer > m_creat_aura_interval)
	{
		m_CreatAuraTimer = 0;

		CEffectManager::GetInstance().Create(EFFECT_ID::AURA, m_Position, 0xcc440044, 0.0f);
	}

	m_AttackPattern = (ATTACK_PATTERN)((m_Life / 500) % 2);

	switch (m_AttackPattern)
	{
	case ATTACK_PATTERN::RANDOM:	RandomAttack();	break;
	case ATTACK_PATTERN::CERCLE:	CercleAttack();	break;
	}
}

/*!
 *	ランダム攻撃
 */
void 
CUfoBoss::
RandomAttack()
{
	if (--m_FireTime <= 0)
	{
		m_FireTime = m_random_interval;

		CUnitManager& um = CUnitManager::GetInstance();
		if (um.GetFighter())
		{
			const float radius = (float)(rand() % 180);
			CBulletManager& bm = CBulletManager::GetInstance();
			bm.Create(m_Category, BULLET_ID::BOSS, m_Position + vivid::Vector2((float)m_width / 2.0f, 0.0f), DEG_TO_RAD(radius), 2.0f);
		}
	}
}

/*!
 *	サークル攻撃
 */
void 
CUfoBoss::
CercleAttack()
{
	m_Position.x += m_Velocity.x;

	if (m_Position.x < m_move_switch_point)
	{
		m_Position.x = m_move_switch_point;
		m_Velocity.x *= -1.0f;
	}
	else if (m_Position.x + (float)m_width > (float)vivid::WINDOW_WIDTH - m_move_switch_point)
	{
		m_Position.x = (float)vivid::WINDOW_WIDTH - m_move_switch_point - (float)m_width;
		m_Velocity.x *= -1.0f;
	}

	if (--m_FireTime <= 0)
	{
		m_FireTime = m_cercle_interval;

		CUnitManager& um = CUnitManager::GetInstance();
		if (um.GetFighter())
		{
			const int bc = 10;
			const float radius = 360.0f / (float)bc;
			CBulletManager& bm = CBulletManager::GetInstance();
			for (int i = 0; i < bc; ++i)
			{
				bm.Create(m_Category, BULLET_ID::BOSS_HOMING, GetCenterPosition(), DEG_TO_RAD(i * radius), 3.0f);
			}
		}
	}
}

void 
CUfoBoss::
Dead()
{
	if (++m_SpotLightTimer > m_spot_light_interval && !(m_SpotLightCount > 15))
	{
		m_SpotLightTimer = 0;

		CEffectManager& effect = CEffectManager::GetInstance();
		float angle = rand() % 360;

		effect.Create(EFFECT_ID::BOSS_SPOT_LIGHT, GetCenterPosition(), 0xffffffff, DEG_TO_RAD(angle));

		++m_SpotLightCount;
	}

	if(++m_DeleteTimer > m_delete_time)
	{
		CEffectManager& effect = CEffectManager::GetInstance();
		effect.Delete(EFFECT_ID::BOSS_SPOT_LIGHT);
		effect.Delete(EFFECT_ID::BOSS_WHITE_EFFECT);

		const int destroy = 10;

		for (int i = 0; i < destroy; ++i)
			effect.Create(EFFECT_ID::BOSS_DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
		
		effect.Create(EFFECT_ID::BOSS_EXPLOSION_RING, GetCenterPosition(), 0xffffffff, 0.0f);

		CSoundManager::GetInstance().Play(SOUND_ID::BOSS_DESTORY, false);
		m_ActiveFlag = false;
	}
}
