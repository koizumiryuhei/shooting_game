#include "unit_manager.h"
#include <string>
#include "../scene_manager//scene_manager.h"
#include "../scene_manager/scene/game_main/game_main.h"
#include "../bullet_manager/bullet_manager.h"
#include "../../../utility/utility.h"
#include "unit/fighter/fighter.h"
#include "unit/ufo_small/ufo_small.h"
#include "unit/ufo_middle/ufo_middle.h"
#include "unit/ufo_large/ufo_large.h"
#include "unit//ufo_boss/ufo_boss.h"

const float CUnitManager::m_dummy_length = 99999999.0f;

/*!
 *  インスタンスの取得
 */
CUnitManager& 
CUnitManager::GetInstance()
{
    static CUnitManager instance;
    return instance;
}

/*!
 *  初期化
 */
void 
CUnitManager::
Initialize()
{
    m_UfoTable.clear();
    m_UnitList.clear();
    m_CreateTimer = 0;
    DeployUfo();
}

/*!
 *  更新
 */
void 
CUnitManager::
Update()
{
    UpdateUfoTable();

    UpdateUnit();
}

/*!
 *  描画
 */
void 
CUnitManager::
Draw()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*!
 *  解放
 */
void 
CUnitManager::
Finalize()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        (*it)->Finalize();
        delete(*it);
        ++it;
    }
}

/*!
 *  ユニット生成
 */
void 
CUnitManager::
Create(UNIT_ID id, const vivid::Vector2& pos)
{
    IUnit* unit = nullptr;

    switch (id)
    {
    case UNIT_ID::FIGHTER:    unit = new CFighter();     break;
    case UNIT_ID::UFO_SMALL:  unit = new CUfoSmall();    break;
    case UNIT_ID::UFO_MIDDLE: unit = new CUfoMiddle();   break;
    case UNIT_ID::UFO_LARGE:  unit = new CUfoLarge();    break;
    case UNIT_ID::UFO_BOSS:   unit = new CUfoBoss();     break;
    }

    if (!unit)return;
    unit->Initialize(pos);
    m_UnitList.push_back(unit);
}

/*!
 *  ユニットと弾の当たり判定
 */
void 
CUnitManager::
CheckHitBullet(IBullet* bullet)
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        if ((*it)->CheckHitBullet(bullet))
            return;

        ++it;
    }
}

/*!
 *  弾と一番近いユニットを探す
 */
IUnit* 
CUnitManager::
FindNearUnit(IBullet* bullet)
{
    if (m_UnitList.empty())return nullptr;
    UNIT_LIST::iterator it = m_UnitList.begin();
    vivid::Vector2 v;
    float min = m_dummy_length;
    IUnit* unit = nullptr;
    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitCategory() != bullet->GetBulletCategory())
        {
            v = (*it)->GetCenterPosition() - bullet->GetCenterPosition();
            if (v.Length() <= min)
            {
                min = v.Length();
                unit = (*it);
            }
        }

        ++it;
    }
    return unit;
}

/*!
 *  戦闘機取得
 */
IUnit* 
CUnitManager::
GetFighter()
{
    if (m_UnitList.empty())return nullptr;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == UNIT_ID::FIGHTER)
            return(*it);
        ++it;
    }
    return nullptr;
}

/*!
 *  残りのUFOを調べる
 */
bool 
CUnitManager::
CheckRemainingUfo()
{
    if (m_UnitList.empty())return false;
    if (!m_UfoTable.empty())return true;
    UNIT_LIST::iterator it = m_UnitList.begin();

    int count = 0;

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitCategory() == UNIT_CATEGORY::UFO)
            ++count;
        ++it;
    }

    return (count > 0) ? true : false;
}

/*!
 *  コンストラクタ
 */
CUnitManager::
CUnitManager()
{
}

/*!
 *  デストラクタ
 */
CUnitManager::
~CUnitManager()
{
}

/*!
 *  コピーコンストラクタ
 */
CUnitManager::
CUnitManager(const CUnitManager& rhs)
{
    (void)rhs;
}

/*!
 *  参照演算子
 */
CUnitManager& 
CUnitManager::
operator=(const CUnitManager& rhs)
{
    (void)rhs;
    return *this;
}

/*!
 *  UFOの配置
 */
void 
CUnitManager::
DeployUfo()
{
    // CSVローダーの宣言
    CCSVLoader csv_loader;
    //CSVファイルロード
    csv_loader.Load("data/ufo_table.csv");
    for (int i = 0; i < csv_loader.GetRows(); ++i)
    {
        UFO_TABLE_DATA t;
        t.id = (UNIT_ID)csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::ID);
        t.x = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::X);
        t.y = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::Y);
        t.create_frame = csv_loader.GetInteger(i, (int)UFO_TABLE_DATA_PARAM::CREATE_TIME);
        m_UfoTable.push_back(t);
    }

    // 解放
    csv_loader.Unload();
}

/*!
 *  UFOテーブル更新
 */
void 
CUnitManager::
UpdateUfoTable()
{
    if (m_UfoTable.empty())return;
    UFO_TABLE::iterator it = m_UfoTable.begin();
    UFO_TABLE_DATA t = *it;
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::T))
        m_CreateTimer += 500;
#endif
    if (++m_CreateTimer > t.create_frame)
    {
        vivid::Vector2 pos((float)(t.x), (float)(t.y));
        Create(t.id, pos);
        m_UfoTable.erase(it);
    }
}

/*!
 *  ユニット更新
 */
void 
CUnitManager::
UpdateUnit()
{
    if (m_UnitList.empty())return;
    UNIT_LIST::iterator it = m_UnitList.begin();
    while (it != m_UnitList.end())
    {
        IUnit* unit = (IUnit*)(*it);
        unit->Update();
        if (!unit->GetActive())
        {
            unit->Finalize();
            delete unit;
            it = m_UnitList.erase(it);
            continue;
        }

        ++it;
    }
}
