
/*!
 *  @file       unit_id.h
 *  @brief      ユニットID
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief      ユニット識別ID
 */
enum class UNIT_CATEGORY
{
    UNKNOW,   //!< 所属不明
    FIGHTER,  //!< 戦闘機
    UFO,      //!< UFO
};

/*!
 *  @brief      ユニットID
 */
enum class UNIT_ID
{
    FIGHTER,        //!< 戦闘機
    UFO_SMALL,      //!< UFO(小)
    UFO_MIDDLE,     //!< UFO(中)
    UFO_LARGE,      //!< UFO(大)
    UFO_BOSS,       //!< UFO(ボス)
};
