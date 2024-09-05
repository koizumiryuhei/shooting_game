#pragma once

#include "vivid.h"
#include "effect_id.h"
#include "../../../../utility/utility.h"

#define RAND_IN_360	rand() % 360

/*!
 *	@brief	エフェクト基底クラス
 */
class IEffect
{
public:

	/*!
	 *	@brief	コンストラクタ
	 */
	IEffect();

	/*!
	 *	@brief	コンストラクタ
	 */
	IEffect(EFFECT_ID id, int width, int height);

	/*!
	 *	@brief	デストラクタ
	 */
	virtual ~IEffect();

	/*!
	 *	@brief	初期化
	 */
	virtual void Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

	/*!
	 *	@brief	更新
	 */
	virtual void Update();

	/*!
	 *	@brief	描画
	 */
	virtual void Draw();

	/*!
	 *	@brief	解放
	 */
	virtual void Finalize();

	/*!
	 *	@brief	位置の取得
	 */
	vivid::Vector2 GetPosition();

	/*!
	 *	@brief	位置の設定
	 */
	void SetPosition(const vivid::Vector2& position);

	/*!
	 *	@brief	アクティブフラグの取得
	 */
	bool GetActive();

	/*!
	 *	@brief	アクティブフラグの設定
	 */
	void SetActive(bool active);

	/*!
	 *	@brief	識別番号取得
	 */
	EFFECT_ID GetID() { return m_id; }

protected:

	/*!
	 *	@brief	フェードアウト
	 * 
	 *	@param[in]	speed	フェード速度
	 */
	void FadeOut(const int& speed);

	const EFFECT_ID m_id;			//!< 識別番号

	int				m_Width;		//!< 幅
	int				m_Height;		//!< 高さ
	vivid::Vector2	m_Position;		//!< 位置
	unsigned int	m_Color;		//!< 色
	vivid::Vector2	m_Anchor;		//!< 基準点
	vivid::Rect		m_Rect;			//!< 読み込み範囲
	vivid::Vector2	m_Scale;		//!< 拡大率
	float			m_Rotation;		//!< 回転値
	bool			m_ActiveFlag;	//!< アクティブフラグ
};