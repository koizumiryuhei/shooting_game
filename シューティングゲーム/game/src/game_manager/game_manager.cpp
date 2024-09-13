
/*!
 *  @file       game_manager.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_manager.h"
#include "game_object\game_object.h"
#include "game_object/container/container.h"

/*
 *  インスタンスの取得
 */
CGameManager&
CGameManager::
GetInstance( void )
{
    static CGameManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CGameManager::
Initialize( void )
{
    CSoundManager& sound = CSoundManager::GetInstance();

    sound.Load();

    sound.Play(SOUND_ID::BGM, true);
    
    // シーンマネージャー初期化
    CSceneManager::GetInstance().Initialize();

    // エフェクトマネージャー初期化
    CEffectManager::GetInstance().Initialize();

    CContainer::GetInstance().Initialize();
}

/*
 *  更新
 */
void
CGameManager::
Update( void )
{
    // シーンマネージャー更新
    CSceneManager::GetInstance().Update();

    // エフェクトマネージャー更新
    CEffectManager::GetInstance().Update();
}

/*
 *  描画
 */
void
CGameManager::
Draw( void )
{
    // シーンマネージャー取得
    CSceneManager& sm = CSceneManager::GetInstance();

    // シーン描画
    sm.Draw();

    // エフェクトマネージャー描画
    CEffectManager::GetInstance().Draw();

    // シーンエフェクト描画
    sm.DrawSceneEffect();
}

/*
 *  解放
 */
void
CGameManager::
Finalize( void )
{
    // エフェクトマネージャー解放
    CEffectManager::GetInstance().Finalize();

    // シーンマネージャー解放
    CSceneManager::GetInstance().Finalize();
}

/*
 *  コンストラクタ
 */
CGameManager::
CGameManager( void )
{
}

/*
 *  コピーコンストラクタ
 */
CGameManager::
CGameManager( const CGameManager& rhs )
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CGameManager::
~CGameManager( void )
{
}

/*
 *  代入演算子
 */
CGameManager&
CGameManager::
operator=( const CGameManager& rhs )
{
    (void)rhs;

    return *this;
}
