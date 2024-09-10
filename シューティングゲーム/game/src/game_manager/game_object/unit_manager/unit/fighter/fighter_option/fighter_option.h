#pragma once

/*
 *	@file	fighter_option.h
 *	@brief	���^�퓬�@
 *	@author	RyuheiKoizumi
 *	@date	2024/9/10
 */

#include "vivid.h"
#include "../../unit.h"

class CFighterOption : public IUnit
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CFighterOption();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CFighterOption();

	/*!
	 *	@brief	������
	 */
	void Initialize(const vivid::Vector2& pos)override;

	/*!
	 *	@brief	�X�V
	 */
	void Update()override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

	/*!
	 *	@brief	���
	 */
	void Finalize()override;

	/*!
	 *	@brief	�ǔ��^�[�Q�b�g�̃Z�b�g
	 */
	void SetFollowTarget(IUnit* target) { m_FollowTarget = target; }

private:

	static const int	m_width;		//!< ��
	static const int	m_height;		//!< ����
	static const float	m_radius;		//!< ���a

	IUnit*				m_FollowTarget;	//!< �ǔ��^�[�Q�b�g

};