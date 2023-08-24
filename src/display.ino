//初始化屏幕
extern void tft_init(void)
{
  tft.begin();
  tft.setRotation(0);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.fillScreen(TFT_BLACK);
  
  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

//进度条
byte loadNum = 6;
extern void tft_display_loading(byte delayTime)
{
  clk.setColorDepth(8);
  clk.createSprite(200, 50);
  clk.fillSprite(TFT_BLACK);

  clk.drawRoundRect(0, 0, 200, 16, 8, TFT_WHITE);
  clk.fillRoundRect(3, 3, loadNum, 10, 5, TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_GREEN, TFT_BLACK);
  clk.drawString("Connecting to WiFi", 100, 40, 2);
  clk.pushSprite(20, 110);
  clk.deleteSprite();
  loadNum += 1;
  if (loadNum >= 194)
  {
    loadNum = 194;
  }
  delay(delayTime);
}

//将进度条刷到100%
extern void tft_display_loading_complete(void)
{
  while (loadNum < 194)
  { //让动画走完
    tft_display_loading(1);
  }
} 

//绘制屏幕布局
extern void tft_display_layout(void)
{
  //绘制顶部视图
  //TJpgDec.drawJpg(0, 0, watchtop, sizeof(watchtop));

  //绘制底部视图
  //TJpgDec.drawJpg(0, 220, watchbottom, sizeof(watchbottom));

  //绘制中间显示窗口
  tft.setViewport(0, 0, 240, 240);
  tft.fillScreen(TFT_BLACK);
  tft.fillRoundRect(0, 0, 240, 240, 7, TFT_WHITE); //实心圆角矩形

  //在窗口内绘制线框
  tft.drawFastHLine(0, 34, 240, TFT_BLACK);
  tft.drawFastVLine(150, 0, 34, TFT_BLACK);
  tft.drawFastHLine(0, 206, 240, TFT_BLACK);
  tft.drawFastVLine(60, 206, 34, TFT_BLACK);
  tft.drawFastVLine(160, 206, 34, TFT_BLACK);

  //在窗口内绘制图标
  TJpgDec.drawJpg(162, 150, humidity, sizeof(humidity));       //湿度图标
  TJpgDec.drawJpg(163, 210, temperature, sizeof(temperature)); //温度图标
}

//刷新时间显示
extern void tft_display_time(void)
{
  static String hourMinute_old = "";
  static String second_old = "";
  static String week_old = "";
  static String monthDay_old = "";

  String hourMinute_now = hourMinute();
  String second_now = num2str(second());
  String week_now = week();
  String monthDay_now = monthDay();

  clk.setColorDepth(8);

  /***中间时间区***/
  //时分
  if(hourMinute_now != hourMinute_old)
  {
    hourMinute_old = hourMinute_now;

    clk.createSprite(140, 48);
    clk.fillSprite(TFT_WHITE);
    //clk.loadFont(FxLED_48);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(hourMinute_now, 70, 24, 7); //绘制时和分
    //clk.unloadFont();
    clk.pushSprite(28, 40);
    clk.deleteSprite();
  }
  //秒
  if(second_now != second_old)
  {
    second_old = second_now;
    clk.createSprite(40, 32);
    clk.fillSprite(TFT_WHITE);

    clk.loadFont(FxLED_32);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(second_now, 20, 16);

    clk.unloadFont();
    clk.pushSprite(170, 60);
    clk.deleteSprite();
  }

  /***底部***/
  clk.loadFont(ZdyLwFont_20);
  //星期
  if(week_now != week_old)
  {
    week_old = week_now;
    clk.createSprite(56, 30);
    clk.fillSprite(TFT_WHITE);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(week_now, 28, 15);
    clk.pushSprite(2, 208);
    clk.deleteSprite();
  }
  //月日
  if(monthDay_now != monthDay_old)
  {
    monthDay_old = monthDay_now;
    clk.createSprite(98, 30);
    clk.fillSprite(TFT_WHITE);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(monthDay_now, 49, 15);
    clk.pushSprite(61, 208);
    clk.deleteSprite();
  }
  clk.unloadFont();
}

//刷新gif
extern void tft_display_gif(bool isChangeMode)
{
  static uint8_t mode = 0;
  static uint8_t index = 0;
  static uint32_t time_old = 0;
  uint8_t x,y,dt;
  uint32_t time_now = 0;

  if(isChangeMode)
  {
    mode += 1;
    if(mode > 3) mode=1;
    index = 0;
    time_old = 0;
  }

  //修改动画的播放速度
  switch(mode) {
    case 1:x=80;y=104;dt=40;break;  //动画-龙猫跳绳
    case 2:x=80;y=114;dt=50;break;  //动画-龙猫转圈
    case 3:x=83;y=114;dt=30;break;  //动画-太空人(胖)
  }

  time_now = millis();
  if(time_now - time_old >= dt) 
  {
    index += 1;
    time_old = time_now;
  }
  if(mode == 1) { //动画-龙猫跳绳
    switch(index) {
      case 1:  TJpgDec.drawJpg(x,y,chinchilla_1_0, sizeof(chinchilla_1_0));break;
      case 2:  TJpgDec.drawJpg(x,y,chinchilla_1_1, sizeof(chinchilla_1_1));break;
      case 3:  TJpgDec.drawJpg(x,y,chinchilla_1_2, sizeof(chinchilla_1_2));break;
      case 4:  TJpgDec.drawJpg(x,y,chinchilla_1_3, sizeof(chinchilla_1_3));break;
      case 5:  TJpgDec.drawJpg(x,y,chinchilla_1_4, sizeof(chinchilla_1_4));break;
      case 6:  TJpgDec.drawJpg(x,y,chinchilla_1_5, sizeof(chinchilla_1_5));break;
      case 7:  TJpgDec.drawJpg(x,y,chinchilla_1_6, sizeof(chinchilla_1_6));break;
      case 8:  TJpgDec.drawJpg(x,y,chinchilla_1_7, sizeof(chinchilla_1_7));break;
      case 9:  TJpgDec.drawJpg(x,y,chinchilla_1_8, sizeof(chinchilla_1_8));break;
      case 10: TJpgDec.drawJpg(x,y,chinchilla_1_9, sizeof(chinchilla_1_9));break;
      case 11: TJpgDec.drawJpg(x,y,chinchilla_1_10, sizeof(chinchilla_1_10));break;
      case 12: TJpgDec.drawJpg(x,y,chinchilla_1_11, sizeof(chinchilla_1_11));break;
      case 13: TJpgDec.drawJpg(x,y,chinchilla_1_12, sizeof(chinchilla_1_12));break;
      case 14: TJpgDec.drawJpg(x,y,chinchilla_1_13, sizeof(chinchilla_1_13));break;
      case 15: TJpgDec.drawJpg(x,y,chinchilla_1_14, sizeof(chinchilla_1_14));break;
      case 16: TJpgDec.drawJpg(x,y,chinchilla_1_15, sizeof(chinchilla_1_15));break;
      case 17: TJpgDec.drawJpg(x,y,chinchilla_1_16, sizeof(chinchilla_1_16));break;
      case 18: TJpgDec.drawJpg(x,y,chinchilla_1_17, sizeof(chinchilla_1_17));break;
      case 19: TJpgDec.drawJpg(x,y,chinchilla_1_18, sizeof(chinchilla_1_18));break;
      case 20: TJpgDec.drawJpg(x,y,chinchilla_1_19, sizeof(chinchilla_1_19));break;
      case 21: TJpgDec.drawJpg(x,y,chinchilla_1_20, sizeof(chinchilla_1_20));break;
      case 22: TJpgDec.drawJpg(x,y,chinchilla_1_21, sizeof(chinchilla_1_21));break;
      case 23: TJpgDec.drawJpg(x,y,chinchilla_1_22, sizeof(chinchilla_1_22));break;
      case 24: TJpgDec.drawJpg(x,y,chinchilla_1_23, sizeof(chinchilla_1_23));break;
      case 25: TJpgDec.drawJpg(x,y,chinchilla_1_24, sizeof(chinchilla_1_24));break;
      case 26: TJpgDec.drawJpg(x,y,chinchilla_1_25, sizeof(chinchilla_1_25));break;
      case 27: TJpgDec.drawJpg(x,y,chinchilla_1_26, sizeof(chinchilla_1_26));break;
      case 28: TJpgDec.drawJpg(x,y,chinchilla_1_27, sizeof(chinchilla_1_27));break;
      case 29: TJpgDec.drawJpg(x,y,chinchilla_1_28, sizeof(chinchilla_1_28));break;
      case 30: TJpgDec.drawJpg(x,y,chinchilla_1_29, sizeof(chinchilla_1_29));break;
      case 31: TJpgDec.drawJpg(x,y,chinchilla_1_30, sizeof(chinchilla_1_30));break;
      case 32: TJpgDec.drawJpg(x,y,chinchilla_1_31, sizeof(chinchilla_1_31));break;
      case 33: TJpgDec.drawJpg(x,y,chinchilla_1_32, sizeof(chinchilla_1_32));break;
      case 34: TJpgDec.drawJpg(x,y,chinchilla_1_33, sizeof(chinchilla_1_33));break;
      case 35: TJpgDec.drawJpg(x,y,chinchilla_1_34, sizeof(chinchilla_1_34));break;
      case 36: TJpgDec.drawJpg(x,y,chinchilla_1_35, sizeof(chinchilla_1_35));break;
      case 37: TJpgDec.drawJpg(x,y,chinchilla_1_36, sizeof(chinchilla_1_36));break;
      case 38: TJpgDec.drawJpg(x,y,chinchilla_1_37, sizeof(chinchilla_1_37));break;
      case 39: TJpgDec.drawJpg(x,y,chinchilla_1_38, sizeof(chinchilla_1_38));break;
      case 40: TJpgDec.drawJpg(x,y,chinchilla_1_39, sizeof(chinchilla_1_39));index=0;break;
    }
  }
  else if(mode == 2) { //动画-龙猫转圈
    switch(index) {
      case 1:  TJpgDec.drawJpg(x,y,chinchilla_2_0, sizeof(chinchilla_2_0));break;
      case 2:  TJpgDec.drawJpg(x,y,chinchilla_2_1, sizeof(chinchilla_2_1));break;
      case 3:  TJpgDec.drawJpg(x,y,chinchilla_2_2, sizeof(chinchilla_2_2));break;
      case 4:  TJpgDec.drawJpg(x,y,chinchilla_2_3, sizeof(chinchilla_2_3));break;
      case 5:  TJpgDec.drawJpg(x,y,chinchilla_2_4, sizeof(chinchilla_2_4));break;
      case 6:  TJpgDec.drawJpg(x,y,chinchilla_2_5, sizeof(chinchilla_2_5));break;
      case 7:  TJpgDec.drawJpg(x,y,chinchilla_2_6, sizeof(chinchilla_2_6));break;
      case 8:  TJpgDec.drawJpg(x,y,chinchilla_2_7, sizeof(chinchilla_2_7));break;
      case 9:  TJpgDec.drawJpg(x,y,chinchilla_2_8, sizeof(chinchilla_2_8));break;
      case 10: TJpgDec.drawJpg(x,y,chinchilla_2_9, sizeof(chinchilla_2_9));break;
      case 11: TJpgDec.drawJpg(x,y,chinchilla_2_10, sizeof(chinchilla_2_10));break;
      case 12: TJpgDec.drawJpg(x,y,chinchilla_2_11, sizeof(chinchilla_2_11));break;
      case 13: TJpgDec.drawJpg(x,y,chinchilla_2_12, sizeof(chinchilla_2_12));break;
      case 14: TJpgDec.drawJpg(x,y,chinchilla_2_13, sizeof(chinchilla_2_13));break;
      case 15: TJpgDec.drawJpg(x,y,chinchilla_2_14, sizeof(chinchilla_2_14));break;
      case 16: TJpgDec.drawJpg(x,y,chinchilla_2_15, sizeof(chinchilla_2_15));break;
      case 17: TJpgDec.drawJpg(x,y,chinchilla_2_16, sizeof(chinchilla_2_16));break;
      case 18: TJpgDec.drawJpg(x,y,chinchilla_2_17, sizeof(chinchilla_2_17));break;
      case 19: TJpgDec.drawJpg(x,y,chinchilla_2_18, sizeof(chinchilla_2_18));break;
      case 20: TJpgDec.drawJpg(x,y,chinchilla_2_19, sizeof(chinchilla_2_19));break;
      case 21: TJpgDec.drawJpg(x,y,chinchilla_2_20, sizeof(chinchilla_2_20));break;
      case 22: TJpgDec.drawJpg(x,y,chinchilla_2_21, sizeof(chinchilla_2_21));break;
      case 23: TJpgDec.drawJpg(x,y,chinchilla_2_22, sizeof(chinchilla_2_22));break;
      case 24: TJpgDec.drawJpg(x,y,chinchilla_2_23, sizeof(chinchilla_2_23));break;
      case 25: TJpgDec.drawJpg(x,y,chinchilla_2_24, sizeof(chinchilla_2_24));break;
      case 26: TJpgDec.drawJpg(x,y,chinchilla_2_25, sizeof(chinchilla_2_25));break;
      case 27: TJpgDec.drawJpg(x,y,chinchilla_2_26, sizeof(chinchilla_2_26));break;
      case 28: TJpgDec.drawJpg(x,y,chinchilla_2_27, sizeof(chinchilla_2_27));break;
      case 29: TJpgDec.drawJpg(x,y,chinchilla_2_28, sizeof(chinchilla_2_28));break;
      case 30: TJpgDec.drawJpg(x,y,chinchilla_2_29, sizeof(chinchilla_2_29));break;
      case 31: TJpgDec.drawJpg(x,y,chinchilla_2_30, sizeof(chinchilla_2_30));break;
      case 32: TJpgDec.drawJpg(x,y,chinchilla_2_31, sizeof(chinchilla_2_31));break;
      case 33: TJpgDec.drawJpg(x,y,chinchilla_2_32, sizeof(chinchilla_2_32));break;
      case 34: TJpgDec.drawJpg(x,y,chinchilla_2_33, sizeof(chinchilla_2_33));break;
      case 35: TJpgDec.drawJpg(x,y,chinchilla_2_34, sizeof(chinchilla_2_34));break;
      case 36: TJpgDec.drawJpg(x,y,chinchilla_2_35, sizeof(chinchilla_2_35));break;
      case 37: TJpgDec.drawJpg(x,y,chinchilla_2_36, sizeof(chinchilla_2_36));break;
      case 38: TJpgDec.drawJpg(x,y,chinchilla_2_37, sizeof(chinchilla_2_37));break;
      case 39: TJpgDec.drawJpg(x,y,chinchilla_2_38, sizeof(chinchilla_2_38));break;
      case 40: TJpgDec.drawJpg(x,y,chinchilla_2_39, sizeof(chinchilla_2_39));break;
      case 41: TJpgDec.drawJpg(x,y,chinchilla_2_40, sizeof(chinchilla_2_40));break;
      case 42: TJpgDec.drawJpg(x,y,chinchilla_2_41, sizeof(chinchilla_2_41));break;
      case 43: TJpgDec.drawJpg(x,y,chinchilla_2_42, sizeof(chinchilla_2_42));break;
      case 44: TJpgDec.drawJpg(x,y,chinchilla_2_43, sizeof(chinchilla_2_43));break;
      case 45: TJpgDec.drawJpg(x,y,chinchilla_2_44, sizeof(chinchilla_2_44));break;
      case 46: TJpgDec.drawJpg(x,y,chinchilla_2_45, sizeof(chinchilla_2_45));break;
      case 47: TJpgDec.drawJpg(x,y,chinchilla_2_46, sizeof(chinchilla_2_46));break;
      case 48: TJpgDec.drawJpg(x,y,chinchilla_2_47, sizeof(chinchilla_2_47));break;
      case 49: TJpgDec.drawJpg(x,y,chinchilla_2_48, sizeof(chinchilla_2_48));break;
      case 50: TJpgDec.drawJpg(x,y,chinchilla_2_49, sizeof(chinchilla_2_49));break;
      case 51: TJpgDec.drawJpg(x,y,chinchilla_2_50, sizeof(chinchilla_2_50));break;
      case 52: TJpgDec.drawJpg(x,y,chinchilla_2_51, sizeof(chinchilla_2_51));break;
      case 53: TJpgDec.drawJpg(x,y,chinchilla_2_52, sizeof(chinchilla_2_52));break;
      case 54: TJpgDec.drawJpg(x,y,chinchilla_2_53, sizeof(chinchilla_2_53));break;
      case 55: TJpgDec.drawJpg(x,y,chinchilla_2_54, sizeof(chinchilla_2_54));break;
      case 56: TJpgDec.drawJpg(x,y,chinchilla_2_55, sizeof(chinchilla_2_55));break;
      case 57: TJpgDec.drawJpg(x,y,chinchilla_2_56, sizeof(chinchilla_2_56));break;
      case 58: TJpgDec.drawJpg(x,y,chinchilla_2_57, sizeof(chinchilla_2_57));break;
      case 59: TJpgDec.drawJpg(x,y,chinchilla_2_58, sizeof(chinchilla_2_58));break;
      case 60: TJpgDec.drawJpg(x,y,chinchilla_2_59, sizeof(chinchilla_2_59));break;
      case 61: TJpgDec.drawJpg(x,y,chinchilla_2_60, sizeof(chinchilla_2_60));break;
      case 62: TJpgDec.drawJpg(x,y,chinchilla_2_61, sizeof(chinchilla_2_61));break;
      case 63: TJpgDec.drawJpg(x,y,chinchilla_2_62, sizeof(chinchilla_2_62));break;
      case 64: TJpgDec.drawJpg(x,y,chinchilla_2_63, sizeof(chinchilla_2_63));break;
      case 65: TJpgDec.drawJpg(x,y,chinchilla_2_64, sizeof(chinchilla_2_64));break;
      case 66: TJpgDec.drawJpg(x,y,chinchilla_2_65, sizeof(chinchilla_2_65));break;
      case 67: TJpgDec.drawJpg(x,y,chinchilla_2_66, sizeof(chinchilla_2_66));break;
      case 68: TJpgDec.drawJpg(x,y,chinchilla_2_67, sizeof(chinchilla_2_67));break;
      case 69: TJpgDec.drawJpg(x,y,chinchilla_2_68, sizeof(chinchilla_2_68));break;
      case 70: TJpgDec.drawJpg(x,y,chinchilla_2_69, sizeof(chinchilla_2_69));break;
      case 71: TJpgDec.drawJpg(x,y,chinchilla_2_70, sizeof(chinchilla_2_70));break;
      case 72: TJpgDec.drawJpg(x,y,chinchilla_2_71, sizeof(chinchilla_2_71));break;
      case 73: TJpgDec.drawJpg(x,y,chinchilla_2_72, sizeof(chinchilla_2_72));break;
      case 74: TJpgDec.drawJpg(x,y,chinchilla_2_73, sizeof(chinchilla_2_73));break;
      case 75: TJpgDec.drawJpg(x,y,chinchilla_2_74, sizeof(chinchilla_2_74));break;
      case 76: TJpgDec.drawJpg(x,y,chinchilla_2_75, sizeof(chinchilla_2_75));break;
      case 77: TJpgDec.drawJpg(x,y,chinchilla_2_76, sizeof(chinchilla_2_76));break;
      case 78: TJpgDec.drawJpg(x,y,chinchilla_2_77, sizeof(chinchilla_2_77));break;
      case 79: TJpgDec.drawJpg(x,y,chinchilla_2_78, sizeof(chinchilla_2_78));break;
      case 80: TJpgDec.drawJpg(x,y,chinchilla_2_79, sizeof(chinchilla_2_79));index=0;break;
    }
  }
  else if(mode == 3) { //动画-太空人
    switch(index) {
      case 1:  TJpgDec.drawJpg(x,y,Astronaut_1_0, sizeof(Astronaut_1_0));break;
      case 2:  TJpgDec.drawJpg(x,y,Astronaut_1_1, sizeof(Astronaut_1_1));break;
      case 3:  TJpgDec.drawJpg(x,y,Astronaut_1_2, sizeof(Astronaut_1_2));break;
      case 4:  TJpgDec.drawJpg(x,y,Astronaut_1_3, sizeof(Astronaut_1_3));break;
      case 5:  TJpgDec.drawJpg(x,y,Astronaut_1_4, sizeof(Astronaut_1_4));break;
      case 6:  TJpgDec.drawJpg(x,y,Astronaut_1_5, sizeof(Astronaut_1_5));break;
      case 7:  TJpgDec.drawJpg(x,y,Astronaut_1_6, sizeof(Astronaut_1_6));break;
      case 8:  TJpgDec.drawJpg(x,y,Astronaut_1_7, sizeof(Astronaut_1_7));break;
      case 9:  TJpgDec.drawJpg(x,y,Astronaut_1_8, sizeof(Astronaut_1_8));break;
      case 10: TJpgDec.drawJpg(x,y,Astronaut_1_9, sizeof(Astronaut_1_9));index=0;break;
    }
  }
  else{
    mode = 0;
    index = 0;
    time_old = 0;
  }
}

String scrollText[6];
//天气信息写到屏幕上
extern void tft_display_weather(String *cityDZ, String *dataSK, String *dataFC)
{

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, *dataSK);
  JsonObject sk = doc.as<JsonObject>();

  //TFT_eSprite clkb = TFT_eSprite(&tft);

  /***绘制相关文字***/
  clk.setColorDepth(8);
  clk.loadFont(ZdyLwFont_20);

  //温度
  clk.createSprite(52, 30);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["temp"].as<String>() + "℃", 26, 15);
  clk.pushSprite(184, 208);
  clk.deleteSprite();

  //城市名称
  clk.createSprite(84, 30);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["cityname"].as<String>(), 42, 15);
  clk.pushSprite(151, 1);
  clk.deleteSprite();

  //PM2.5空气指数
  uint16_t pm25TFT_WHITE = tft.color565(156, 202, 127); //优
  String aqiTxt = "优";
  int pm25V = sk["aqi"];
  if (pm25V > 200)
  {
    pm25TFT_WHITE = tft.color565(136, 11, 32); //重度
    aqiTxt = "重度";
  }
  else if (pm25V > 150)
  {
    pm25TFT_WHITE = tft.color565(186, 55, 121); //中度
    aqiTxt = "中度";
  }
  else if (pm25V > 100)
  {
    pm25TFT_WHITE = tft.color565(242, 159, 57); //轻
    aqiTxt = "轻度";
  }
  else if (pm25V > 50)
  {
    pm25TFT_WHITE = tft.color565(247, 219, 100); //良
    aqiTxt = "良";
  }
  clk.createSprite(50, 24);
  clk.fillSprite(TFT_WHITE);
  clk.fillRoundRect(0, 0, 50, 24, 4, pm25TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_WHITE);
  clk.drawString(aqiTxt, 25, 13);
  clk.pushSprite(5, 150);
  clk.deleteSprite();

  //湿度
  clk.createSprite(56, 24);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["SD"].as<String>(), 28, 13);
  //clk.drawString("100%",28,13);
  clk.pushSprite(185, 150);
  clk.deleteSprite();

  scrollText[0] = "实时天气 " + sk["weather"].as<String>();
  scrollText[1] = "空气质量 " + aqiTxt;
  scrollText[2] = "风向 " + sk["WD"].as<String>() + sk["WS"].as<String>();

  //左上角滚动字幕
  //解析第二段JSON
  deserializeJson(doc, *cityDZ);
  JsonObject dz = doc.as<JsonObject>();
  //Serial.println(sk["ws"].as<String>());
  //横向滚动方式
  //String aa = "今日天气:" + dz["weather"].as<String>() + "，温度:最低" + dz["tempn"].as<String>() + "，最高" + dz["temp"].as<String>() + " 空气质量:" + aqiTxt + "，风向:" + dz["wd"].as<String>() + dz["ws"].as<String>();
  //scrollTextWidth = clk.textWidth(scrollText);
  //Serial.println(aa);
  scrollText[3] = "今日" + dz["weather"].as<String>();

  deserializeJson(doc, *dataFC);
  JsonObject fc = doc.as<JsonObject>();

  scrollText[4] = "最低温度" + fc["fd"].as<String>() + "℃";
  scrollText[5] = "最高温度" + fc["fc"].as<String>() + "℃";

  //Serial.println(scrollText[0]);

  clk.unloadFont();
}

int currentIndex = 0;
int prevTime = 0;
TFT_eSprite clkb = TFT_eSprite(&tft);

static void scrollTxt(int pos)
{
  clkb.createSprite(148, 24);
  clkb.fillSprite(TFT_WHITE);
  clkb.setTextWrap(false);
  clkb.setTextDatum(CC_DATUM);
  clkb.setTextColor(TFT_BLACK, TFT_WHITE);
  clkb.drawString(scrollText[currentIndex], 74, pos + 12);
  clkb.pushSprite(2, 4);
}

extern void tft_display_banner(void)
{
  if (scrollText[currentIndex])
  {
    clkb.setColorDepth(8);
    clkb.loadFont(ZdyLwFont_20);

    for (int pos = 24; pos > 0; pos--)
    {
      scrollTxt(pos);
    }

    clkb.deleteSprite();
    clkb.unloadFont();

    if (currentIndex >= 5)
    {
      currentIndex = 0; //回第一个
    }
    else
    {
      currentIndex += 1; //准备切换到下一个
    }
  }
}
