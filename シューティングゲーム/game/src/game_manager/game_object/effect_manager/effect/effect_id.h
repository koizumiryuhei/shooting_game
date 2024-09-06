#pragma once

// エフェクトID
enum class EFFECT_ID
{
	DUMMY,				//!< ダミー

	TRAFECTORY,			//!< 軌跡エフェクト
	DESTORY,			//!< 撃破エフェクト
	HIT,				//!< ヒットエフェクト
	DAMAGE,				//!< ダメージエフェクト
	HOMING,				//!< ホーミングエフェクト
	AURA,				//!< オーラエフェクト
	LIFE,				//!< ライフエフェクト
	CHARGE_PARTICLE,	//!< チャージパーティクルエフェクト
	CHARGE_EFFECT,		//!< チャージエフェクト
	EMERGENCY,			//!< 警告エフェクト
	BOSS_WHITE_EFFECT,	//!< ボスホワイトエフェクト
	BOSS_SPOT_LIGHT,	//!< ボススポットライト
	BOSS_DESTORY,		//!< ボス撃破エフェクト
	EXPLOSION_RING,		//!< リングエフェクト
	BOSS_EXPLOSION_RING,//!< ボスリングエフェクト
};