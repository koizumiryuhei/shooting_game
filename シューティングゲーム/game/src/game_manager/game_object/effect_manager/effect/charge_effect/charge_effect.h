#pragma once

#include "vivid.h"
#include "../effect.h"

class CChargeEffect : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CChargeEffect();

	/*!
	 *	@brief	デストラクタ
	 */
	~CChargeEffect();

	/*!
	 *	@brief	初期化
	 */
	void Initialize(const vivid::Vector2& position, unsigned int color, float rotation)override;

	/*!
	 *	@brief	更新
	 */
	void Update()override;

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

private:

	static const int			m_width;		//!< 幅
	static const int			m_height;		//!< 高さ
	static const int			m_fade_speed;	//!< フェード速度
	static const float			m_scale_speed;	//!< 拡大速度
	static const std::string	m_file_name;	//!< ファイル名
};