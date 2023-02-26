void startWiFi()
{
    Serial.println("STARTING WIFI THINGY");
    WiFi.mode(WIFI_STA);
    WiFi.begin(&(WIFI_SSID[0]), &(WIFI_PASS[0]));

    Serial.println("Waiting for WiFi...");

      matrix.fillScreen(black);
      matrix.show();
      matrix.show();

    int tries = 0;
    boolean wifi_connected = true;

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);   
        matrix.fillScreen(yellow);
        matrix.show();
        matrix.show();
      
        tries++;
        if (tries > 5)
        {
            tries = 0;
            Serial.println("Wifi connection failed, start local wifi");
            wifi_connected = false;
            break;
        }
    }

    if (wifi_connected == false)
    {
        startLocalWiFi();
    }
    else
    {
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.print(WiFi.localIP());
        Serial.println("");
        startServer();
        connectTovMix(false);
    }
}

// This starts the M5Stack as a WiFi Access Point so you can configure it
void startLocalWiFi()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP("M5-ATOM-Tally", "12345678");
    apEnabled = true;
    delay(100);
    startServer();
      
      matrix.fillScreen(magenta);
      matrix.show();
      matrix.show();
}
