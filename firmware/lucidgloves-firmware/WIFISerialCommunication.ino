//only compiles if WIFISerial is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_WIFISERIAL
#include <WiFi.h>
#include <HTTPClient.h>

class WIFISerialCommunication : public ICommunication {

private:
  bool m_isOpen;
  WiFiClient client;

  void connect() {
    while (!client.connect(host, port)) //blocks thread until connected
      delay(500);
    Serial.print("Connected to Server at" + String(client.localIP()) + ":" + String(client.localPort()));
  }

public:
  WIFISerialCommunication() {
    m_isOpen = false;
  }

  bool isOpen() {
    return m_isOpen;
  }

  void start() {
    Serial.begin(SERIAL_BAUD_RATE);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    m_isOpen = true;
    Serial.println("Connected to WiFi");

    connect();
    
  }
  void output(char* data) {
    if (!client.connected()) {
      Serial.println("Client not connected, attempting reconnect");
      connect();
    }
    client.println(data);
    #endif
  }

  bool readData(char* input) {
    if (!client.connected()) {
      Serial.println("Client not connected, attempting reconnect");
      connect();
    }
    String message = client.readStringUntil('\n');
  //  String message = client.readStringUntil('\n', input, 100);
    //input[size] = NULL;
    strcpy(input, message.c_str());
    
    return input != NULL && strlen(input) > 0;
  }
};
#endif
