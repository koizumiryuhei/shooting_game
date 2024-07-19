
/*!
 *  @file       bullet_manager.cpp
 *  @brief      弾管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "bullet_manager.h"
#include "..\unit_manager\unit_manager.h"
#include "bullet\normal_bullet\normal_bullet.h"
#include "bullet/homing_bullet/homing_bullet.h"
#include "bullet/boss_bullet/boss_bullet.h"
#include "bullet/boss_homing_bullet/boss_homing_bullet.h"
#include "../game_object.h"

/*
 *  インスタンスの取得
 */
CBulletManager& 
CBulletManager::
GetInstance(void)
{
    static CBulletManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CBulletManager::
Initialize( void )
{
    m_BulletList.clear();
}

/*
 *  更新
 */
void
CBulletManager::
Update( void )
{
    // リストが空なら終了
    if( m_BulletList.empty( ) ) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while( it != m_BulletList.end() )
    {
        IBullet* bullet = (IBullet*)(*it);

        bullet->Update();

        CUnitManager::GetInstance().CheckHitBullet(bullet);
        // 弾が非アクティブなら削除してリストから外す
        if( !bullet->GetActive( ) )
        {
            bullet->Finalize();

            delete bullet;

            it = m_BulletList.erase( it );

            continue;
        }

        ++it;
    }
}

/*
 *  描画
 */
void
CBulletManager::
Draw( void )
{
    if(m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while( it != m_BulletList.end() )
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void
CBulletManager::
Finalize( void )
{
    if(m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while( it != m_BulletList.end() )
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_BulletList.clear();
}

/*
 *  弾生成
 */
void
CBulletManager::
Create(UNIT_CATEGORY category, BULLET_ID id, const vivid::Vector2& pos, float dir, float speed )
{
    IBullet* bullet = nullptr;
    CSoundManager& sound = CSoundManager::GetInstance();

    switch( id )
    {
    case BULLET_ID::NORMAL:         bullet = new CNormalBullet();       sound.Play(SOUND_ID::SHOT, false);          break;
    case BULLET_ID::HOMING:         bullet = new CHomingBullet();       sound.Play(SOUND_ID::HOMING_SHOT, false);   break;
    case BULLET_ID::BOSS:           bullet = new CBossBullet();         sound.Play(SOUND_ID::SHOT, false);          break;
    case BULLET_ID::BOSS_HOMING:    bullet = new CBossHomingBullet();   sound.Play(SOUND_ID::SHOT, false);          break;
    }

    if(!bullet) return;

    bullet->Initialize(category, pos, dir, speed );

    // 生成した弾をリストに追加
    m_BulletList.push_back( bullet );
}

/*
 *  コンストラクタ
 */
CBulletManager::
CBulletManager( void )
{
}

/*
 *  コピーコンストラクタ
 */
CBulletManager::
CBulletManager( const CBulletManager& rhs )
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CBulletManager::
~CBulletManager( void )
{
}

/*
 *  代入演算子
 */
CBulletManager& 
CBulletManager::
operator=( const CBulletManager& rhs )
{
    (void)rhs;

    return *this;
}
