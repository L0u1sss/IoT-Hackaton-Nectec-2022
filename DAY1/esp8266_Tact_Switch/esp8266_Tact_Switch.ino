#define button 16
void setup()
{
Serial.begin(9600);
pinMode(button ,INPUT_PULLUP);
}

void loop()
{
bool ReadSwitch = digitalRead(button);
if(ReadSwitch == 0)
{
Serial.println("Pressed Switch.");
}
}
