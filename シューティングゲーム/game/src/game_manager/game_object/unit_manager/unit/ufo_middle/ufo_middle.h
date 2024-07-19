
#pragma once

#include "../unit.h"

/*!
 *	@brief	UFO(中)クラス
 */
class CUfoMiddle : public IUnit
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CUfoMiddle();

	/*!
	 *	@brief	デストラクタ
	 */
	~CUfoMiddle();

	/*!
	 *	@brief	初期化
	 *
	 *	@param[in]	position	初期座標
	 */
	void Initialize(const vivid::Vector2& position)override;

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

private:

	/*!
	 *	@brief	攻撃
	 */
	void Attack()override;

	static const int	m_width;			//!< 幅
	static const int	m_height;			//!< 高さ
	static const float	m_radius;			//!< 半径
	static const int	m_max_life;			//!< 最大ライフ
	static const int	m_fire_interval;	//!< 攻撃間隔
	static const float	m_move_speed;		//!< 移動速度
	int					m_FireTime;			//!< 攻撃タイマー
};