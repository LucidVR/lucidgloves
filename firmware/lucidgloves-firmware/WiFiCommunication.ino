//only compiles if WiFi is set because it won't compile for a non-compatible board
#if COMMUNICATION == COMM_WIFI
#include <WiFi.h>

#define WIFI_READ_BUFFER_LEN 100
class WiFiCommunication : public ICommunication {
  private:
    bool m_isOpen;
    WiFiServer m_server{WIFI_PORT};
    WiFiClient m_client;
    char m_buffer[WIFI_READ_BUFFER_LEN];
    int m_buffer_pos = 0;
    
  public:
    WiFiCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      Serial.begin(115200);
      WiFi.mode(WIFI_STA);
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi connection failed!\n");
        return;
      }
       else {
        Serial.print("Your board has been assigned IP address: ");
        Serial.println(WiFi.localIP());
        m_isOpen = true;
       }
       m_server.begin();
    }

    void output(char* data){
      if(!m_client || !m_client.connected()) {
        m_client = m_server.available();

        if(m_client) {
          Serial.println("TCP client connected!");
        }
      }
      
      if(!m_client) {
        // No client connected, nothing to do.
        return;
      }
      
      // m_client.write(data);
    }

    bool readData(char* input){
      if(!m_client) {
        // No client connected, nothing to read.
        return false;
      }

      while(m_client.available() > 0) {
        m_buffer[m_buffer_pos] = m_client.read();
        if(m_buffer[m_buffer_pos] == '\n') {
          m_buffer[m_buffer_pos] = NULL;
          strcpy(input, m_buffer);
          m_buffer_pos = 0;
          // Serial.println("Received text from client:");
          // Serial.println(input);
          return true;
        }
        ++m_buffer_pos;
        if(m_buffer_pos >= WIFI_READ_BUFFER_LEN) {
          m_buffer_pos = 0;
        }
      }
      return false;
    }
};
#endif
