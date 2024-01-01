void setup()
{
Serial.begin(9600);
}
void loop()
{
for (int i = 0; i < 2; i++){
Serial.print("Hello World 1");
delay(1000);
}
for (int i = 0; i < 3; i++){
Serial.println("Hello World 2");
delay(1000);
}
}
