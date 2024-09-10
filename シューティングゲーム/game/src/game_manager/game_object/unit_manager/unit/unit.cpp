
/*!
 *  @file       unit.cpp
 *  @brief      ユニット
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "unit.h"
#include "..\..\..\..\utility\utility.h"
#include "..\..\bullet_manager\bullet\bullet.h"
#include "../../game_object.h"

const int   IUnit::m_change_color_speed  = 1;
const float IUnit::m_bloom_fade_speed    = 1.5f;

/*
 *  コンストラクタ
 */
IUnit::
IUnit(int width, int height, float radius, int life, UNIT_CATEGORY category, UNIT_ID unit_id)
    : m_Width(width)
    , m_Height(height)
    , m_Radius(radius)
    , m_Position(vivid::Vector2(0.0f, 0.0f))
    , m_Velocity(vivid::Vector2(0.0f, 0.0f))
    , m_LightColor(0xffffffff)
    , m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
    , m_Rect({ 0, 0, m_Width, m_Height })
    , m_Scale(vivid::Vector2(1.0f, 1.0f))
    , m_Rotation(0.0f)
    , m_ActiveFlag(true)
    , m_MaxLife(life)
    , m_Life(life)
    , m_Category(category)
    , m_UnitID(unit_id)
    , m_InvincibleFlag(true)
    , m_UnitState(UNIT_STATE::APPEAR)
{
}

/*
 *  デストラクタ
 */
IUnit::
~IUnit( void )
{
}

/*
 *  初期化
 */
void
IUnit::
Initialize( const vivid::Vector2& position )
{
    m_Position          = position;
    m_Velocity          = vivid::Vector2( 0.0f, 0.0f );
    m_ActiveFlag        = true;
    m_InvincibleFlag    = true;
    m_UnitState         = UNIT_STATE::APPEAR;
    m_ColorFactor       = rand( ) % 360;
}

/*
 *  更新
 */
void
IUnit::
Update( void )
{
    switch( m_UnitState )
    {
    case UNIT_STATE::APPEAR:     Appear( );      break;
    case UNIT_STATE::ATTACK:     Attack( );      break;
    case UNIT_STATE::DEAD:       Dead( );        break;
    }

    ChangeLightColor();

    if( m_Position.y > vivid::WINDOW_HEIGHT && !m_InvincibleFlag )
        m_ActiveFlag = false;
}

/*
 *  描画
 */
void
IUnit::
Draw( void )
{
}

/*
 *  解放
 */
void
IUnit::
Finalize( void )
{
}

/*
 *  アタリ判定チェック
 */
bool
IUnit::
CheckHitBullet( IBullet* bullet )
{
    // 無効であれば飛ばす
    if (!bullet || m_Category == bullet->GetBulletCategory() || m_InvincibleFlag  || m_UnitState == UNIT_STATE::DEAD )
        return false;

    // ユニットと弾のベクトル差
    vivid::Vector2 v = GetCenterPosition( ) - bullet->GetCenterPosition();

    // 当たり判定
    if( v.Length() <= m_Radius + bullet->GetRadius() )
    {
        CEffectManager& effect = CEffectManager::GetInstance();

        effect.Create(EFFECT_ID::HIT, bullet->GetCenterPosition(), bullet->GetBulletColor(), 0.0f);
        effect.Create(EFFECT_ID::HIT, bullet->GetCenterPosition(), bullet->GetBulletColor(), 0.0f);
        effect.Create(EFFECT_ID::HIT, bullet->GetCenterPosition(), bullet->GetBulletColor(), 0.0f);

        bullet->SetActive( false );

        if( --m_Life <= 0 )
        {
            m_UnitState = UNIT_STATE::DEAD;

            if (m_UnitID == UNIT_ID::UFO_BOSS)
                effect.Create(EFFECT_ID::BOSS_WHITE_EFFECT, GetPosition(), 0xffffffff, 0.0f);
        }

        return true;
    }

    return false;
}

/*
 *  ユニットID取得
 */
UNIT_ID
IUnit::
GetUnitID(void)
{
    return m_UnitID;
}

/*
 *  位置取得
 */
vivid::Vector2
IUnit::
GetPosition( void )
{
    return m_Position;
}

/*
 *  位置設定
 */
void
IUnit::
SetPosition( const vivid::Vector2& positioin )
{
    m_Position = positioin;
}

/*
 *  中心位置取得
 */
vivid::Vector2
IUnit::
GetCenterPosition( void )
{
    return m_Position + vivid::Vector2( m_Width / 2.0f, m_Height / 2.0f );
}

/*
 *  半径取得
 */
float
IUnit::
GetRadius( void )
{
    return m_Radius;
}

/*
 *  アクティブフラグ取得
 */
bool
IUnit::
GetActive( void )
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ取得
 */
void
IUnit::
SetActive( bool active )
{
    m_ActiveFlag = active;
}

/*
 *  ユニット識別子取得
 */
UNIT_CATEGORY
IUnit::
GetUnitCategory( void )
{
    return m_Category;
}

/*
 *  ライフ取得
 */
int
IUnit::
GetLife( void )
{
    return m_Life;
}

/*
 *  最大ライフ取得
 */
int
IUnit::
GetMaxLife( void )
{
    return m_MaxLife;
}

/*
 *  無敵フラグ取得
 */
bool
IUnit::
GetInvincibleFlag( void )
{
    return m_InvincibleFlag;
}

/*
 *  無敵フラグ設定
 */
void
IUnit::
SetInvincibleFlag( bool flag )
{
    m_InvincibleFlag = flag;
}

/*
 *  ユニット状態取得
 */
UNIT_STATE
IUnit::
GetUnitState( void )
{
    return m_UnitState;
}

/*
 *  ユニット状態設定
 */
void
IUnit::
SetUnitState( UNIT_STATE state )
{
    m_UnitState = state;
}

/*
 *  ライトカラーの変更
 */
void
IUnit::
ChangeLightColor( void )
{
    m_ColorFactor += m_change_color_speed;

    m_ColorFactor %= 360;

    m_BloomColor = m_LightColor = ChangeNumberToColor( 360, m_ColorFactor);

    m_AlphaFactor += m_bloom_fade_speed;

    // アルファ値計算
    int alpha = (int)( abs( cos( DEG_TO_RAD( m_AlphaFactor ) ) ) * 255.0f );

    m_BloomColor = ( alpha << 24 ) | ( m_BloomColor & 0x00ffffff );
}

/*
 *  登場
 */
void
IUnit::
Appear(void)
{
    m_Position.y += m_Velocity.y;

    if( m_Position.y > 0.0f )
    {
        m_InvincibleFlag = false;

        m_UnitState = UNIT_STATE::ATTACK;
    }
}

/*
 *  攻撃
 */
void
IUnit::
Attack(void)
{
    m_Position += m_Velocity;
}

/*
 *  死亡
 */
void
IUnit::
Dead(void)
{
    CSoundManager::GetInstance().Play(SOUND_ID::DESTORY, false);

    CEffectManager& effect = CEffectManager::GetInstance();

    const int destroy = 6;

    for (int i = 0; i < destroy; ++i)
        effect.Create(EFFECT_ID::DESTORY, GetCenterPosition(), 0xffffffff, 0.0f);

    effect.Create(EFFECT_ID::EXPLOSION_RING, GetCenterPosition(), 0xffffffff, 0.0f);

    m_ActiveFlag = false;
}
