#pragma once

#include "../effect.h"

class CExplosionRing : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CExplosionRing();

	/*!
	 *	@brief	デストラクタ
	 */
	~CExplosionRing();

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
	static const int			m_fade_speed;
	static const float			m_scale_speed;
	static const std::string	m_file_name;
	static const std::string	m_bloom_file_name;

};