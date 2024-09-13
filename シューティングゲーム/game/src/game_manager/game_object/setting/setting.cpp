#include "setting.h"
#include "../container/container.h"

const int CSetting::m_var_width = 240;
const int CSetting::m_var_height = 32;
const int CSetting::m_point_width = 32;
const int CSetting::m_point_height = 32;
const vivid::Vector2 CSetting::m_accelerator_var_position = { (float)((vivid::WINDOW_WIDTH - m_var_width) / 2), 200.0f };
const vivid::Vector2 CSetting::m_max_accelerator_var_position = { (float)((vivid::WINDOW_WIDTH - m_var_width) / 2), 400.0f };
const vivid::Vector2 CSetting::m_point_anchor = { (float)m_point_width, (float)m_point_height };
const float CSetting::m_point_radius = 30;

CSetting& 
CSetting::
GetInstance(void)
{
    static CSetting instance;

    return instance;
}

void 
CSetting::
Initialize(void)
{
    CContainer& container = CContainer::GetInstance();

    float acce = container.GetFighterData().m_move_accelerator;
    float maxAcce = container.GetFighterData().m_max_move_accelerator;
    float acceRate = (acce - container.GetFighterData().m_down_limit_move_accelerator) / (container.GetFighterData().m_up_limit_move_accelerator - container.GetFighterData().m_down_limit_move_accelerator);
    float maxAcceRate = (maxAcce - container.GetFighterData().m_down_limit_max_move_accelerator) / (container.GetFighterData().m_up_limit_max_move_accelerator - container.GetFighterData().m_down_limit_max_move_accelerator);

    m_AcceleratorPointPosition = m_accelerator_var_position;
    m_MaxAcceleratorPointPosition = m_max_accelerator_var_position;

    m_AcceleratorPointPosition.x += (float)(m_var_width - m_point_width) * acceRate;
    m_MaxAcceleratorPointPosition.x += (float)(m_var_width - m_point_width) * maxAcceRate;

    m_SelectAcceleratorPoint = false;
    m_SelectMaxAcceleratorPoint = false;
}

void 
CSetting::
Draw(void)
{
    vivid::DrawTexture("data/var.png", m_accelerator_var_position);
    vivid::DrawTexture("data/var.png", m_max_accelerator_var_position);

    vivid::DrawTexture("data/ball.png", m_AcceleratorPointPosition, 0xffff0000);
    vivid::DrawTexture("data/ball.png", m_MaxAcceleratorPointPosition, 0xff0000ff);
}

void 
CSetting::
Setting(void)
{
    if (vivid::mouse::Released(vivid::mouse::BUTTON_ID::LEFT) && (m_SelectAcceleratorPoint || m_SelectMaxAcceleratorPoint))
    {
        m_SelectAcceleratorPoint = false;
        m_SelectMaxAcceleratorPoint = false;

        CContainer& container = CContainer::GetInstance();

        float acceUpLimit = container.GetFighterData().m_up_limit_move_accelerator - container.GetFighterData().m_down_limit_move_accelerator;
        float maxAcceUpLimit = container.GetFighterData().m_up_limit_max_move_accelerator - container.GetFighterData().m_down_limit_max_move_accelerator;
        float acceRate = (m_AcceleratorPointPosition.x - m_accelerator_var_position.x) / (m_var_width - m_point_anchor.x);
        float maxAcceRate = (m_MaxAcceleratorPointPosition.x - m_max_accelerator_var_position.x) / (m_var_width - m_point_anchor.x);

        container.GetFighterData().m_move_accelerator = acceUpLimit * acceRate + container.GetFighterData().m_down_limit_move_accelerator;
        container.GetFighterData().m_max_move_accelerator = maxAcceUpLimit * maxAcceRate + container.GetFighterData().m_down_limit_max_move_accelerator;
    }

    if (!vivid::mouse::Button(vivid::mouse::BUTTON_ID::LEFT))return;

    vivid::Point mouse = vivid::mouse::GetCursorPos();

    vivid::Vector2 pos;
    pos.x = mouse.x;
    pos.y = mouse.y;

    CheckPointCollision(pos);

    if (m_SelectAcceleratorPoint)
    {
        m_AcceleratorPointPosition.x = pos.x - m_point_anchor.x / 2.0f;

        if (m_AcceleratorPointPosition.x + m_point_anchor.x > m_accelerator_var_position.x + m_var_width)
        {
            m_AcceleratorPointPosition.x = m_accelerator_var_position.x + m_var_width - m_point_anchor.x;
        }
        else if (m_AcceleratorPointPosition.x < m_accelerator_var_position.x)
        {
            m_AcceleratorPointPosition.x = m_accelerator_var_position.x;
        }
    }
    else if (m_SelectMaxAcceleratorPoint)
    {
        m_MaxAcceleratorPointPosition.x = pos.x - m_point_anchor.x / 2.0f;

        if (m_MaxAcceleratorPointPosition.x + m_point_anchor.x > m_max_accelerator_var_position.x + m_var_width)
        {
            m_MaxAcceleratorPointPosition.x = m_max_accelerator_var_position.x + m_var_width - m_point_anchor.x;
        }
        else if (m_MaxAcceleratorPointPosition.x < m_max_accelerator_var_position.x)
        {
            m_MaxAcceleratorPointPosition.x = m_max_accelerator_var_position.x;
        }
    }
}

CSetting::
CSetting()
{
}

CSetting::
CSetting(const CSetting& rhs)
{
    (void)rhs;
}

CSetting::
~CSetting()
{
}

CSetting& 
CSetting::
operator=(const CSetting& rhs)
{
    (void)rhs;

    return (*this);
}

void CSetting::CheckPointCollision(vivid::Vector2 pos)
{
    vivid::Vector2 vec = pos - m_AcceleratorPointPosition;

    float length = sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length < m_point_radius)
    {
        m_SelectAcceleratorPoint = true;
    }

    vec = pos - m_MaxAcceleratorPointPosition;
    length = sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length < m_point_radius)
    {
        m_SelectMaxAcceleratorPoint = true;
    }
}
