#pragma once

#include "../effect.h"

class CEmergencyEffect : public IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CEmergencyEffect();

	/*!
	 *	@brief	デストラクタ
	 */
	~CEmergencyEffect();

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

	enum class FADE_STATE
	{
		FADE_IN,
		FADE_OUT,
	};

	static const int			m_width;
	static const int			m_height;
	static const int			m_warning_width;
	static const int			m_warning_height;
	static const int			m_max_alpha;
	static const int			m_min_alpha;
	static const int			m_fade_speed;
	static const int			m_flash_count;
	static const int			m_max_bg_count;
	static const float			m_scroll_speed;
	static const std::string	m_emergency_file_name;
	static const std::string	m_warning_file_name;
	static const std::string	m_white_file_name;

	vivid::Vector2*				m_WarningPosition1;
	vivid::Vector2*				m_WarningPosition2;
	int							m_FlashCounter;
	FADE_STATE					m_FadeState;

};