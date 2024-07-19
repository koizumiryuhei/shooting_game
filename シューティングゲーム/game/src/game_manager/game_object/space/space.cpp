
/*!
 *  @file       space.cpp
 *  @brief      宇宙
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "space.h"

const int   CSpace::m_width         = 800;
const int   CSpace::m_height        = 600;
const int   CSpace::m_max_bg_count  = 2;
const float CSpace::m_scroll_speed  = 0.5f;

/*
 *  コンストラクタ
 */
CSpace::
CSpace( void )
    : m_Position( nullptr )
    , m_Velocity( nullptr )
{
}

/*
 *  デストラクタ
 */
CSpace::
~CSpace( void )
{
}

/*
 *  初期化
 */
void
CSpace::
Initialize( void )
{
    if(!m_Position)
        m_Position = new vivid::Vector2[m_max_bg_count];

    if(!m_Velocity)
        m_Velocity = new vivid::Vector2[m_max_bg_count];

    for(int i = 0; i < m_max_bg_count; ++i )
    {
        m_Position[i].y = (float)i * (float)m_height;

        m_Velocity[i] = vivid::Vector2( 0.0f, m_scroll_speed );
    }
}

/*
 *  更新
 */
void
CSpace::
Update( void )
{
    // スクロール処理
    for(int i = 0; i < m_max_bg_count; ++i )
    {
        m_Position[i] += m_Velocity[i];

        if( m_Position[i].y > m_height )
            m_Position[i].y = -m_height + ( m_Position[i].y - m_height );
    }
}

/*
 *  描画
 */
void
CSpace::
Draw( void )
{
    for(int i = 0; i < m_max_bg_count; ++i )
        vivid::DrawTexture( "data\\space.png", m_Position[i] );
}

/*
 *  解放
 */
void
CSpace::
Finalize( void )
{
    delete[] m_Position;

    m_Position = nullptr;

    delete[] m_Velocity;

    m_Velocity = nullptr;
}
