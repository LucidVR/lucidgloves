//only compiles if BTSerial is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_WIFISERIAL
#include <WiFi.h>
#include <WebSocketsClient.h>

WebSocketsClient webSocket;

class WifiSerialCommunication : public ICommunication {
  private:
    bool m_isOpen;
    int counter;


  public:
    WifiSerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen() {
      return m_isOpen;
    }

    void start() {
      Serial.begin(115200);
      WiFi.begin(WIFISERIAL_SSID, WIFISERIAL_PASSWORD);

      for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
      }

      if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Couln't connect to the wifi, check your settings.");
        return;
      }

      Serial.println("Connected to the wifi.");

      webSocket.begin(WIFISERIAL_SERVER, WIFISERIAL_SERVER_PORT);
      webSocket.onEvent([](WStype_t type, uint8_t * payload, size_t length) {
        Serial.println("OnEvent");
        switch (type) {
          case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
          case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n", payload);

            // send message to server when Connected
            webSocket.sendTXT("Connected");
            break;
          case WStype_TEXT:
            Serial.printf("[WSc] get text: \n%s", payload);

            // send message to server
            // webSocket.sendTXT("message here");
            break;
          case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
          case WStype_ERROR:
          case WStype_FRAGMENT_TEXT_START:
          case WStype_FRAGMENT_BIN_START:
          case WStype_FRAGMENT:
          case WStype_FRAGMENT_FIN:
            break;
        }

      });

      Serial.println("Trying to connect to server...");
      m_isOpen = true;
      webSocket.setReconnectInterval(5000);
    }

    void output(char* data) {
      Serial.println(data);
      char cstr[16];
      char buf[100];
      itoa(counter, cstr, 10);
      strcpy(buf,cstr);
      strcpy(buf," ");
      strcpy(buf,data);
      webSocket.sendTXT(buf);
      counter++;
    }

    void loop() {
      webSocket.loop();
    }
};

#endif
