#pragma once

#include "vivid.h"
#include "../effect.h"

class CChargeParticle : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CChargeParticle();

	/*!
	 *	@brief	デストラクタ
	 */
	~CChargeParticle();

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

	static const int			m_width;			//!< 幅
	static const int			m_height;			//!< 高さ
	static const int			m_fade_speed;		//!< フェード速度
	static const float			m_move_speed;		//!< 移動速度
	static const float			m_accelerator;		//!< 加速度
	static const float			m_max_accelerator;	//!< 最大加速度
	static const float			m_max_create_length;//!< 最長生成
	static const std::string	m_file_name;		//!< ファイル名

	vivid::Vector2				m_Velocity;			//!< 速度
	vivid::Vector2				m_Accelerator;		//!< 加速度

};