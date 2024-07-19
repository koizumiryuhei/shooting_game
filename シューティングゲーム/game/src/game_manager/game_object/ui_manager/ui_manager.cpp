#include "ui_manager.h"

CUIManager& CUIManager::GetInstance()
{
	static CUIManager instance;

	return instance;
}

void CUIManager::Initialize()
{
	m_FighterLifeGauge.Initialize();
}

void CUIManager::Update()
{
	m_FighterLifeGauge.Update();
}

void CUIManager::Draw()
{
	m_FighterLifeGauge.Draw();
}

void CUIManager::Finalize()
{
	m_FighterLifeGauge.Finalize();
}

CUIManager::CUIManager()
{
}

CUIManager::CUIManager(const CUIManager& rhs)
{
	(void)rhs;
}

CUIManager::~CUIManager()
{
}

CUIManager& CUIManager::operator=(const CUIManager& rhs)
{
	(void)rhs;

	return *this;
}
