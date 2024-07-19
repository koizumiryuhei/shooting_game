
/*!
 *  @file       utility.cpp
 *  @brief      ユーティリティ
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "utility.h"

/*
 *  色相環
 */
unsigned int
ChangeHSVToColor(float hue, float saturation, float brightness)
{
    int r = 0, g = 0, b = 0;
    int region = 0;
    float fraction = 0.0f;
    int min = 0, max = 0, up = 0, down = 0;

    while (hue > 360.0f || hue < 0.0f)
    {
        if (hue >= 360.0f)     hue -= 360.0f;
        else if (hue < 0.0f)   hue += 360.0f;
    }

    if (saturation > 1.0f) saturation = 1.0f;
    else if (saturation < 0.0f) saturation = 0.0f;

    if (brightness > 1.0f) brightness = 1.0f;
    else if (brightness < 0.0f) brightness = 0.0f;

    max = (int)(brightness * 255);

    if (saturation == 0.0f)
    {
        r = max;
        g = max;
        b = max;
    }
    else
    {
        region = (int)(hue / 60.0f);
        fraction = hue / 60.0f - region;
        min = (int)(max * (1.0f - saturation));
        up = min + (int)(fraction * max * saturation);
        down = max - (int)(fraction * max * saturation);

        switch (region)
        {
        case 0:r = max;  g = up;  b = min; break;
        case 1:r = down;  g = max; b = min; break;
        case 2:r = min;  g = max; b = up;  break;
        case 3:r = min;  g = down; b = max; break;
        case 4:r = up;   g = min; b = max; break;
        case 5:r = max;  g = min; b = down; break;
        }
    }

    return (0xff << 24 | (unsigned char)r << 16 | (unsigned char)g << 8 | (unsigned char)b);
}

/*
 *  色相環より色の取得
 */
unsigned int
ChangeNumberToColor(int step, int number)
{
    number %= step;

    float hue = 360.0f / (float)step * (float)number;

    return ChangeHSVToColor(hue, 1.0f, 1.0f);
}
