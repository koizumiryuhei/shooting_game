#include "fighter_life_gauge.h"
#include "../../unit_manager/unit_manager.h"
#include "../../effect_manager/effect_manager.h"

const int				CFighterLifeGauge::m_width		= 150;
const int				CFighterLifeGauge::m_height		= 10;
const vivid::Vector2	CFighterLifeGauge::m_position	= vivid::Vector2(10.0f, 10.0f);
const vivid::Rect		CFighterLifeGauge::m_frame_rect = { 0,0,m_width, m_height };
const vivid::Rect		CFighterLifeGauge::m_bar_rect	= { 0,m_height,m_width, m_height * 2 };
const int				CFighterLifeGauge::m_bar_speed	= 1;

CFighterLifeGauge::
CFighterLifeGauge()
{
}

CFighterLifeGauge::
~CFighterLifeGauge()
{
}

void 
CFighterLifeGauge::
Initialize()
{
	m_Rect = m_bar_rect;
}

void 
CFighterLifeGauge::
Update()
{
	IUnit* fighter = CUnitManager::GetInstance().GetFighter();

	// 現在のライフの割合
	float rate = 0.0f;

	if (fighter)
	{
		rate = (float)fighter->GetLife() / (float)fighter->GetMaxLife();
	}

	int life = (int)(rate * (float)m_width);

	// ライフが減った分まで減らす
	if (m_Rect.right > life)
	{
		m_Rect.right -= m_bar_speed;

		CEffectManager::GetInstance().Create(EFFECT_ID::LIFE, vivid::Vector2(m_position.x + m_Rect.right, m_position.y), 0xff0000ff, 0.0f);
	}
}

void 
CFighterLifeGauge::
Draw()
{
	vivid::DrawTexture("data/life_gauge.png", m_position, 0xffffffff, m_frame_rect);
	vivid::DrawTexture("data/life_gauge.png", m_position, 0xffffffff, m_Rect);
}

void 
CFighterLifeGauge::
Finalize()
{
}
