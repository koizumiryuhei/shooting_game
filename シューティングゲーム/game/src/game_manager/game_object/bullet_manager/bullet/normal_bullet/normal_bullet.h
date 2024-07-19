
/*!
 *  @file       normal_bullet.h
 *  @brief      通常弾
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\bullet.h"

/*!
 *  @class      CNormalBullet
 *
 *  @brief      通常弾クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CNormalBullet
    : public IBullet
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CNormalBullet( void );

    /*!
     *  @brief      デストラクタ
     */
    ~CNormalBullet( void );

    /*!
     *  @brief      描画
     */
    void    Draw( void );

private:
    static const int    m_width;    //!< 幅
    static const int    m_height;   //!< 高さ
    static const float  m_radius;   //!< 半径
};
