#pragma once

#include "../effect.h"

class CLifeEffect : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CLifeEffect();

	/*!
	 *	@brief	デストラクタ
	 */
	~CLifeEffect();

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

	static const int			m_width;
	static const int			m_height;
	static const int			m_one_rotation;
	static const int			m_max_rotation;
	static const int			m_min_rotation;
	static const float			m_speed;
	static const int			m_fade_speed;
	static const std::string	m_file_name;	//!< ファイル名

	vivid::Vector2				m_Velocity;
	float						m_RotationSpeed;

};