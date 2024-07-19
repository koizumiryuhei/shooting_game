#include "effect.h"

IEffect::
IEffect()
	: m_Width(0)
	, m_Height(0)
	, m_Position(vivid::Vector2::ZERO)
	, m_Color(0xffffffff)
	, m_Anchor(vivid::Vector2::ZERO)
	, m_Rect({0,0,0,0})
	, m_Scale(vivid::Vector2::ONE)
	, m_Rotation(0.0f)
	, m_ActiveFlag(true)
{
}

IEffect::
IEffect(int width, int height)
	: m_Width(width)
	, m_Height(height)
	, m_Position(vivid::Vector2::ZERO)
	, m_Color(0xffffffff)
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect({0,0,m_Width,m_Height})
	, m_Scale(vivid::Vector2::ONE)
	, m_Rotation(0.0f)
	, m_ActiveFlag(true)
{
}

IEffect::
~IEffect()
{
}

void 
IEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
	m_Position		= position;
	m_Color			= color;
	m_Rotation		= rotation;
	m_ActiveFlag	= true;
}

void 
IEffect::
Update()
{
}

void 
IEffect::
Draw()
{
}

void 
IEffect::
Finalize()
{
}

vivid::Vector2 
IEffect::
GetPosition()
{
	return m_Position;
}

void 
IEffect::
SetPosition(const vivid::Vector2& position)
{
	m_Position = position;
}

bool 
IEffect::
GetActive()
{
	return m_ActiveFlag;
}

void 
IEffect::
SetActive(bool active)
{
	m_ActiveFlag = active;
}
