#pragma once

/*
 *	@file	fighter_option.h
 *	@brief	小型戦闘機
 *	@author	RyuheiKoizumi
 *	@date	2024/9/10
 */

#include "vivid.h"
#include "../../unit.h"

class CFighterOption : public IUnit
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CFighterOption();

	/*!
	 *	@brief	デストラクタ
	 */
	~CFighterOption();

	/*!
	 *	@brief	初期化
	 */
	void	Initialize(const vivid::Vector2& pos)override;

	/*!
	 *	@brief	更新
	 */
	void	Update(void)override;

	/*!
	 *	@brief	描画
	 */
	void	Draw(void)override;

	/*!
	 *	@brief	解放
	 */
	void	Finalize(void)override;

	/*!
	 *	@brief	追尾ターゲットのセット
	 */
	void	SetFollowTarget(IUnit* target) { m_FollowTarget = target; }

	/*!
	 *	@brief	射撃
	 */
	void	Fire();

private:

	/*!
	 *  @brief      登場
	 */
	void	Appear(void)override;

	/*!
	 *  @brief      攻撃
	 */
	void    Attack(void)override;

	/*!
	 *  @brief      死亡
	 */
	void    Dead(void)override;

	static const int	m_width;		//!< 幅
	static const int	m_height;		//!< 高さ
	static const float	m_radius;		//!< 半径
	static const float	m_move_speed;	//!< 移動速度
	static const float	m_follow_angle;	//!< 追尾角度

	IUnit*				m_FollowTarget;	//!< 追尾ターゲット
	float				m_Angle;		//!< 角度

};