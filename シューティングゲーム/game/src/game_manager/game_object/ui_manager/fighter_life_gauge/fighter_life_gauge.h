
#pragma once

#include "vivid.h"

/*!
 *	@brief	ファイターライフゲージクラス
 */
class CFighterLifeGauge
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CFighterLifeGauge();

	/*!
	 *	@brief	デストラクタ
	 */
	~CFighterLifeGauge();

	/*!
	 *	@brief	初期化
	 */
	void Initialize();
	
	/*!
	 *	@brief	更新
	 */
	void Update();

	/*!
	 *	@brief	描画
	 */
	void Draw();

	/*!
	 *	@brief	解放
	 */
	void Finalize();

private:

	static const int			m_width;		//!< 幅
	static const int			m_height;		//!< 高さ
	static const vivid::Vector2	m_position;		//!< 位置
	static const vivid::Rect	m_frame_rect;	//!< 枠の読み込み範囲
	static const vivid::Rect	m_bar_rect;		//!< バーの読み込み範囲
	static const int			m_bar_speed;	//!< バーの移動速度
	
	vivid::Rect					m_Rect;			//!< バーの読み込み範囲
};