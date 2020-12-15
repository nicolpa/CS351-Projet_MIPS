#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ANSI_COLOR
#define ANSI_COLOR

#define ESC "\x1b"

enum ANSIColorCode
{
    DEFAULT_CODE = 39,
    BLACK_CODE = 30,
    RED_CODE,
    GREEN_CODE,
    YELLOW_CODE,
    BLUE_CODE,
    MAGENTA_CODE,
    CYAN_CODE,
    LIGHT_GREY_CODE,
    DARK_GREY_CODE = 90,

    LIGHT_RED_CODE,
    LIGHT_GREEN_CODE,
    LIGHT_YELLOW_CODE,
    LIGHT_BLUE_CODE,
    LIGHT_MAGENTA_CODE, 
    LIGHT_CYAN_CODE,
    WHITE_CODE
};

enum Attribute
{
    NORMAL,
    BOLD,
    FAINT,
    ITALIC,
    UNDERLINED,
    BLINK,
    REVERSE = 7,
    HIDDEN
};

enum Clear
{
    CLEAR_FROM_CURSOR_TO_END,
    CLEAR_FROM_CURSOR_TO_BEGIN,
    CLEAR_ALL
};

enum FontRatio
{
    DOUBLE_HEIGHT_TOP_HALF = 3,
    DOUBLE_HEIGHT_BOTTOM_HALF,
    SINGLE_WIDTH_SINGLE_HEIGHT,
    DOUBLE_WIDTH_SINGLE_HEIGHT
};

/**
 * Reset all attributes of the terminal
 */
void resetAttributes();

/**
 * Change the text color
 * @param The new color for the text
 */
void setForegroundColor(int color);

/**
 * Set the text's background
 * @param color The background color
 */
void setBackgroundColor(int color);

/**
 * Set the attribute for the text
 * @param attribute The attribute to apply on the text
 */
void setTextAttribute(int attribute);

#endif