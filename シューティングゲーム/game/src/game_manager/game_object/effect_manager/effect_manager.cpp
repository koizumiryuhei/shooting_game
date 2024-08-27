#include "effect_manager.h"
#include "effect/effect.h"
#include "effect/charge_effect/charge_effect.h"
#include "effect/charge_particle/charge_particle.h"
#include "effect/trafectory_effect/trafectory_effect.h"
#include "effect/boss_spot_light/boss_spot_light.h"

CEffectManager& 
CEffectManager::
GetInstance()
{
	static CEffectManager instance;
	return instance;
}

void 
CEffectManager::
Initialize()
{
	m_EffectList.clear();
}

void 
CEffectManager::
Update()
{
	if (m_EffectList.empty())return;

	EFFECT_LIST::iterator it = m_EffectList.begin();

	while (it != m_EffectList.end())
	{
		IEffect* effect = static_cast<IEffect*>(*it);

		effect->Update();

		if (!effect->GetActive())
		{
			effect->Finalize();

			delete effect;

			it = m_EffectList.erase(it);

			continue;
		}

		++it;
	}
}

void 
CEffectManager::
Draw()
{
	if (m_EffectList.empty())return;

	EFFECT_LIST::iterator it = m_EffectList.begin();

	while (it != m_EffectList.end())
	{
		(*it)->Draw();

		++it;
	}
}

void 
CEffectManager::
Finalize()
{
	if (m_EffectList.empty())return;

	EFFECT_LIST::iterator it = m_EffectList.begin();

	while (it != m_EffectList.end())
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}

	m_EffectList.clear();
}

void 
CEffectManager::
Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation)
{
	IEffect* effect = nullptr;

	switch (id)
	{
	case EFFECT_ID::TRAFECTORY:			effect = new CTrafectoryEffect();	break;
	case EFFECT_ID::DESTORY:			break;
	case EFFECT_ID::HIT:				break;
	case EFFECT_ID::DAMAGE:				break;
	case EFFECT_ID::HOMING:				break;
	case EFFECT_ID::AURA:				break;
	case EFFECT_ID::LIFE:				break;
	case EFFECT_ID::CHARGE_PARTICLE:	effect = new CChargeParticle();		break;
	case EFFECT_ID::CHARGE_EFFECT:		effect = new CChargeEffect();		break;
	case EFFECT_ID::EMERGENCY:			break;
	case EFFECT_ID::BOSS_WHITE_EFFECT:	break;
	case EFFECT_ID::BOSS_SPOT_LIGHT:	effect = new CBossSpotLight();		break;
	case EFFECT_ID::BOSS_DESTORY:		break;
	}

	if (!effect)return;

	effect->Initialize(pos, color, rotation);

	m_EffectList.push_back(effect);
}
