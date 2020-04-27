#include "UI.h"

//包含ssd1306依赖库
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//使用引脚定义
#define OLED_DC PA11
#define OLED_CS 10
#define OLED_RESET PA12

//显示器显示尺寸定义
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);

void UI_begin()
{
    //显示器初始化
    display.begin(SSD1306_SWITCHCAPVCC);

    display.display();

    display.clearDisplay();

#ifdef UI_DEBUG
    Serial.print("UI_begin");
    Serial.println();
#endif
}

void UI_update()
{
    //清屏
    display.clearDisplay();

    //设置文字字体
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    //显示表头
    for (int i = 0; i < 8; i++)
    {
        display.setCursor(UI_str[i].X, UI_str[i].Y); // Start at top-left corner
        display.println(UI_str[i].string);
    }

    //显示数字
    for (int j = 0; j < 12; j++)
    {
        display.setCursor(UI_data[j].X, UI_data[j].Y); // Start at top-left corner
        display.println(UI_data[j].data);
    }

#ifdef UI_DEBUG
    Serial.print("UI_update");
    Serial.println();
#endif

}