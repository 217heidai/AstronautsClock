/*
 * ***********************************************
 * 修改自d88880(抖音号)的简易太空人时钟代码
 * 
 * 程序硬件介绍 ESP8266 + LCD屏幕（ST7789）
 * 屏幕使用的中景园1.3寸240分辨率全彩屏幕，7、8、10针脚的屏应该都可以，具体请自己参考引脚定义
 * 
 */
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <TJpg_Decoder.h>
#include <Buzzer.h>


#include "font/ZdyLwFont_20.h"
#include "font/FxLED_32.h"

#include "img/pangzi/i0.h"
#include "img/pangzi/i1.h"
#include "img/pangzi/i2.h"
#include "img/pangzi/i3.h"
#include "img/pangzi/i4.h"
#include "img/pangzi/i5.h"
#include "img/pangzi/i6.h"
#include "img/pangzi/i7.h"
#include "img/pangzi/i8.h"
#include "img/pangzi/i9.h"

#include "img/temperature.h"
#include "img/humidity.h"
#include "img/watch_top.h"
#include "img/watch_bottom.h"


const char ssid[] = "";  //WIFI名称
const char password[] = ""; //WIFI密码
String cityCode = "101020100"; //天气城市代码，上海

//RTC变量地址
#define RTCdz_sleep_count_night       0    //夜间计数地址RTC
//睡眠
#define SLEEP_COUNT_NIGHT_MAX        12    //需要跳过几次，20-8点不更新
#define SLEEP_TIME_START             20    //20点开始休眠
#define SLEEP_TIME_NIGHT             60    //夜间休眠60min
#define SLEEP_TIME_DAY                5    //白天休眠5min

TFT_eSPI tft = TFT_eSPI(); // 引脚请自行配置tft_espi库中的 User_Setup.h文件
TFT_eSprite clk = TFT_eSprite(&tft);
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
  if (y >= tft.height())
    return 0;
  tft.pushImage(x, y, w, h, bitmap);
  // Return 1 to decode next block
  return 1;
}

void setup()
{
  Serial.begin(115200);

  ESP.wdtFeed(); //喂狗

  //sleep_at_night(0); //夜间自动休眠

  //tft_init(); //屏幕初始化
  tft.begin();
  tft.setRotation(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.fillScreen(TFT_BLACK);
  
  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);

  if(!wifi_connect()) //连接wifi，并刷新进度条
  {//wifi连接失败进入休眠，休眠时长SLEEP_TIME_DAY
    esp_sleep(SLEEP_TIME_DAY);
  }

  ntp_init(); //ntp服务初始化

  //getCityCode(); //根据IP自动获取城市代码，用于后续天气显示

  tft_display_loading_complete(); //将进度条刷到100%

  tft_display_layout(); //绘制屏幕布局
}

time_t time_old = 0; //上次时间刷新时间
time_t weater_old = 0; //上次天气获取时间
time_t banner_old = 0; //上次banner刷新时间
time_t time_now = 0; //当前秒
time_t hour_old = 0;
time_t hour_now = 0;
void loop()
{
  //static time_t time_old = 0; //上次时间刷新时间
  //static time_t weater_old = 0; //上次天气获取时间
  //static time_t banner_old = 0; //上次banner刷新时间
  //static time_t time_now = now(); //当前秒
  time_now = now();
  hour_now = hour();
  //刷新时间信息，每秒刷新
  if (time_now != time_old)
  {
    time_old = time_now;
    tft_display_time();

    //Serial.printf("\nhour_old = %d, hour_now = %d\n", hour_old, hour_now);
    //整点报时
    if(hour_now != hour_old)
    {
      hour_old = hour_now;
      Beep(2);

      //if(hour_now >= SLEEP_TIME_START) //夜间休眠
      //{
      //  sleep_at_night(1);//立即休眠
      //}
    }
  }

  //刷新天气信息，每30分钟刷新
  if (time_now - weater_old > 30 * 60)
  {
    weater_old = time_now;
    getCityWeater();
  }
  
  //刷新banner，每3秒刷新
  if (time_now - banner_old > 2)
  {
    ESP.wdtFeed();//喂狗
    banner_old = time_now;
    tft_display_banner();
  }

  //刷新太空人图片
  tft_display_spaceman();
}
