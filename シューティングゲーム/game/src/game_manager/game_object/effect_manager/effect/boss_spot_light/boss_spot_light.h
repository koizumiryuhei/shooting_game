#pragma once

#include "vivid.h"
#include "../effect.h"

class CBossSpotLight : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CBossSpotLight();

	/*!
	 *	@brief	デストラクタ
	 */
	~CBossSpotLight();

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
	static const int			m_color_table_count;
	static const unsigned int	m_color_table[];
	static const std::string	m_file_name;	//!< ファイル名

	float						m_RotationSpeed;

};