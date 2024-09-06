
#pragma once

#include "../unit.h"

enum class ATTACK_PATTERN
{
	RANDOM,
	CERCLE,
};

/*!
 *	@brief	UFO(ボス)クラス
 */
class CUfoBoss : public IUnit
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	CUfoBoss();

	/*!
	 *	@brief	デストラクタ
	 */
	~CUfoBoss();

	/*!
	 *	@brief	初期化
	 *
	 *	@param[in]	position	初期座標
	 */
	void Initialize(const vivid::Vector2& position)override;

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

private:

	/*!
	 *	@brief	攻撃
	 */
	void Attack()override;

	/*!
	 *	@brief	ランダム攻撃
	 */
	void RandomAttack();

	/*!
	 *	@brief	サークル攻撃
	 */
	void CercleAttack();

	/*!
	 *	@brief	死亡
	 */
	void Dead()override;

	static const int	m_width;				//!< 幅
	static const int	m_height;				//!< 高さ
	static const float	m_radius;				//!< 半径
	static const int	m_max_life;				//!< 最大ライフ
	static const int	m_random_interval;		//!< ランダム攻撃間隔
	static const int	m_cercle_interval;		//!< サークル攻撃間隔
	static const float	m_move_speed;			//!< 移動速度
	static const float	m_move_switch_point;	//!< 移動切り替え地点
	static const int	m_spot_light_interval;	//!< スポットライト生成間隔
	static const int	m_creat_aura_interval;	//!< オーラ作成間隔
	static const int	m_delete_time;			//!< 消滅時間

	int					m_FireTime;				//!< 攻撃タイマー
	int					m_SpotLightTimer;		//!< スポットライトタイマー
	int					m_SpotLightCount;		//!< スポットライト生成数
	int					m_CreatAuraTimer;		//!< オーラ生成時間
	int					m_DeleteTimer;			//!< 消滅タイマー1
	ATTACK_PATTERN		m_AttackPattern;		//!< 攻撃パターン

};