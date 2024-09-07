#include "effect_manager.h"
#include "effect/effect.h"
#include "effect/charge_effect/charge_effect.h"
#include "effect/charge_particle/charge_particle.h"
#include "effect/trafectory_effect/trafectory_effect.h"
#include "effect/boss_spot_light/boss_spot_light.h"
#include "effect/life_effect/life_effect.h"
#include "effect/homing_effect/homing_effect.h"
#include "effect/hit_effect/hit_effect.h"
#include "effect/emergency_effect/emergency_effect.h"
#include "effect/destory_effect/destory_effect.h"
#include "effect/boss_destory_effect/boss_destory_effect.h"
#include "effect/explosion_ring/explosion_ring.h"
#include "effect/boss_explosion_ring/boss_explosion_ring.h"
#include "effect/boss_white_effect/boss_white_effect.h"
#include "effect/aura_effect/aura_effect.h"
#include "effect/damage_effect/damage_effect.h"

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
	case EFFECT_ID::TRAFECTORY:				effect = new CTrafectoryEffect();	break;
	case EFFECT_ID::DESTORY:				effect = new CDestroyEffect();		break;
	case EFFECT_ID::HIT:					effect = new CHitEffect();			break;
	case EFFECT_ID::DAMAGE:					effect = new CDamageEffect();		break;
	case EFFECT_ID::HOMING:					effect = new CHomingEffect();		break;
	case EFFECT_ID::AURA:					effect = new CAuraEffect();			break;
	case EFFECT_ID::LIFE:					effect = new CLifeEffect();			break;
	case EFFECT_ID::CHARGE_PARTICLE:		effect = new CChargeParticle();		break;
	case EFFECT_ID::CHARGE_EFFECT:			effect = new CChargeEffect();		break;
	case EFFECT_ID::EMERGENCY:				effect = new CEmergencyEffect();	break;
	case EFFECT_ID::BOSS_WHITE_EFFECT:		effect = new CBossWhiteEffect();	break;
	case EFFECT_ID::BOSS_SPOT_LIGHT:		effect = new CBossSpotLight();		break;
	case EFFECT_ID::BOSS_DESTORY:			effect = new CBossDestroyEffect();	break;
	case EFFECT_ID::EXPLOSION_RING:			effect = new CExplosionRing();		break;
	case EFFECT_ID::BOSS_EXPLOSION_RING:	effect = new CBossExplosionRing();  break;
	}

	if (!effect)return;

	effect->Initialize(pos, color, rotation);

	m_EffectList.push_back(effect);
}

void 
CEffectManager::
Delete(EFFECT_ID id)
{
	if (m_EffectList.empty())return;

	EFFECT_LIST::iterator it = m_EffectList.begin();

	while (it != m_EffectList.end())
	{
		IEffect* effect = (*it);

		if (effect->GetID() == id)
		{
			effect->Finalize();

			delete effect;

			it = m_EffectList.erase(it);

			continue;
		}

		++it;
	}
}
