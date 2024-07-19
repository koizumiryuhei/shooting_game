#include "sound_manager.h"

const char* CSoundManager::m_sound_file_names[] =
{
	"data\\bgm.wav",
	"data\\shot.wav",
	"data\\homing_shot.wav",
	"data\\destory.wav",
	"data\\boss_destory.wav",
	"data\\fighter_hit.wav",
	"data\\warning.wav",
	"data\\warning_short.wav",
	"data\\gameover.wav",
	"data\\gameclear.wav",
	"data\\z_button.wav",
};

CSoundManager& 
CSoundManager::
GetInstance()
{
	static CSoundManager instance;
	return instance;
}

void 
CSoundManager::
Load()
{
	for (int i = 0; i < (int)SOUND_ID::MAX; ++i)
		vivid::LoadSound(m_sound_file_names[i]);
}

void 
CSoundManager::
Play(SOUND_ID id, bool loop)
{
	vivid::PlaySound(m_sound_file_names[(int)id], loop);
}

CSoundManager::
CSoundManager()
{
}

CSoundManager::
CSoundManager(const CSoundManager& rhs)
{
	(void)rhs;
}

CSoundManager::
~CSoundManager()
{
}

CSoundManager& 
CSoundManager::
operator=(const CSoundManager& rhs)
{
	(void)rhs;

	return *this;
}
