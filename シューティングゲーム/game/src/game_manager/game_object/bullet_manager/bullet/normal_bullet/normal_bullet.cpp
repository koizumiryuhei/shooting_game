
/*!
 *  @file       normal_bullet.cpp
 *  @brief      通常弾
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "normal_bullet.h"

const int   CNormalBullet::m_width    = 32;
const int   CNormalBullet::m_height   = 16;
const float CNormalBullet::m_radius   = 8.0f;

/*
 *  コンストラクタ
 */
CNormalBullet::
CNormalBullet( void )
    : IBullet( m_width, m_height, m_radius )
{
}

/*
 *  デストラクタ
 */
CNormalBullet::
~CNormalBullet( void )
{
}

/*
 *  描画
 */
void
CNormalBullet::
Draw( void )
{
    vivid::DrawTexture("data\\normal_bullet_bloom.png", m_Position, m_Color, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD );
    vivid::DrawTexture("data\\normal_bullet.png", m_Position, 0xffffffff, m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD );
}
