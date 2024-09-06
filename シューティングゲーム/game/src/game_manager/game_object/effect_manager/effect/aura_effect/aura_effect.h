#pragma once

#include "../effect.h"

class CAuraEffect : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CAuraEffect();

	/*!
	 *	@brief	デストラクタ
	 */
	~CAuraEffect();

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
	static const float			m_move_speed;
	static const std::string	m_file_name;

};