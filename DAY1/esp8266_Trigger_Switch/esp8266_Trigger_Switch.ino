#define button 16
int CheckButton;
void setup()
{
Serial.begin(9600);
pinMode(button ,INPUT_PULLUP);
}
void loop()
{
bool ReadSwitch = digitalRead(button);
if (CheckButton != ReadSwitch)
{
if(ReadSwitch == 0)
{
Serial.println("Pressed Switch.");
}
CheckButton = ReadSwitch;
delay(100);
}
}
