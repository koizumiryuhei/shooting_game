
/*!
 *  @file       fighter.cpp
 *  @brief      �퓬�@
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "fighter.h"
#include "..\..\..\..\..\utility\utility.h"
#include "../../../game_object.h"

const int               CFighter::m_width                       = 36;
const int               CFighter::m_height                      = 36;
const float             CFighter::m_radius                      = 1.0f;
const vivid::Vector2    CFighter::m_start_position              = vivid::Vector2( (float)vivid::WINDOW_WIDTH / 2.0f - (float)m_width / 2.0f, (float)vivid::WINDOW_HEIGHT * 1.2f );
const float             CFighter::m_move_friction               = 0.975f;
const float             CFighter::m_max_move_accelerator        = 0.25f;
const float             CFighter::m_move_accelerator            = 0.05f;
const float             CFighter::m_create_effect_length        = 2.5f;
const int               CFighter::m_max_fire_time               = 10;
const int               CFighter::m_max_life                    = 5;
const int               CFighter::m_nbullet_fire_interval       = 10;
const int               CFighter::m_charge_shot_time            = 60 * 0.5f;
const int               CFighter::m_max_invincible_time         = 180;
const int               CFighter::m_invincible_visible_interval = 4;

/*
 *  �R���X�g���N�^
 */
CFighter::
CFighter(void)
    : IUnit(m_width, m_height, m_radius, m_max_life, UNIT_CATEGORY::FIGHTER, UNIT_ID::FIGHTER)
    , m_Accelerator( vivid::Vector2( 0.0f, 0.0f ) )
    , m_MoveAccelerator( 0.0f )
    , m_NBulletFireTimer( 0 )
    , m_InvincibleTime( 0 )
{
}

/*
 *  �f�X�g���N�^
 */
CFighter::
~CFighter( void )
{
}

/*
 *  ������
 */
void
CFighter::
Initialize( const vivid::Vector2& position )
{
    (void)position;

    IUnit::Initialize( m_start_position );

    m_Accelerator           = vivid::Vector2( 0.0f, -10.0f );
    m_MoveAccelerator       = 0.0f;
    m_AlphaFactor           = 0.0f;
    m_NBulletFireTimer      = 0;
    m_HBulletFireTimer      = 0;
    m_Life = m_MaxLife      = m_max_life;
    m_InvincibleTime        = 0;
}

/*
 *  �X�V
 */
void
CFighter::
Update( void )
{
    IUnit::Update( );

#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::I))
    {
        m_InvincibleTime = 9999;
        m_InvincibleFlag = true;
    }
#endif
}

/*
 *  �`��
 */
void
CFighter::
Draw( void )
{
    const vivid::Rect rect = { 0, 0, m_width, m_height };
    const vivid::Vector2 anchor( (float)m_width  / 2.0f, (float)m_height / 2.0f );
    const vivid::Vector2 scale( 1.0f, 1.0f );

    if( m_InvincibleTime <= 0 || ( m_InvincibleTime / m_invincible_visible_interval ) % 2 == 0 )
    {
        vivid::DrawTexture("data\\fighter.png", m_Position);
        vivid::DrawTexture("data\\fighter_light_bloom.png", m_Position, m_BloomColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD );
        vivid::DrawTexture("data\\fighter_light.png", m_Position, m_LightColor, rect, anchor, scale, 0.0f, vivid::ALPHABLEND::ADD );
    }
}

/*
 *  ���
 */
void
CFighter::
Finalize( void )
{
}

/*
 *  �A�^������`�F�b�N
 */
bool
CFighter::
CheckHitBullet( IBullet* bullet )
{
    if (!bullet || m_Category == bullet->GetBulletCategory() || m_InvincibleFlag  || m_UnitState == UNIT_STATE::DEAD )
        return false;

    vivid::Vector2 v = GetCenterPosition( ) - bullet->GetCenterPosition();

    if( v.Length() <= m_Radius + bullet->GetRadius() )
    {
        CSoundManager::GetInstance().Play(SOUND_ID::FIGHTER_HIT, false);

        CEffectManager::GetInstance().Create(EFFECT_ID::DAMAGE, vivid::Vector2::ZERO, 0xffff0000, 0.0f);

        bullet->SetActive( false );

        if( --m_Life <= 0 )
        {
            m_UnitState = UNIT_STATE::DEAD;
        }
        else
        {
            m_InvincibleTime = m_max_invincible_time;

            m_InvincibleFlag = true;
        }

        return true;
    }

    return false;
}

/*
 *  �o��
 */
void
CFighter::
Appear(void)
{
    Move( );

    Effect();

    if( m_Position.y < (float)vivid::WINDOW_HEIGHT * 0.8f )
    {
        m_Velocity = vivid::Vector2( 0.0f, 0.0f );

        m_Accelerator = vivid::Vector2( 0.0f, 0.0f );

        m_InvincibleFlag = false;

        m_UnitState = UNIT_STATE::ATTACK;
    }
}

/*
 *  �U��
 */
void
CFighter::
Attack(void)
{
    Fire();

    Control();

    Move();

    Effect();

    CheckMoveArea();

    if( --m_InvincibleTime < 0 )
    {
        m_InvincibleTime = 0;

        m_InvincibleFlag = false;
    }
}

/*
 *  ���S
 */
void
CFighter::
Dead(void)
{
    CEffectManager& effect = CEffectManager::GetInstance();

    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);
    effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);

    m_ActiveFlag = false;
}

