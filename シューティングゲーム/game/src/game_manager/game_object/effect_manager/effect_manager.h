#pragma once

#include <list>
#include "vivid.h"
#include "effect/effect_id.h"

class IEffect;

/*!
 *	@brief	エフェクトマネージャークラス
 */
class CEffectManager
{
public:

	/*!
	 *	@brief	インスタンスの取得
	 */
	static CEffectManager& GetInstance();

	/*!
	 *	@brief	初期化
	 */
	void Initialize();

	/*!
	 *	@brief	更新
	 */
	void Update();

	/*!
	 *	@brief	描画
	 */
	void Draw();

	/*!
	 *	@brief	解放
	 */
	void Finalize();

	/*!
	 *	@brief	エフェクトの生成
	 */
	void Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation);

	/*!
	 *	@brief	エフェクト削除
	 */
	void Delete(EFFECT_ID id);

private:

	/*!
	 *	@brief	コンストラクタ
	 */
	CEffectManager() = default;

	/*!
	 *	@brief	コピーコンストラクタ
	 */
	CEffectManager(const CEffectManager& rhs) = delete;

	/*!
	 *	@brief	デストラクタ
	 */
	~CEffectManager() = default;

	/*!
	 *	@brief	参照演算子
	 */
	CEffectManager& operator=(const CEffectManager& rhs) = delete;

	// エフェクトリスト型の定義
	using EFFECT_LIST = std::list<IEffect*>;
	EFFECT_LIST m_EffectList;	//!< エフェクトリスト
};