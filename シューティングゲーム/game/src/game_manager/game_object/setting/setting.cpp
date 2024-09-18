#include "setting.h"
#include "../container/container.h"

const int               CSetting::m_var_width                       = 240;
const int               CSetting::m_var_height                      = 32;
const int               CSetting::m_point_width                     = 32;
const int               CSetting::m_point_height                    = 32;
const vivid::Vector2    CSetting::m_accelerator_var_position        = { (float)((vivid::WINDOW_WIDTH - m_var_width) / 2), 150.0f };
const vivid::Vector2    CSetting::m_max_accelerator_var_position    = { (float)((vivid::WINDOW_WIDTH - m_var_width) / 2), 300.0f };
const vivid::Vector2    CSetting::m_volume_var_position             = { (float)((vivid::WINDOW_WIDTH - m_var_width) / 2), 500.0f };
const vivid::Vector2    CSetting::m_point_anchor                    = { (float)m_point_width / 2.0f, (float)m_point_height / 2.0f };
const float             CSetting::m_point_radius                    = 30;

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

    float acce      = container.GetFighterData().m_move_accelerator;
    float maxAcce   = container.GetFighterData().m_max_move_accelerator;
    int   volume    = container.GetSoundData().m_volume;
    float acceRate      = (acce - container.GetFighterData().m_down_limit_move_accelerator) / (container.GetFighterData().m_up_limit_move_accelerator - container.GetFighterData().m_down_limit_move_accelerator);
    float maxAcceRate   = (maxAcce - container.GetFighterData().m_down_limit_max_move_accelerator) / (container.GetFighterData().m_up_limit_max_move_accelerator - container.GetFighterData().m_down_limit_max_move_accelerator);
    float volumeRate    = (float)(volume - container.GetSoundData().m_min_volume) / (float)(container.GetSoundData().m_max_volume - container.GetSoundData().m_min_volume);

    m_AcceleratorPointPosition      = m_accelerator_var_position;
    m_MaxAcceleratorPointPosition   = m_max_accelerator_var_position;
    m_VolumePointPosition           = m_volume_var_position;

    m_AcceleratorPointPosition.x    += (float)(m_var_width - m_point_width) * acceRate;
    m_MaxAcceleratorPointPosition.x += (float)(m_var_width - m_point_width) * maxAcceRate;
    m_VolumePointPosition.x         += (float)(m_var_width - m_point_width) * volumeRate;

    m_SelectAcceleratorPoint    = false;
    m_SelectMaxAcceleratorPoint = false;
    m_SelectVolumePoint         = false;
}

void 
CSetting::
Draw(void)
{
    vivid::DrawText(30, "プレイヤー移動速度", { 10.0f,10.0f });
    vivid::DrawText(25, "加速値", { m_accelerator_var_position.x, m_accelerator_var_position.y - 25.0f });
    vivid::DrawText(25, "最大速度", { m_max_accelerator_var_position.x, m_max_accelerator_var_position.y - 25.0f });
    vivid::DrawTexture("data/var.png", m_accelerator_var_position);
    vivid::DrawTexture("data/var.png", m_max_accelerator_var_position);
    vivid::DrawText(30, "音量設定", { 10.0f, m_volume_var_position.y - 100.0f });
    vivid::DrawTexture("data/var.png", m_volume_var_position);

    vivid::DrawTexture("data/ball.png", m_AcceleratorPointPosition, 0xffff0000);
    vivid::DrawTexture("data/ball.png", m_MaxAcceleratorPointPosition, 0xff0000ff);
    vivid::DrawTexture("data/ball.png", m_VolumePointPosition, 0xffffff00);

    //float acceRate = (m_AcceleratorPointPosition.x - m_accelerator_var_position.x) / (m_var_width - m_point_width) * 100.0f + 0.01f;
    //float maxAcceRate = (m_MaxAcceleratorPointPosition.x - m_max_accelerator_var_position.x) / (m_var_width - m_point_width) * 100.0f;

    //std::string t_acceRate = std::to_string((int)acceRate);
    //std::string t_maxAcceRate = std::to_string((int)maxAcceRate);

    vivid::DrawText(25, "速い", { m_accelerator_var_position.x + m_var_width + 5.0f, m_accelerator_var_position.y });
    vivid::DrawText(25, "速い", { m_max_accelerator_var_position.x + m_var_width + 5.0f, m_max_accelerator_var_position.y });
    vivid::DrawText(25, "大きい", { m_volume_var_position.x + m_var_width + 5.0f, m_volume_var_position.y });
    vivid::DrawText(25, "遅い", { m_accelerator_var_position.x - 55.0f, m_accelerator_var_position.y });
    vivid::DrawText(25, "遅い", { m_max_accelerator_var_position.x - 55.0f, m_max_accelerator_var_position.y });
    vivid::DrawText(25, "小さい", { m_volume_var_position.x - 80.0f, m_volume_var_position.y });
}

