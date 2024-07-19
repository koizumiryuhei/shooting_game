
/*!
 *  @file       bullet.cpp
 *  @brief      弾
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "bullet.h"
#include "..\..\..\..\utility\utility.h"

const unsigned int  IBullet::m_fighter_color    = 0xff008fff;
const unsigned int  IBullet::m_ufo_color        = 0xffff008f;
const int           IBullet::m_adjust_area      = 200;
const vivid::Rect   IBullet::m_enable_area      = { -m_adjust_area, -m_adjust_area, vivid::WINDOW_WIDTH + m_adjust_area, vivid::WINDOW_HEIGHT + m_adjust_area };

/*
 *  コンストラクタ
 */
IBullet::
IBullet( int width, int height, float radius )
    : m_Width( width )
    , m_Height( height )
    , m_Radius( radius )
    , m_Category( UNIT_CATEGORY::UNKNOW )
    , m_Position( vivid::Vector2( 0.0f, 0.0f ) )
    , m_Velocity( vivid::Vector2( 0.0f, 0.0f ) )
    , m_Color( 0xffffffff )
    , m_Anchor( vivid::Vector2( (float)m_Width  / 2.0f, (float)m_Height / 2.0f ) )
    , m_Rect( { 0, 0, m_Width, m_Height } )
    , m_Scale( vivid::Vector2( 1.0f, 1.0f ) )
    , m_Rotation( 0.0f )
    , m_ActiveFlag( true )
{
}

/*
 *  デストラクタ
 */
IBullet::
~IBullet( void )
{
}

/*
 *  初期化
 */
void
IBullet::
Initialize( UNIT_CATEGORY category, const vivid::Vector2& position, float direction, float speed )
{
    m_Category      = category;
    m_Position      = position - vivid::Vector2( (float)m_Width / 2.0f, 0.0f );
    m_Velocity.x    = cos( direction ) * speed;
    m_Velocity.y    = sin( direction ) * speed;
    m_Color         = ( category == UNIT_CATEGORY::FIGHTER ? m_fighter_color : m_ufo_color );
    m_ActiveFlag    = true;
}

/*
 *  更新
 */
void
IBullet::
Update( void )
{
    // 移動計算
    m_Position += m_Velocity;

    // 画面外チェック
    CheckArea();

    // 移動速度に合わせ得て回転値を算出
    m_Rotation = atan2( m_Velocity.y, m_Velocity.x );
}

/*
 *  描画
 */
void
IBullet::
Draw( void )
{
}

/*
 *  解放
 */
void
IBullet::
Finalize( void )
{
}

/*
 *  位置取得
 */
vivid::Vector2
IBullet::
GetPosition( void )
{
    return m_Position;
}

/*
 *  位置設定
 */
void
IBullet::
SetPosition( const vivid::Vector2& positioin )
{
    m_Position = positioin;
}

/*
 *  中心位置取得
 */
vivid::Vector2
IBullet::
GetCenterPosition( void )
{
    return m_Position + vivid::Vector2( (float)m_Width / 2.0f, (float)m_Height / 2.0f);
}

/*
 *  半径取得
 */
float
IBullet::
GetRadius( void )
{
    return m_Radius;
}

/*
 *  アクティブフラグ取得
 */
bool
IBullet::
GetActive( void )
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ取得
 */
void
IBullet::
SetActive( bool active )
{
    m_ActiveFlag = active;
}

/*
 *  ユニット識別子取得
 */
UNIT_CATEGORY
IBullet::
GetBulletCategory( void )
{
    return m_Category;
}

/*
 *  弾の色取得
 */
unsigned int
IBullet::
GetBulletColor(void)
{
    return m_Color;
}

/*
 *  弾の有効範囲チェック
 */
void
IBullet::
CheckArea( void )
{
    if( m_Position.x < (float)m_enable_area.left || m_Position.x > (float)m_enable_area.right || m_Position.y < (float)m_enable_area.top || m_Position.y > (float)m_enable_area.bottom )
        m_ActiveFlag = false;
}
