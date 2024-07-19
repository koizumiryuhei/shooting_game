
#pragma once

#include "vivid.h"
#include "../bullet.h"

class CBossBullet : public IBullet
{
public:
	/*!
	 *	@brief	コンストラクタ
	 */
	CBossBullet();

	/*!
	 *	@brief	デストラクタ
	 */
	~CBossBullet();

	/*!
	 *	@brief	描画
	 */
	void Draw()override;

private:
	static const int    m_width;    //!< 幅
	static const int    m_height;   //!< 高さ
	static const float  m_radius;   //!< 半径

};