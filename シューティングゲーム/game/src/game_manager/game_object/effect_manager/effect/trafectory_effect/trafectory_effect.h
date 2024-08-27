#pragma once

#include "vivid.h"
#include "../effect.h"

class CTrafectoryEffect : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CTrafectoryEffect();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CTrafectoryEffect();

	/*!
	 *	@brief	������
	 */
	void Initialize(const vivid::Vector2& position, unsigned int color, float rotation)override;

	/*!
	 *	@brief	�X�V
	 */
	void Update()override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:

	static const int	m_width;
	static const int	m_height;
	static const int	m_fade_speed;

};