void 
CSetting::
Setting(void)
{
    CContainer& container = CContainer::GetInstance();

    if (vivid::mouse::Released(vivid::mouse::BUTTON_ID::LEFT) && (m_SelectAcceleratorPoint || m_SelectMaxAcceleratorPoint || m_SelectVolumePoint))
    {
        m_SelectAcceleratorPoint = false;
        m_SelectMaxAcceleratorPoint = false;
        m_SelectVolumePoint = false;

        float acceUpLimit       = container.GetFighterData().m_up_limit_move_accelerator - container.GetFighterData().m_down_limit_move_accelerator;
        float maxAcceUpLimit    = container.GetFighterData().m_up_limit_max_move_accelerator - container.GetFighterData().m_down_limit_max_move_accelerator;
        float acceRate      = ( m_AcceleratorPointPosition.x - m_accelerator_var_position.x ) / ( m_var_width - m_point_width );
        float maxAcceRate   = ( m_MaxAcceleratorPointPosition.x - m_max_accelerator_var_position.x ) / ( m_var_width - m_point_width );

        container.GetFighterData().m_move_accelerator = acceUpLimit * acceRate + container.GetFighterData().m_down_limit_move_accelerator;
        container.GetFighterData().m_max_move_accelerator = maxAcceUpLimit * maxAcceRate + container.GetFighterData().m_down_limit_max_move_accelerator;
    }

    if (!vivid::mouse::Button(vivid::mouse::BUTTON_ID::LEFT))return;

    vivid::Point mouse = vivid::mouse::GetCursorPos();

    vivid::Vector2 pos;
    pos.x = mouse.x;
    pos.y = mouse.y;

    CheckPointCollision(pos - m_point_anchor);

    if (m_SelectAcceleratorPoint)
    {
        m_AcceleratorPointPosition.x = pos.x - m_point_anchor.x;

        // マウスの位置に合わせる
        if (m_AcceleratorPointPosition.x + m_point_width > m_accelerator_var_position.x + m_var_width)
        {
            m_AcceleratorPointPosition.x = m_accelerator_var_position.x + m_var_width - m_point_width;
        }
        else if (m_AcceleratorPointPosition.x < m_accelerator_var_position.x)
        {
            m_AcceleratorPointPosition.x = m_accelerator_var_position.x;
        }
    }
    else if (m_SelectMaxAcceleratorPoint)
    {
        m_MaxAcceleratorPointPosition.x = pos.x - m_point_anchor.x;

        // マウスの位置に合わせる
        if (m_MaxAcceleratorPointPosition.x + m_point_width > m_max_accelerator_var_position.x + m_var_width)
        {
            m_MaxAcceleratorPointPosition.x = m_max_accelerator_var_position.x + m_var_width - m_point_width;
        }
        else if (m_MaxAcceleratorPointPosition.x < m_max_accelerator_var_position.x)
        {
            m_MaxAcceleratorPointPosition.x = m_max_accelerator_var_position.x;
        }
    }
    else if (m_SelectVolumePoint)
    {
        int   volumeUpLimit = container.GetSoundData().m_max_volume - container.GetSoundData().m_min_volume;
        float volumeRate = (m_VolumePointPosition.x - m_volume_var_position.x) / (m_var_width - m_point_width);
        container.GetSoundData().m_volume = (int)((float)volumeUpLimit * volumeRate + (float)container.GetSoundData().m_min_volume);

        CSoundManager::GetInstance().SetVolume(container.GetSoundData().m_volume);

        m_VolumePointPosition.x = pos.x - m_point_anchor.x;

        // マウスの位置に合わせる
        if (m_VolumePointPosition.x + m_point_width > m_volume_var_position.x + m_var_width)
        {
            m_VolumePointPosition.x = m_volume_var_position.x + m_var_width - m_point_width;
        }
        else if (m_VolumePointPosition.x < m_volume_var_position.x)
        {
            m_VolumePointPosition.x = m_volume_var_position.x;
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
    if (m_SelectAcceleratorPoint || m_SelectMaxAcceleratorPoint || m_SelectVolumePoint)return;

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

    vec = pos - m_VolumePointPosition;
    length = sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length < m_point_radius)
    {
        m_SelectVolumePoint = true;
    }
}
