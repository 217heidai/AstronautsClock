# AstronautsClock
基于 ESP8266 及 1.3 寸 TFT 实现的华为太空人时钟。参考了 d88880(抖音号) 的简易太空人时钟代码。

## 展示
![AstronautsClock](https://ghproxy.com/https://raw.githubusercontent.com/217heidai/AstronautsClock/main/doc/AstronautsClock.jpeg)

## 功能
1. 时间、日期、星期，每 1 小时校准一次
2. 实时天气信息：天气、温度、湿度、空气质量，每半小时刷新一次
3. 整点蜂鸣报时
4. 整点更换 gif（龙猫跳绳、龙猫跳舞、太空人）

## 材料清单
1. ESP8266 开发板
2. 中景园 1.3 寸 TFT，分辨率 240 x 240
3. 蜂鸣器
4. 微积木

## 电路图
![tft](https://ghproxy.com/https://raw.githubusercontent.com/217heidai/AstronautsClock/main/doc/TFT.png)

## 代码编译说明
### 依赖库
1. ArduinoJson
2. TimeLib
3. TFT_eSPI
4. TJpg_Decoder
5. Buzzer

### 配置修改
1. 修改 TFT_eSPI 库管脚定义，参考 [User_Setup.h.backup](https://ghproxy.com/https://raw.githubusercontent.com/217heidai/AstronautsClock/main/src/User_Setup.h.backup)：
```C
#define TFT_MISO 14
#define TFT_MOSI 13
#define TFT_CS   -1  // Chip select control pin D8
#define TFT_DC    5  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to NodeMCU RST, see next line)
#define TFT_BL   -1  // LED back-light (only for ST7789 with backlight control pin)
```
2. `CLOCK.ino`中修改 WiFi 信息，设置 `ssid`、`password`
3. `CLOCK.ino`中修改天气城市代码，设置 `cityCode`
