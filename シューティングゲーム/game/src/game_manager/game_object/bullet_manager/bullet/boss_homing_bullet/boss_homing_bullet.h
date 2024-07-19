
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CBossHomingBullet : public IBullet
{
public:
	/*!
	 *	@brief	コンストラクタ
	 */
	CBossHomingBullet();

	/*!
	 *	@brief	デストラクタ
	 */
	~CBossHomingBullet();

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

	/*!
	 *	@brief	待機前
	 */
	void BeforeStandby();

	/*!
	 *	@brief	発射待機
	 */
	void Standby();

	/*!	
	 *	@brief	発射
	 */
	void Launch();

	enum class BULLET_STATE
	{
		BEFORE_STANDBY,
		STANDBY,
		LAUNCH,
	};

	static const int	m_width;				//!< 幅
	static const int	m_height;				//!< 高さ
	static const float	m_radius;				//!< 半径
	static const float	m_initail_velocity;		//!< 初速
	static const float	m_accelerator;			//!< 加速
	static const float	m_max_speed;			//!< 最高速度
	static const int	m_time_to_standby;		//!< 待機までの時間
	static const int	m_max_time_to_launch;	//!< 発射までの最大時間
	const int			m_time_to_launch;		//!< 発射までの時間
	float				m_Speed;				//!< 速さ
	float				m_Angle;				//!< 向き
	int					m_TimerToStandby;		//!< 待機までのタイマー
	int					m_TimerToLaunch;		//!< 発射までのタイマー
	BULLET_STATE		m_BulletState;			//!< 弾状態
};