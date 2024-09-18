#pragma once

#include "vivid.h"

// サウンドID
enum class SOUND_ID
{
	BGM,
	SHOT,
	HOMING_SHOT,
	DESTORY,
	BOSS_DESTORY,
	FIGHTER_HIT,
	WARNING,
	WARNING_SHORT,
	GAMEOVER,
	GAMECLEAR,
	ZBUTTON,

	MAX,
};

/*!
 *	@brief	サウンドマネージャークラス
 */
class CSoundManager
{
public:

	/*!
	 *	@brief	インスタンスの取得
	 *
	 *	@return	サウンドマネージャークラスのインスタンス
	 */
	static CSoundManager& GetInstance();

	/*!
	 *	@brief	読み込み
	 */
	void Load();

	/*!
	 *	@brief	再生
	 */
	void Play(SOUND_ID id, bool loop);

	/*!
	 *	@brief	音量のセット
	 */
	void SetVolume(int volume);

	struct DATA
	{
		const int	m_max_volume = 255;
		const int	m_min_volume = 0;
		int			m_volume;
	};

private:

	/*!
	 *	@brief	コンストラクタ
	 */
	CSoundManager();

	/*!
	 *	@brief	コピーコンストラクタ
	 */
	CSoundManager(const CSoundManager& rhs);

	/*!
	 *	@brief	デストラクタ
	 */
	~CSoundManager();

	/*!
	 *	@brief	参照演算子
	 */
	CSoundManager& operator=(const CSoundManager& rhs);

	static const char* m_sound_file_names[(int)SOUND_ID::MAX];

	DATA m_Data;

};