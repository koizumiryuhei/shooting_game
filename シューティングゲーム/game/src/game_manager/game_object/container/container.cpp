#include "container.h"

CContainer& 
CContainer::
GetInstance(void)
{
	static CContainer instance;

	return instance;
}

void 
CContainer::
Initialize(void)
{
	m_Data.m_fighter_data.m_move_accelerator	 = (m_Data.m_fighter_data.m_up_limit_move_accelerator + m_Data.m_fighter_data.m_down_limit_move_accelerator) / 2.0f;
	m_Data.m_fighter_data.m_max_move_accelerator = (m_Data.m_fighter_data.m_up_limit_max_move_accelerator + m_Data.m_fighter_data.m_down_limit_max_move_accelerator) / 2.0f;
}
