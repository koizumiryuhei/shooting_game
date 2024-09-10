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
	void Initialize(const vivid::Vector2& pos)override;

	/*!
	 *	@brief	更新
	 */
	void Update()override;

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

	/*!
	 *	@brief	解放
	 */
	void Finalize()override;

	/*!
	 *	@brief	追尾ターゲットのセット
	 */
	void SetFollowTarget(IUnit* target) { m_FollowTarget = target; }

private:

	static const int	m_width;		//!< 幅
	static const int	m_height;		//!< 高さ
	static const float	m_radius;		//!< 半径

	IUnit*				m_FollowTarget;	//!< 追尾ターゲット

};