/*
 *  ����
 */
void
CFighter::
Control( void )
{
    bool input = false;

    vivid::Vector2 dir = vivid::Vector2( 0.0f, 0.0f );

    if( vivid::keyboard::Button( vivid::keyboard::KEY_ID::LEFT ) )
    {
        input = true;

        dir.x += -1.0f;
    }

    if( vivid::keyboard::Button( vivid::keyboard::KEY_ID::RIGHT ) )
    {
        input = true;

        dir.x += 1.0f;
    }

    if( vivid::keyboard::Button( vivid::keyboard::KEY_ID::UP ) )
    {
        input = true;

        dir.y += -1.0f;
    }

    if( vivid::keyboard::Button( vivid::keyboard::KEY_ID::DOWN ) )
    {
        input = true;

        dir.y += 1.0f;
    }

    if(input)
    {
        m_MoveAccelerator += m_move_accelerator;

        if( m_MoveAccelerator > m_max_move_accelerator )
            m_MoveAccelerator = m_max_move_accelerator;
    }
    else
    {
        m_MoveAccelerator = 0.0f;
    }

    dir.Normalize();

    m_Accelerator = dir * m_MoveAccelerator;
}

/*
 *  �ˌ�
 */
void
CFighter::
Fire( void )
{
    CBulletManager& bm = CBulletManager::GetInstance();

    // �m�[�}���V���b�g
    if( vivid::keyboard::Button(vivid::keyboard::KEY_ID::Z) )
    {
        if( --m_NBulletFireTimer < 0 )
        {
            m_NBulletFireTimer = m_nbullet_fire_interval;

            bm.Create(m_Category, BULLET_ID::NORMAL, m_Position + vivid::Vector2( m_width / 3.0f, 0.0f ), DEG_TO_RAD( 270.0f ), 10.0f );
            bm.Create(m_Category, BULLET_ID::NORMAL, m_Position + vivid::Vector2( m_width / 3.0f * 2.0f, 0.0f ), DEG_TO_RAD( 270.0f ), 10.0f );
            bm.Create(m_Category, BULLET_ID::NORMAL, m_Position + vivid::Vector2( m_width / 3.0f, 0.0f ), DEG_TO_RAD( 260.0f ), 8.0f );
            bm.Create(m_Category, BULLET_ID::NORMAL, m_Position + vivid::Vector2( m_width / 3.0f * 2.0f, 0.0f ), DEG_TO_RAD( 280.0f ), 8.0f );
        }
    }
    else
    {
        m_NBulletFireTimer = 0;
    }

    // �`���[�W�V���b�g
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::X))
    {
        if (++m_HBulletFireTimer > m_charge_shot_time)
        {
            CEffectManager& effect = CEffectManager::GetInstance();

            if (m_HBulletFireTimer % 12 == 0)
                effect.Create(EFFECT_ID::CHARGE_EFFECT, m_Position, 0xff00afff, 0.0f);

            if(m_HBulletFireTimer % 8 == 0)
            {
                float length = (float)(rand() % 50 + 10);
                float angle = (float)(rand() % 360);

                vivid::Vector2 position;
                position.x = GetCenterPosition().x + cos(angle) * length;
                position.y = GetCenterPosition().y + sin(angle) * length;

                effect.Create(EFFECT_ID::CHARGE_PARTICLE, position, 0xff88aaff, 0.0f);
            }
        }
    }
    else if (vivid::keyboard::Released(vivid::keyboard::KEY_ID::X) && m_HBulletFireTimer > m_charge_shot_time)
    {
        m_HBulletFireTimer = 0;
        bm.Create(m_Category, BULLET_ID::HOMING, m_Position + vivid::Vector2(m_width / 3.0f, m_height), DEG_TO_RAD(210.0f), 10.0f);
        bm.Create(m_Category, BULLET_ID::HOMING, m_Position + vivid::Vector2(m_width / 3.0f * 2.0f, m_height), DEG_TO_RAD(330.0f), 10.0f);
    }
}

/*
 *  �ړ�����
 */
void
CFighter::
Move( void )
{
    m_Velocity += m_Accelerator;

    m_Position += m_Velocity;

    m_Velocity *= m_move_friction;

    m_Accelerator = vivid::Vector2( 0.0f, 0.0f );
}

/*
 *  �ړ��͈̓`�F�b�N
 */
void
CFighter::
CheckMoveArea( void )
{
    const float w = (float)vivid::WINDOW_WIDTH - (float)m_width;
    const float h = (float)vivid::WINDOW_HEIGHT - (float)m_height;

    if( m_Position.x < 0.0f )
    {
        m_Position.x = 0.0f;

        m_Velocity.x *= -1.0f;
    }

    if( m_Position.x > w )
    {
        m_Position.x = w;

        m_Velocity.x *= -1.0f;
    }

    if( m_Position.y < 0.0f )
    {
        m_Position.y = 0.0f;

        m_Velocity.y *= -1.0f;
    }

    if( m_Position.y > h )
    {
        m_Position.y = h;

        m_Velocity.y *= -1.0f;
    }
}

/*!
 *  �O�ՃG�t�F�N�g
 */
void 
CFighter::
Effect(void)
{
    if(m_Velocity.Length() > m_create_effect_length)
    {
        CEffectManager::GetInstance().Create(EFFECT_ID::TRAFECTORY, m_Position, (m_LightColor - 0x88000000), 0.0f);
    }
}
