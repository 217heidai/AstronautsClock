//初始化屏幕
extern bool tft_init(void)
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
  clk.fillSprite(0x0000);

  clk.drawRoundRect(0, 0, 200, 16, 8, 0xFFFF);
  clk.fillRoundRect(3, 3, loadNum, 10, 5, 0xFFFF);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_GREEN, 0x0000);
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
  TJpgDec.drawJpg(0, 0, watchtop, sizeof(watchtop));

  //绘制底部视图
  TJpgDec.drawJpg(0, 220, watchbottom, sizeof(watchbottom));

  //绘制中间显示窗口
  tft.setViewport(0, 20, 240, 200);
  tft.fillScreen(0x0000);
  tft.fillRoundRect(0, 0, 240, 200, 5, TFT_WHITE); //实心圆角矩形

  //在窗口内绘制线框
  tft.drawFastHLine(0, 34, 240, TFT_BLACK);
  tft.drawFastVLine(150, 0, 34, TFT_BLACK);
  tft.drawFastHLine(0, 166, 240, TFT_BLACK);
  tft.drawFastVLine(60, 166, 34, TFT_BLACK);
  tft.drawFastVLine(160, 166, 34, TFT_BLACK);

  //在窗口内绘制图标
  TJpgDec.drawJpg(159, 130, humidity, sizeof(humidity));       //湿度图标
  TJpgDec.drawJpg(161, 171, temperature, sizeof(temperature)); //温度图标
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
    clk.createSprite(58, 32);
    clk.fillSprite(TFT_WHITE);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(week_now, 29, 16);
    clk.pushSprite(1, 168);
    clk.deleteSprite();
  }
  //月日
  if(monthDay_now != monthDay_old)
  {
    monthDay_old = monthDay_now;
    clk.createSprite(98, 32);
    clk.fillSprite(TFT_WHITE);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_BLACK, TFT_WHITE);
    clk.drawString(monthDay_now, 49, 16);
    clk.pushSprite(61, 168);
    clk.deleteSprite();
  }
  clk.unloadFont();
}

//刷新太空人图片
void tft_display_spaceman(void)
{
  int x = 80, y = 94, dt = 30; //瘦子版dt=10毫秒 胖子30较为合适

  TJpgDec.drawJpg(x, y, i0, sizeof(i0));
  delay(dt);
  TJpgDec.drawJpg(x, y, i1, sizeof(i1));
  delay(dt);
  TJpgDec.drawJpg(x, y, i2, sizeof(i2));
  delay(dt);
  TJpgDec.drawJpg(x, y, i3, sizeof(i3));
  delay(dt);
  TJpgDec.drawJpg(x, y, i4, sizeof(i4));
  delay(dt);
  TJpgDec.drawJpg(x, y, i5, sizeof(i5));
  delay(dt);
  TJpgDec.drawJpg(x, y, i6, sizeof(i6));
  delay(dt);
  TJpgDec.drawJpg(x, y, i7, sizeof(i7));
  delay(dt);
  TJpgDec.drawJpg(x, y, i8, sizeof(i8));
  delay(dt);
  TJpgDec.drawJpg(x, y, i9, sizeof(i9));
  delay(dt);
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
  clk.createSprite(54, 32);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["temp"].as<String>() + "℃", 27, 16);
  clk.pushSprite(185, 168);
  clk.deleteSprite();

  //城市名称
  clk.createSprite(88, 32);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["cityname"].as<String>(), 44, 16);
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
  clk.setTextColor(0xFFFF);
  clk.drawString(aqiTxt, 25, 13);
  clk.pushSprite(5, 130);
  clk.deleteSprite();

  //湿度
  clk.createSprite(56, 24);
  clk.fillSprite(TFT_WHITE);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_BLACK, TFT_WHITE);
  clk.drawString(sk["SD"].as<String>(), 28, 13);
  //clk.drawString("100%",28,13);
  clk.pushSprite(180, 130);
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
