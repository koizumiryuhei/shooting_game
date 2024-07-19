
/*!
 *  @file       game_main.cpp
 *  @brief      ゲームメインシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_main.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "..\..\..\..\..\utility\utility.h"

const int               CGameMain::m_fight_width            = 205;
const int               CGameMain::m_fight_height           = 53;
const int               CGameMain::m_gameclear_width        = 368;
const int               CGameMain::m_gameclear_height       = 54;
const int               CGameMain::m_gameover_width         = 361;
const int               CGameMain::m_gameover_height        = 54;
const vivid::Vector2    CGameMain::m_fight_position         = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_fight_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_fight_height / 2.0f);
const vivid::Vector2    CGameMain::m_gameclear_position     = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameclear_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameclear_height / 2.0f);
const vivid::Vector2    CGameMain::m_gameover_position      = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameover_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameover_height / 2.0f);

/*
 *  コンストラクタ
 */
CGameMain::
CGameMain(void)
{
}

/*
 *  デストラクタ
 */
CGameMain::
~CGameMain(void)
{
}

/*
 *  初期化
 */
void
CGameMain::
Initialize(void)
{
    m_Space.Initialize();

    CUnitManager::GetInstance().Initialize();
    CUnitManager::GetInstance().Create(UNIT_ID::FIGHTER, vivid::Vector2(0.0f, 0.0f));
    CBulletManager::GetInstance().Initialize();
    CUIManager::GetInstance().Initialize();

    m_WaitTime = 0;

    m_FihgtAlpha = 255;
    m_GameOverAlpha = 0;
    m_GameClearAlpha = 0;

    m_FightScale = vivid::Vector2(1.0f, 1.0f);
    m_GameClearScale = vivid::Vector2(10.0f, 10.0f);

    m_GameClearRotation = 0.0f;

    m_GameState = GAME_STATE::START;
}

/*
 *  更新
 */
void
CGameMain::
Update(void)
{
    switch (m_GameState)
    {
    case GAME_STATE::START:       Start();       break;
    case GAME_STATE::PLAY:        Play();        break;
    case GAME_STATE::GAMEOVER:    GameOver();    break;
    case GAME_STATE::GAMECLEAR:   GameClear();   break;
    }

    m_Space.Update();
    CUnitManager::GetInstance().Update();
    CBulletManager::GetInstance().Update();
    CUIManager::GetInstance().Update();
}

/*
 *  描画
 */
void
CGameMain::
Draw(void)
{
    m_Space.Draw();
    CUnitManager::GetInstance().Draw();
    CBulletManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();

    switch (m_GameState)
    {
    case GAME_STATE::START:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_fight_width, m_fight_height };
        const vivid::Vector2 anchor((float)m_fight_width / 2.0f, (float)m_fight_height / 2.0f);

        vivid::DrawTexture("data\\fight.png", m_fight_position);
        vivid::DrawTexture("data\\fight.png", m_fight_position, (m_FihgtAlpha << 24) | 0x00ffffff, rect, anchor, m_FightScale, 0.0f, vivid::ALPHABLEND::ADD);
    }
    break;
    case GAME_STATE::GAMEOVER:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_gameover_width, m_gameover_height };
        const vivid::Vector2 anchor((float)m_gameover_width / 2.0f, (float)m_gameover_height / 2.0f);

        vivid::DrawTexture("data\\gameover.png", m_gameclear_position, (m_GameOverAlpha << 24) | 0x00ffffff);
    }
    break;
    case GAME_STATE::GAMECLEAR:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_gameclear_width, m_gameclear_height };
        const vivid::Vector2 anchor((float)m_gameclear_width / 2.0f, (float)m_gameclear_height / 2.0f);

        vivid::DrawTexture("data\\gameclear.png", m_gameover_position, (m_GameClearAlpha << 24) | 0x00ffffff, rect, anchor, m_GameClearScale, m_GameClearRotation);
    }
    break;
    }
}

/*
 *  解放
 */
void
CGameMain::
Finalize(void)
{
    CUIManager::GetInstance().Finalize();
    CBulletManager::GetInstance().Finalize();
    CUnitManager::GetInstance().Finalize();
    m_Space.Finalize();
}

/*
 *  ゲームの状態取得
 */
GAME_STATE
CGameMain::
GetGameState(void)
{
    return m_GameState;
}

/*
 *  ゲームの状態設定
 */
void
CGameMain::
SetGameState(GAME_STATE state)
{
    m_GameState = state;
}

/*
 *  スタート
 */
void
CGameMain::
Start(void)
{
    if (m_WaitTime > 120)
    {
        m_WaitTime = 0;

        m_GameState = GAME_STATE::PLAY;
    }
    else if (m_WaitTime > 30)
    {
        m_FihgtAlpha -= 10;

        if (m_FihgtAlpha < 0)
            m_FihgtAlpha = 0;

        m_FightScale.x += 0.01f;
        m_FightScale.y += 0.01f;

        if (m_FightScale.x > 1.5f)
            m_FightScale.x = m_FightScale.y = 1.5f;
    }

    ++m_WaitTime;
}

/*
 *  プレイ
 */
void
CGameMain::
Play(void)
{
    CUnitManager& unit = CUnitManager::GetInstance();

    // ゲームオーバー
    if (!unit.GetFighter())
    {
        CSoundManager& sound = CSoundManager::GetInstance();
        sound.Play(SOUND_ID::GAMEOVER, false);
        m_GameState = GAME_STATE::GAMEOVER;
    }

    // ゲームクリア
    if (!unit.CheckRemainingUfo())
    {
        CSoundManager& sound = CSoundManager::GetInstance();
        sound.Play(SOUND_ID::GAMECLEAR, false);
        m_GameState = GAME_STATE::GAMECLEAR;
    }

}

/*
 *  ゲームオーバー
 */
void
CGameMain::
GameOver(void)
{
    if (m_WaitTime > 240)
    {
        m_WaitTime = 0;

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
    else if (m_WaitTime > 30)
    {
        m_GameOverAlpha += 2;

        if (m_GameOverAlpha > 255)
            m_GameOverAlpha = 255;
    }

    ++m_WaitTime;
}

/*
 *  ゲームクリア
 */
void
CGameMain::
GameClear(void)
{
    if (m_WaitTime > 240)
    {
        m_WaitTime = 0;

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
    else if (m_WaitTime > 30)
    {
        m_GameClearAlpha += 2;

        if (m_GameClearAlpha > 255)
            m_GameClearAlpha = 255;

        m_GameClearScale.x -= 0.2f;
        m_GameClearScale.y -= 0.2f;

        if (m_GameClearScale.x < 1.0f)
            m_GameClearScale.x = m_GameClearScale.y = 1.0f;

        m_GameClearRotation -= DEG_TO_RAD(20.0f);

        if (m_GameClearRotation < DEG_TO_RAD(-1100.0f))
            m_GameClearRotation = DEG_TO_RAD(-1100.0f);
    }

    ++m_WaitTime;
}
