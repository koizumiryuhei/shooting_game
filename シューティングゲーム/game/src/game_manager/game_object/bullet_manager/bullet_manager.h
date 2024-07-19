
/*!
 *  @file       bullet_manager.h
 *  @brief      弾管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include "vivid.h"
#include "bullet\bullet_id.h"
#include "bullet\bullet.h"
#include "..\unit_manager\unit\unit_id.h"

using namespace std;

/*!
 *  @class      CBulletManager
 *
 *  @brief      弾管理クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CBulletManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CBulletManager&   GetInstance( void );

    /*!
     *  @brief      初期化
     */
    void        Initialize( void );

    /*!
     *  @brief      更新
     */
    void        Update( void );

    /*!
     *  @brief      描画
     */
    void        Draw( void );

    /*!
     *  @brief      解放
     */
    void        Finalize( void );

    /*!
     *  @brief      弾生成
     *
     *  @param[in]  category  ユニット識別子
     *  @param[in]  id          弾ID
     *  @param[in]  pos         位置
     *  @param[in]  dir         向き
     *  @param[in]  speed       速さ
     */
    void        Create( UNIT_CATEGORY category, BULLET_ID id, const vivid::Vector2& pos, float dir, float speed );

private:
    /*!
     *  @brief      コンストラクタ
     */
    CBulletManager( void );

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CBulletManager( const CBulletManager& rhs );

    /*!
     *  @brief      デストラクタ
     */
    ~CBulletManager( void );

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CBulletManager& operator=( const CBulletManager& rhs );

    /*!
     *  @brief      弾リスト型
     */
    using BULLET_LIST = list<IBullet*>;

    BULLET_LIST     m_BulletList;   //!< 弾リスト
};
