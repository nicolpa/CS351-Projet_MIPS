#include "../include/ANSIColor.h"


void resetAttributes() 
{
    printf("%s[%dm", ESC, NORMAL);
}

void setForegroundColor(int color) 
{
    printf("%s[38;2;%dm", ESC, color);
}

void setBackgroundColor(int color) 
{
    printf("%s[48;2;%dm", ESC, color);
}

void setTextAttribute(int attribute) 
{
    printf("%s[%dm", ESC, attribute);
}