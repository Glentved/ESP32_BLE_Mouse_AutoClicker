#include <EEPROM.h>
#include <BleMouse.h>

BleMouse bleMouse;

int interval_time;

bool setup_complete = false;
unsigned long starttime, endtime;

void setup() {
  EEPROM.begin(16);
  delay(500);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  interval_time = EEPROM.readInt(2); //read saved click interval
  if (interval_time < 200) { // if first time programmed, set clickspeed to 500
    interval_time = 500;
  }
  setup_Webserver();

  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <= 15000) // ACTIVATE WIFI
  {
    Webserver_loop();
    endtime = millis();
    delay(1);
    click_mouse();
  }
  digitalWrite(LED_BUILTIN, LOW);
  webserver_stop();  //stop wifi
  
  delay(100);
  setup_complete = true;
  bleMouse.begin();  // start Bluetooth
}

void loop() {  //run on core 1
  if (bleMouse.isConnected()) {
    click_mouse();
  }
}

void click_mouse() {

  //This is basically blink without delay 
  
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  if (currentMillis - previousMillis >= interval_time) {
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //toggle led
    if (setup_complete == true) {   //only use bluetooth if setup via WiFi is complete
      bleMouse.click(MOUSE_LEFT);
      Serial.println("click with mouse");
    }
    else {
      Serial.println("Blink led, without mouse click");
    }
  }
}
