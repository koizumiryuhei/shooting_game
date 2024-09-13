
/*!
 *  @file       title.h
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"..\scene.h"

/*!
 *  @class      CTitle
 *
 *  @brief      タイトルシーンクラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CTitle
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CTitle( void );

    /*!
     *  @brief      デストラクタ
     */
    ~CTitle( void );

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

private:

    /*!
     *  @brief      設定
     */
    void        Setting();

    /*!
     *  @brief  状態ID
     */
    enum class STATE
    {
        WAIT,
        SHINE,
        APPEAR,
        SETTING,
    };

    static const int            m_shine_width;          //!< 光の幅
    static const int            m_shine_height;         //!< 光の高さ
    static const int            m_shine_time;           //!< 光る時間
    static const int            m_blink_time;           //!< 点滅時間
    static const float          m_shine_rotation_speed; //!< 光の回転速度
    static const float          m_shine_speed;          //!< 光の移動速度
    static const vivid::Vector2 m_title_positon;        //!< タイトルロゴ位置
    static const vivid::Vector2 m_message_positon;      //!< メッセージの位置
    static const vivid::Vector2 m_copyright_positon;    //!< コピーライトの位置
    vivid::Vector2              m_ShinePosition;        //!< 光の位置
    float                       m_ShineRotation;        //!< 光の回転値
    STATE                       m_State;                //!< 状態ID
    int                         m_ShineTime;            //!< 光る時間
    int                         m_BlinkTime;            //!< 点滅時間
};
