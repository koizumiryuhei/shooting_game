
#pragma once

#include "../unit.h"

enum class ATTACK_PATTERN
{
	RANDOM,
	CERCLE,
};

/*!
 *	@brief	UFO(�{�X)�N���X
 */
class CUfoBoss : public IUnit
{
public:

	/*!
	 *	@brief	�R���X�g���N�^
	 */
	CUfoBoss();

	/*!
	 *	@brief	�f�X�g���N�^
	 */
	~CUfoBoss();

	/*!
	 *	@brief	������
	 *
	 *	@param[in]	position	�������W
	 */
	void Initialize(const vivid::Vector2& position)override;

	/*!
	 *	@brief	�`��
	 */
	void Draw()override;

private:

	/*!
	 *	@brief	�U��
	 */
	void Attack()override;

	/*!
	 *	@brief	�����_���U��
	 */
	void RandomAttack();

	/*!
	 *	@brief	�T�[�N���U��
	 */
	void CercleAttack();

	/*!
	 *	@brief	���S
	 */
	void Dead()override;

	static const int	m_width;			//!< ��
	static const int	m_height;			//!< ����
	static const float	m_radius;			//!< ���a
	static const int	m_max_life;			//!< �ő僉�C�t
	static const int	m_random_interval;	//!< �����_���U���Ԋu
	static const int	m_cercle_interval;	//!< �T�[�N���U���Ԋu
	static const float	m_move_speed;		//!< �ړ����x
	static const float	m_move_switch_point;//!< �ړ��؂�ւ��n�_
	int					m_FireTime;			//!< �U���^�C�}�[
	ATTACK_PATTERN		m_AttackPattern;	//!< �U���p�^�[��
};