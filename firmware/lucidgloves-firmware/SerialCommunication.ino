class SerialCommunication : public ICommunication {
  private:
    bool m_isOpen;

  public:
    SerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      Serial.begin(SERIAL_BAUD_RATE);
      m_isOpen = true;
    }

    void output(char* data){
      Serial.print(data);
      Serial.flush();
    }
};
