#pragma once

/*
 *	@file	setting.h
 *	@brief	設定
 *	@author	RyuheiKoizumi
 *	@date	2024/9/13
 */

#include "vivid.h"

class CSetting
{
public:

	/*!
	 *	@brief	インスタンスの取得
	 */
	static CSetting& GetInstance(void);

	/*!
	 *	@brief	初期化
	 */
	void Initialize(void);

	/*!
	 *	@brief	描画
	 */
	void Draw(void);

	/*!
	 *	@brief	変数の設定
	 */
	void Setting(void);

private:

	/*!
	 *	@brief	コンストラクタ
	 */
	CSetting();

	/*!
	 *	@brief	コピーコンストラクタ
	 */
	CSetting(const CSetting& rhs);

	/*!
	 *	@brief	デストラクタ
	 */
	~CSetting();

	/*!
	 *	@brief	参照演算子
	 */
	CSetting& operator=(const CSetting& rhs);

	/*!
	 *	@brief	ポイントとの当たり判定
	 */
	void CheckPointCollision(vivid::Vector2 pos);

	static const int			m_var_width;
	static const int			m_var_height;
	static const int			m_point_width;
	static const int			m_point_height;
	static const vivid::Vector2 m_accelerator_var_position;
	static const vivid::Vector2 m_max_accelerator_var_position;
	static const vivid::Vector2 m_point_anchor;
	static const float			m_point_radius;

	vivid::Vector2				m_AcceleratorPointPosition;
	vivid::Vector2				m_MaxAcceleratorPointPosition;
	bool						m_SelectAcceleratorPoint;
	bool						m_SelectMaxAcceleratorPoint;

};