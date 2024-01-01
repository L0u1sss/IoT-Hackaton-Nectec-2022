#define led2 19
#define led3 18
#define led4 5
#define sw3 16 //คุมi
#define sw2 17 //คุมj
int checksw3;
int checksw2;
int i=0; //คุมโดยswitch3
int j=0; //คุมโดยswitch2
void setup() {
Serial.begin(9600);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(sw3, INPUT_PULLUP);
pinMode(sw2, INPUT_PULLUP);
digitalWrite(led2, 1);
digitalWrite(led3, 1);
digitalWrite(led4, 1);
}

void loop() {
bool readsw3 = digitalRead(sw3);
bool readsw2 = digitalRead(sw2);
//ทำswitch3
if ( checksw3 != readsw3 ){
if (readsw3 == 0){
i++;
}
checksw3 = readsw3;
}
//ทำswitch2
if ( checksw2 != readsw2 ){
if (readsw2 == 0){
j++;
}
checksw2 = readsw2;
}
if (j==1){
  digitalWrite(led2 , 0);
}
else if (j==2){
  digitalWrite(led2 , 1);
}
else if (j==3){
  j=1;
}
else if (i==1){
digitalWrite(led3 ,0);
}
else if (i == 2){
digitalWrite(led3, 1);

}
else if (i == 3){
digitalWrite(led4, 0);
}
else if (i == 4){
digitalWrite(led4, 1);
}
else if (i == 5){
digitalWrite(led3, 0);
digitalWrite(led4, 0);
}
else if (i == 6){
digitalWrite(led3, 1);
digitalWrite(led4, 1);

}
else if (i == 7){
i=1;
}
}
