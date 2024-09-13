#pragma once

/*
 *	@file	container.h
 *	@brief	変数置き場
 *	@author	RyuheiKoizumi
 *	@date	2024/9/13
 */

#include "../unit_manager/unit/fighter/fighter.h"

class CContainer
{
private:

	struct DATA
	{
		CFighter::DATA m_fighter_data;
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

};