
/*!
 *  @file       unit.h
 *  @brief      ユニット
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "unit_id.h"

class IBullet;

/*!
 *  @brief  ユニットの状態ID
 */
enum class UNIT_STATE
{
    APPEAR, //!< 登場
    ATTACK, //!< 攻撃
    DEAD,   //!< 死亡
};

/*!
 *  @class      IUnit
 *
 *  @brief      ユニットベースクラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IUnit
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  width       幅
     *  @param[in]  height      高さ
     *  @param[in]  radius      半径
     *  @param[in]  life        ライフ
     *  @param[in]  category  ユニット識別子
     *  @param[in]  unit_id     ユニットID
     */
    IUnit(int width, int height, float radius, int life, UNIT_CATEGORY category, UNIT_ID unit_id);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IUnit( void );

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     */
    virtual void    Initialize( const vivid::Vector2& position );

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
     *  @brief      アタリ判定チェック
     *
     *  @param[in]  bullet  弾クラス
     *
     *  @retval     true    当たっている
     *  @retval     false   当たっていない
     */
    virtual bool    CheckHitBullet( IBullet* bullet );

    /*!
     *  @brief      ユニットID取得
     *
     *  @return     ユニットID
     */
    UNIT_ID         GetUnitID( void );

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
    UNIT_CATEGORY   GetUnitCategory( void );

    /*!
     *  @brief      ライフ取得
     *
     *  @return     ライフ
     */
    int             GetLife( void );

    /*!
     *  @brief      最大ライフ取得
     *
     *  @return     最大ライフ
     */
    int             GetMaxLife( void );

    /*!
     *  @brief      無敵フラグ取得
     *
     *  @return     無敵フラグ
     */
    bool            GetInvincibleFlag( void );

    /*!
     *  @brief      無敵フラグ設定
     *
     *  @param[in]  flag    無敵フラグ
     */
    void            SetInvincibleFlag( bool flag );

    /*!
     *  @brief      状態取得
     *
     *  @return     状態ID
     */
    UNIT_STATE      GetUnitState( void );

    /*!
     *  @brief      状態設定
     *
     *  @param[in]  state    状態ID
     */
    void            SetUnitState( UNIT_STATE state );

protected:
    /*!
     *  @brief      ライトカラーの変更
     */
    void            ChangeLightColor( void );

    /*!
     *  @brief      登場
     */
    virtual void    Appear( void );

    /*!
     *  @brief      攻撃
     */
    virtual void    Attack( void );

    /*!
     *  @brief      死亡
     */
    virtual void    Dead( void );

    static const int        m_change_color_speed;   //!< 色の変更速度
    static const float      m_bloom_fade_speed;     //!< ブルームフェード速度
    int                     m_Width;                //!< 幅
    int                     m_Height;               //!< 高さ
    float                   m_Radius;               //!< 半径
    vivid::Vector2          m_Position;             //!< 位置
    vivid::Vector2          m_Velocity;             //!< 速度
    unsigned int            m_LightColor;           //!< 光の色
    unsigned int            m_BloomColor;           //!< 光の色
    vivid::Vector2          m_Anchor;               //!< 基準点
    vivid::Rect             m_Rect;                 //!< 読み込み範囲
    vivid::Vector2          m_Scale;                //!< 拡大率
    float                   m_Rotation;             //!< 回転値
    bool                    m_ActiveFlag;           //!< アクティブフラグ
    int                     m_ColorFactor;          //!< 光の色の変化要素
    float                   m_AlphaFactor;          //!< アルファ値変化要素
    int                     m_Life;                 //!< ライフ
    int                     m_MaxLife;              //!< 最大ライフ
    UNIT_CATEGORY           m_Category;             //!< ユニット識別子
    UNIT_ID                 m_UnitID;               //!< ユニットID
    bool                    m_InvincibleFlag;       //!< 無敵フラグ
    UNIT_STATE              m_UnitState;            //!< 状態ID
};
