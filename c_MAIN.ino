WiFiClient client;
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

//PinButton btnM5(39);
PinButton btnAction(39);

char currentState = -1;
bool connectedTovMix = false;

char deviceName[32];
int status = WL_IDLE_STATUS;
bool apEnabled = false;
boolean started = false;

// Time measure
int interval = 5000;
unsigned long lastCheck = 0;

void setup()
{
  uint8_t c;
  Serial.begin(115200);
  M5.begin();
  
  matrix.begin();
  delay(10);
  matrix.setBrightness(20); // Jasność max
  
  loadSettings();
  
  Serial.print("SSID: ");
  Serial.println(&(WIFI_SSID[0]));
  Serial.print("PASS: ");
  Serial.println(&(WIFI_PASS[0]));
}

void loop()
{
  server.handleClient();
  matrix.clear();
 
  if(!started){
    started = true;
    start();
  }
  
  btnAction.update();
 
  if (btnAction.isDoubleClick()) {
        connectTovMix(false);
  }

  
  if(btnAction.isLongClick()){
    if(!client.connected()){
       resetSettings();
    } else {
      Serial.println("No need to reset");
      Serial.println("You're connected");
      delay(3000);
    }
  }
  
  while (client.available())
  {
    server.handleClient();
    String data = client.readStringUntil('\r\n');
    handleData(data);
  }
  
  if (!client.connected() && !apEnabled && millis() > lastCheck + interval)
  {
    client.stop();
    lastCheck = millis();
    noConnectionTovMix();
  }

  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Reconnect WiFi");
    WiFi.reconnect();
  }

  matrix.setTextColor(matrix.Color(0,0,255));
  matrix.setTextWrap(false);
  matrix.setCursor(0,0);
  matrix.fillScreen(0);

}

void start()
{
  loadSettings();
  Serial.println(""); 
  Serial.println("vMix M5 ATOM Tally");
  Serial.println("by AW");  
  Serial.println("");

  matrix.fillScreen(green);
  matrix.show(); 
  matrix.show();
  delay(1000);
  matrix.fillScreen(red);
  matrix.show(); 
  matrix.show();
  delay(1000);
  matrix.fillScreen(blue);
  matrix.show(); 
  matrix.show();
  delay(1000);
  matrix.fillScreen(black);
  matrix.show(); 
  matrix.show();
  delay(1000);

  delay(2000);

  startWiFi();
}
