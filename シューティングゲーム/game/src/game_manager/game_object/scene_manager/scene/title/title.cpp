
/*!
 *  @file       title.cpp
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "title.h"
#include "..\..\scene_manager.h"
#include "..\..\..\..\..\utility\utility.h"
#include "../../../game_object.h"
#include "../../../setting/setting.h"

const int               CTitle::m_shine_width           = 32;
const int               CTitle::m_shine_height          = 32;
const int               CTitle::m_shine_time            = 60;
const int               CTitle::m_blink_time            = 10;
const float             CTitle::m_shine_rotation_speed  = 10.0f;
const float             CTitle::m_shine_speed           = -10.0f;
const vivid::Vector2    CTitle::m_title_positon         = vivid::Vector2( 240.0f - 192.0f, 100.0f );
const vivid::Vector2    CTitle::m_message_positon       = vivid::Vector2( 240.0f - 64.0f, 320.0f );
const vivid::Vector2    CTitle::m_copyright_positon     = vivid::Vector2( 480.0f - 286.0f, 640.0f - 13.0f );

/*
 *  コンストラクタ
 */
CTitle::
CTitle( void )
{
}

/*
 *  デストラクタ
 */
CTitle::
~CTitle( void )
{
}

/*
 *  初期化
 */
void
CTitle::
Initialize( void )
{
    m_State = STATE::WAIT;

    m_ShinePosition.x = (float)vivid::WINDOW_WIDTH / 2.0f - (float)m_shine_width / 2.0f;
    m_ShinePosition.y = (float)vivid::WINDOW_HEIGHT * 0.9f;

    m_ShineRotation = 0;
    
    m_ShineTime = 0;

    m_BlinkTime = 0;
}

/*
 *  更新
 */
void
CTitle::
Update( void )
{
    switch( m_State )
    {
    case STATE::WAIT:
        {
            if( vivid::keyboard::Trigger( vivid::keyboard::KEY_ID::Z ) )
            {
                CSoundManager::GetInstance().Play(SOUND_ID::ZBUTTON, false);
                m_State = STATE::SHINE;
            }
            
            if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))
            {
                CSetting::GetInstance().Initialize();

                m_State = STATE::SETTING;
            }
        }
        break;
    case STATE::SHINE:
        {
            if( ++m_ShineTime > m_shine_time )
            {
                m_State = STATE::APPEAR;
            }
        }
        break;
    case STATE::APPEAR:
        {
            m_ShinePosition.y += m_shine_speed;

            if( m_ShinePosition.y < -m_shine_height )
                CSceneManager::GetInstance( ).ChangeScene( SCENE_ID::GAMEMAIN );
        }
        break;
    case STATE::SETTING:
        {
            Setting();

            if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
            {
                m_State = STATE::WAIT;
            }
        }
        break;
    }

    m_ShineRotation += DEG_TO_RAD( m_shine_rotation_speed );
}

/*
 *  描画
 */
void
CTitle::
Draw( void )
{
    vivid::DrawTexture( "data\\title_background.png", vivid::Vector2( 0.0f, 0.0f ) );
    vivid::DrawTexture( "data\\copyright.png", m_copyright_positon );

    switch( m_State )
    {
    case STATE::WAIT:
        {
            vivid::DrawTexture( "data\\title.png", m_title_positon );

            if( ( ++m_BlinkTime / m_blink_time ) % 2 == 0 )
                vivid::DrawTexture( "data\\z_button.png", m_message_positon );
        }
        break;
    case STATE::SHINE:
    case STATE::APPEAR:
        {
            const vivid::Rect rect = { 0, 0, m_shine_width, m_shine_height };
            const vivid::Vector2 anchor( (float)m_shine_width  / 2.0f, (float)m_shine_height / 2.0f );
            const vivid::Vector2 scale( 1.0f, 1.0f );

            vivid::DrawTexture( "data\\title_shine_bloom.png", m_ShinePosition, 0xff00ffff, rect, anchor, scale, m_ShineRotation, vivid::ALPHABLEND::ADD );
            vivid::DrawTexture( "data\\title_shine.png", m_ShinePosition, 0xffffffff, rect, anchor, scale, m_ShineRotation, vivid::ALPHABLEND::ADD );
        }
        break;
    case STATE::SETTING:
        {
            CSetting::GetInstance().Draw();
        }
        break;
    }
}

/*
 *  解放
 */
void
CTitle::
Finalize( void )
{
}

/*!
 *  設定
 */
void 
CTitle::
Setting()
{
    CSetting::GetInstance().Setting();
}
