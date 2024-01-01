#define BLYNK_TEMPLATE_ID "TMPLnS9PXJ5Y"
#define BLYNK_DEVICE_NAME "4ledzaza"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#incint led1 = 5;
#incint led2 = 4;
#incint led3 = 0;
#incint led4 = 2;
BLYNK_WRITE(V0) {
  int pinvalue = param.asInt();
  digitalWrite(led1,pinvalue);
}
BLYNK_WRITE(V1) {
  int pinvalue = param.asInt();
  digitalWrite(led2,pinvalue);
}
BLYNK_WRITE(V2) {
  int pinvalue = param.asInt();
  digitalWrite(led3,pinvalue);
}
BLYNK_WRITE(V3) {
  int pinvalue = param.asInt();
  digitalWrite(led4,pinvalue);
}
void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
