
/*!
 *  @file       bullet.h
 *  @brief      弾
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "bullet_id.h"
#include "..\..\unit_manager\unit\unit_id.h"

/*!
 *  @class      IBullet
 *
 *  @brief      弾ベースクラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IBullet
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  width   幅
     *  @param[in]  height  高さ
     *  @param[in]  radius  半径
     */
    IBullet( int width, int height, float radius );

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IBullet( void );

    /*!
     *  @brief      初期化
     *
     *  @param[in]  category  ユニット識別子
     *  @param[in]  position    位置
     *  @param[in]  direction   向き
     *  @param[in]  speed       速さ
     */
    virtual void    Initialize( UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed );

    /*!
     *  @brief      更新
     */
    virtual void    Update( void );

    /*!
     *  @brief      描画
     */
    virtual void    Draw( void );

    /*!
     *  @brief      解放
     */
    virtual void    Finalize( void );

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    vivid::Vector2  GetPosition( void );

    /*!
     *  @brief      位置設定
     *
     *  @param[in]  position    位置
     */
    void            SetPosition( const vivid::Vector2& position );

    /*!
     *  @brief      中心位置取得
     *
     *  @return     中心位置
     */
    vivid::Vector2  GetCenterPosition( void );

    /*!
     *  @brief      半径取得
     *
     *  @return     半径
     */
    float           GetRadius( void );

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            GetActive( void );

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive( bool active );

    /*!
     *  @brief      ユニット識別子取得
     *
     *  @return     ユニット識別子
     */
    UNIT_CATEGORY   GetBulletCategory( void );

    /*!
     *  @brief      弾の色取得
     *
     *  @return     弾の色
     */
    unsigned int    GetBulletColor( void );

protected:
    /*!
     *  @brief      弾の有効範囲チェック
     */
    void    CheckArea( void );

    static const unsigned int   m_fighter_color;    //!< 戦闘機の弾の色
    static const unsigned int   m_ufo_color;        //!< UFO弾の色
    static const int            m_adjust_area;      //!< 弾の生存可能エリア範囲
    static const vivid::Rect    m_enable_area;      //!< 弾の生存可能エリア
    int                         m_Width;            //!< 幅
    int                         m_Height;           //!< 高さ
    float                       m_Radius;           //!< 半径
    vivid::Vector2              m_Position;         //!< 位置
    vivid::Vector2              m_Velocity;         //!< 速度
    unsigned int                m_Color;            //!< 色
    vivid::Vector2              m_Anchor;           //!< 基準点
    vivid::Rect                 m_Rect;             //!< 読み込み範囲
    vivid::Vector2              m_Scale;            //!< 拡大率
    float                       m_Rotation;         //!< 回転値
    bool                        m_ActiveFlag;       //!< アクティブフラグ
    UNIT_CATEGORY               m_Category;         //!< 弾識別子
};
