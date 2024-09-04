
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CHomingBullet : public IBullet
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CHomingBullet();

	/*!
	 *	@brief	デストラクタ
	 */
	~CHomingBullet();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  category  ユニット識別子
	 *  @param[in]  position    位置
	 *  @param[in]  direction   向き
	 *  @param[in]  speed       速さ
	 */
	void Initialize(UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed)override;

	/*!
	 *	@brief	更新
	 */
	void Update()override;

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

private:

	static const int	m_width;			//!< 幅
	static const int	m_height;			//!< 高さ
	static const float	m_radius;			//!< 半径
	static const float	m_accelerator;		//!< 加速
	static const float	m_max_speed;		//!< 最高速度
	static const float	m_homing_angle;		//!< ホーミング角度
	static const int	m_max_homing_time;	//!< ホーミングする最大時間
	static const int	m_effect_interval;	//!< エフェクト生成間隔

	float				m_Speed;			//!< 速さ
	float				m_Angle;			//!< 向き
	int					m_HomingTime;		//!< ホーミングする時間1
	int					m_EffectTimer;		//!< エフェクトタイマー

};
