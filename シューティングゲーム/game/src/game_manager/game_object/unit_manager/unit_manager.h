
#pragma once

#include "vivid.h"
#include <list>
#include "unit/unit_id.h"
#include "unit/unit.h"
#include "../bullet_manager/bullet/bullet.h"

using namespace std;

/*!
 *	@brief	ユニット管理クラス
 */
class CUnitManager
{
public:

	/*!
	 *	@brief	インスタンスの取得
	 * 
	 *	@return	インスタンス
	 */
	static CUnitManager& GetInstance();

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
	 *	@brief	ユニット生成
	 * 
	 *	@param[in]	id	ユニットID
	 *	@param[in]	pos	生成座標
	 */
	void Create(UNIT_ID id, const vivid::Vector2& pos);

	/*!
	 *	@brief	ユニットと弾の当たり判定
	 * 
	 *	@param[in]	bullet	弾クラスポインタ
	 */
	void CheckHitBullet(IBullet* bullet);

	/*!
	 *	@brief	弾に一番近いユニットを探す
	 * 
	 *	@param[in]	bullet	弾クラスポインタ
	 * 
	 *	@return	弾に一番近いユニットのアドレス
	 */
	IUnit* FindNearUnit(IBullet* bullet);

	/*!
	 *	@brief	戦闘機取得
	 * 
	 *	@return	ユニットのアドレス
	 */
	IUnit* GetFighter();

	/*!
	 *	@brief	残りのUFOを調べる
	 * 
	 *	@return	残っていなければfalse
	 */
	bool CheckRemainingUfo();

private:

	/*!
	 *	@brief	コンストラクタ
	 */
	CUnitManager();

	/*!
	 *	@brief	デストラクタ
	 */
	~CUnitManager();

	/*!
	 *	@brief	コピーコンストラクタ
	 */
	CUnitManager(const CUnitManager& rhs);

	/*!
	 *	@brief	代入演算子
	 */
	CUnitManager& operator=(const CUnitManager& rhs);

	/*!
	 *	@brief	UFOの配置
	 */
	void DeployUfo();

	/*!
	 *	@brief	UFOテーブル更新
	 */
	void UpdateUfoTable();

	/*!
	 *	@brief	全ユニットの更新
	 */
	void UpdateUnit();

	/*!
	 *	@brief	UFOテーブル用構造体ID
	 */
	enum class UFO_TABLE_DATA_PARAM
	{
		ID,
		X,
		Y,
		CREATE_TIME,
	};

	/*!
	 *	@brief	UFOテーブル用構造体
	 */
	struct UFO_TABLE_DATA
	{
		UNIT_ID	id;
		int		x;
		int		y;
		int		create_frame;
	};

	// UFOテーブルリスト
	using UFO_TABLE = list<UFO_TABLE_DATA>;

	// ユニットリスト型
	using UNIT_LIST = list<IUnit*>;

	static const float	m_dummy_length;			//!< 最短距離計算用ダミーデータ

	UNIT_LIST			m_UnitList;				//!< ユニットリスト
	int					m_CreateTimer;			//!< 生成時間
	UFO_TABLE			m_UfoTable;				//!< UFOテーブルリスト

};