
#pragma once

#include "vivid.h"
#include "fighter_life_gauge/fighter_life_gauge.h"

/*!
 *	@brief	UIマネージャークラス
 */
class CUIManager
{
public:

	/*!
	 *	@brief	インスタンスの取得
	 * 
	 *	@return	UIマネージャークラスインスタンス
	 */
	static CUIManager& GetInstance();

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

private:

	/*!
	 *	@brief	コンストラクタ
	 */
	CUIManager();

	/*!
	 *	@brief	コピーコンストラクタ
	 */
	CUIManager(const CUIManager& rhs);

	/*!
	 *	@brief	デストラクタ
	 */
	~CUIManager();

	/*!
	 *	@brief	代入演算子
	 */
	CUIManager& operator=(const CUIManager& rhs);

	CFighterLifeGauge m_FighterLifeGauge;	//!< 戦闘機のライフゲージオブジェクト
};