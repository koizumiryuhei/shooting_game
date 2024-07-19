
/*!
 *  @file       utility.h
 *  @brief      ユーティリティ
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "vivid.h"
#include "csv_loader\csv_loader.h"

/*!
 *  @brief      角度をラジアン値に変換
 *
 *  @param[in]  d   角度
 *
 *  @return     ラジアン値
 */
#define DEG_TO_RAD( d )     (float)( (d) * 3.14f / 180.0f )

/*!
 *  @brief      色相環から色を取得
 *
 *  @param[in]  hue         色相
 *  @param[in]  saturation  彩度
 *  @param[in]  brightness  明度
 *
 *  @return     色
 */
unsigned int    ChangeHSVToColor(float hue, float saturation, float brightness);

/*!
 *  @brief      色相環から色を取得
 *
 *  @param[in]  step    節目となる値
 *  @param[in]  number  カラーに変換する数値
 *
 *  @return     色
 */
unsigned int    ChangeNumberToColor(int step, int number);
