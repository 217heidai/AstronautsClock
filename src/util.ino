extern String num2str(int digits)
{
  String s = "";
  if (digits < 10)
    s = s + "0";
  s = s + digits;
  return s;
}

//星期
extern String week(void)
{
  String wk[7] = {"日", "一", "二", "三", "四", "五", "六"};
  String s = "周" + wk[weekday() - 1];
  return s;
}

//月日
extern String monthDay(void)
{
  String s = String(month());
  s = s + "月" + day() + "日";
  return s;
}

//时分
extern String hourMinute(void)
{
  String s = num2str(hour());
  s = s + ":" + num2str(minute());
  return s;
}

//关闭显示
#define TFT_COMMAND_SLPIN                        0x10  //tft command: SLPIN(10h): Sleep In mode
#define TFT_COMMAND_DLPOFFSAVE                   0xBD  //tft command: DLPOFFSAVE (BDh): Display off power save
#define TFT_COMMANDDATA_DOFSAVE                  0x00  //tft command data: Power save for display off mode. When DOFSAVE=0, power consumption in display off mode will be saved.
#define TFT_COMMAND_DELAY                          10  //delay 10ms for next command
static void tft_display_off(void)
{
  tft.writecommand(TFT_COMMAND_SLPIN); //tft 设置为 Sleep In mode
  delayMicroseconds(TFT_COMMAND_DELAY);

  tft.writecommand(TFT_COMMAND_DLPOFFSAVE); //tft 设置为 Display off power save
  delayMicroseconds(TFT_COMMAND_DELAY);
  tft.writedata(TFT_COMMANDDATA_DOFSAVE);
  delayMicroseconds(TFT_COMMAND_DELAY);
}

//系统休眠
extern void esp_sleep(unsigned char minutes)
{
  tft_display_off(); //关闭显示

  if (minutes > 70) minutes = 70;  //esp8266的最大睡眠时间间隔为 4,294,967,295 µs 约合71分钟
  ESP.deepSleep(minutes * 60 * 1000000, WAKE_NO_RFCAL);  //WAKE_RF_DEFAULT  WAKE_RFCAL  WAKE_NO_RFCAL  WAKE_RF_DISABLED
}

extern void sleep_at_night(unsigned char type) //夜间休眠, 0-自动，1-立即
{
  uint32_t RTC_sleep_count_night = 0;   //20-8点不更新
  
  //立即休眠
  if (type == 1)
  {
    RTC_sleep_count_night = 1;
    ESP.rtcUserMemoryWrite(RTCdz_sleep_count_night, &RTC_sleep_count_night, sizeof(RTC_sleep_count_night));
    esp_sleep(SLEEP_TIME_NIGHT);
  }

  //自动判断是否休眠
  ESP.rtcUserMemoryRead(RTCdz_sleep_count_night, &RTC_sleep_count_night, sizeof(RTC_sleep_count_night));
  Serial.printf("RTC_sleep_count_night: %d\n", RTC_sleep_count_night);
  if (RTC_sleep_count_night < SLEEP_COUNT_NIGHT_MAX) // 继续休眠
  {
    RTC_sleep_count_night++;
    ESP.rtcUserMemoryWrite(RTCdz_sleep_count_night, &RTC_sleep_count_night, sizeof(RTC_sleep_count_night));
    esp_sleep(SLEEP_TIME_NIGHT);
  }
}