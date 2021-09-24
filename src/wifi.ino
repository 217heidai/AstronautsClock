//连接wifi
extern bool wifi_connect(void)
{
  Serial.printf("\n\nConnecting to WiFi[%s]...\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    for (byte n = 0; n < 10; n++)
    {
      tft_display_loading(50); //每50毫秒检测一次，刷新一次进度条
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    return false;
  }

  Serial.printf("Connected to WiFi[%s], IP:", ssid);
  Serial.println(WiFi.localIP());

  return true;
}
