const bool USING_JOYSTICK = false;  //configure if you're using joystick
const bool FLIP_X = false;          //flip x axis joystick
const bool FLIP_Y = false;          //flip x axis joystick
const int calibrationLoops = 20000;
const int loopTime = 0;
int sensorValue = 0;
String commandFromPC = "";
int loops = 0;
int maxFingers[5] = {0,0,0,0,0};
int minFingers[5] = {1023,1023,1023,1023};

int calib[5] = {500,500,500,500,500};

int xFlip = FLIP_X?-1:1;
int yFlip = FLIP_Y?-1:1;

void setup() {
  // put your setup code here, to run once:
  /*for (int b = 0; b < 5; b++)
        minFingers[b] = 1023;
  for (int c = 0; c < 5; c++)
        maxFingers[c] = 0;*/
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(loopTime);
  {
      int theseFingers[5] = {1023-analogRead(A4), 1023-analogRead(A3), 1023-analogRead(A2), 1023-analogRead(A1), 1023-analogRead(A0)};
      int joyX = analogRead(A5);
      int joyY = analogRead(A6);
      int joyClick = digitalRead(2);

      if (joyClick == HIGH){
        joyClick = 1;
      }

      //If still in calibration time, run calibration
      for (int i = 0; i < 5; i++){
        if (loops < calibrationLoops){
          if (theseFingers[i] > maxFingers[i])
            maxFingers[i] = theseFingers[i];
          if (theseFingers[i] < minFingers[i])
            minFingers[i] = theseFingers[i];
          loops++;
        }
        if (minFingers[i] != maxFingers[i]){
          calib[i] = (int)((float)(theseFingers[i] - minFingers[i]) / (float)(maxFingers[i] - minFingers[i]) * 1023.0f);
        }
      }
      char stringToPrint[75];
      bool grabbing = (calib[0] + calib[1] + calib[2] + calib[3]) / 4 <= 1023/2 ? 0:1;
      //                       fingers        joystick  buttons  gestures
      sprintf(stringToPrint, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
      calib[0], calib[1], calib[2], calib[3], calib[4], USING_JOYSTICK?joyX*xFlip:1023/2, USING_JOYSTICK?joyY*yFlip:1023/2, 1 - joyClick, calib[1]<=(1023/2)?0:1, 0, 0, grabbing, 0);
      Serial.print(stringToPrint);
      Serial.flush();
  }
}
