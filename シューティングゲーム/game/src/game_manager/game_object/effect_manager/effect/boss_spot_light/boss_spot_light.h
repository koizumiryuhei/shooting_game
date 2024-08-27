#pragma once

#include "vivid.h"
#include "../effect.h"

class CBossSpotLight : public IEffect
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CBossSpotLight();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CBossSpotLight();

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

	float				m_RotationSpeed;

};