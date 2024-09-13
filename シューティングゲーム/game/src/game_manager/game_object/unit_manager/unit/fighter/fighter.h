
/*!
 *  @file       fighter.h
 *  @brief      戦闘機
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\unit.h"

class CFighterOption;

/*!
 *  @class      CFighter
 *
 *  @brief      戦闘機クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CFighter
    : public IUnit
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CFighter( void );

    /*!
     *  @brief      デストラクタ
     */
    ~CFighter( void );

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    初期位置
     */
    void        Initialize( const vivid::Vector2& position )override;

    /*!
     *  @brief      更新
     */
    void        Update( void )override;

    /*!
     *  @brief      描画
     */
    void        Draw( void )override;

    /*!
     *  @brief      解放
     */
    void        Finalize( void )override;

    /*!
     *  @brief      アタリ判定チェック
     *
     *  @param[in]  bullet  弾クラス
     *
     *  @retval     true    当たっている
     *  @retval     false   当たっていない
     */
    bool        CheckHitBullet( IBullet* bullet )override;

    struct DATA
    {
        const float m_up_limit_move_accelerator         = 0.09f;
        const float m_down_limit_move_accelerator       = 0.01f;
        const float m_up_limit_max_move_accelerator     = 0.5f;
        const float m_down_limit_max_move_accelerator   = 0.1f;
        float m_move_accelerator;
        float m_max_move_accelerator;
    };

private:

    /*!
     *  @brief      登場
     */
    void        Appear( void )override;

    /*!
     *  @brief      攻撃
     */
    void        Attack( void )override;

    /*!
     *  @brief      死亡
     */
    void        Dead( void )override;

    /*!
     *  @brief      操作
     */
    void        Control( void );

    /*!
     *  @brief      射撃
     */
    void        Fire( void );

    /*!
     *  @brief      移動処理
     */
    void        Move( void );

    /*!
     *  @brief      移動範囲チェック
     */
    void        CheckMoveArea( void );

    /*!
     *  @brief      軌跡エフェクト
     */
    void        Effect( void );

    static const int                m_width;                        //!< 幅
    static const int                m_height;                       //!< 高さ
    static const float              m_radius;                       //!< 半径
    static const vivid::Vector2     m_start_position;               //!< 初期位置
    static const float              m_move_friction;                //!< 移動用減速率
    //static const float              m_max_move_accelerator;         //!< 移動時の加速度
    //static const float              m_move_accelerator;             //!< 移動時の加速度
    static const float              m_create_effect_length;         //!< エフェクトを出す基準の大きさ
    static const int                m_max_fire_time;                //!< 発射時間
    static const int                m_max_life;                     //!< 最大ライフ
    static const int                m_nbullet_fire_interval;        //!< 通常弾発射間隔
    static const int                m_charge_shot_time;             //!< チャージショットタイム
    static const int                m_max_invincible_time;          //!< 無敵時間
    static const int                m_invincible_visible_interval;  //!< 無敵時間中の点滅間隔

    DATA                            m_Data;                         //!< 加速度データ
    vivid::Vector2                  m_Accelerator;                  //!< 加速度
    float                           m_MoveAccelerator;              //!< 移動用加速度
    int                             m_NBulletFireTimer;             //!< ノーマル弾発射タイマー
    int                             m_HBulletFireTimer;             //!< ホーミング弾発射タイマー
    int                             m_InvincibleTime;               //!< 無敵時間
    CFighterOption*                 m_Option1;
    CFighterOption*                 m_Option2;

};
