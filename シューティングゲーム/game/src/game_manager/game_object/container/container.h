#pragma once

/*
 *	@file	container.h
 *	@brief	変数置き場
 *	@author	RyuheiKoizumi
 *	@date	2024/9/13
 */

#include "../unit_manager/unit/fighter/fighter.h"
#include "../sound_manager/sound_manager.h"

class CContainer
{
private:

	struct DATA
	{
		CFighter::DATA m_fighter_data;
		CSoundManager::DATA m_sound_data;
	};

public:

	DATA m_Data;

	/*!
	 *	@brief	インスタンスの取得
	 */
	static CContainer& GetInstance(void);

	/*!
	 *	@brief	初期化
	 */
	void Initialize(void);

	/*!
	 *	@brief	ファイターデータ取得
	 */
	CFighter::DATA& GetFighterData(void) { return m_Data.m_fighter_data; }

	/*!
	 *	@brief	サウンドデータ取得
	 */
	CSoundManager::DATA& GetSoundData(void) { return m_Data.m_sound_data; }

};