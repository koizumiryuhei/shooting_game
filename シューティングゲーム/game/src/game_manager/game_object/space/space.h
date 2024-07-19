
/*!
 *  @file       space.h
 *  @brief      宇宙
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

/*!
 *  @class      CSpace
 *
 *  @brief      宇宙クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CSpace
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSpace( void );

    /*!
     *  @brief      デストラクタ
     */
    ~CSpace( void );

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
    static const int                m_width;                    //!< 幅
    static const int                m_height;                   //!< 高さ
    static const int                m_max_bg_count;             //!< 背景の数
    static const float              m_scroll_speed;             //!< スクロール速度
    vivid::Vector2*                 m_Position;                 //!< 位置
    vivid::Vector2*                 m_Velocity;                 //!< 速度
};
