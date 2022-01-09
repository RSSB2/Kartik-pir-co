//message format @message*
int a;
float b;
int temp=0,i=0;

char str[15];

const int PIRsensor = 2; // PIR sensor pin
const int Relay1  = 3; // Relay1 pin
const int Relay2  = 4; // Relay2 pin

int PIRSensorState; // the current state of sensor

void setup() 
{
  pinMode(PIRsensor, INPUT); // set arduino pin to input
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("ATE0");
  delay(500);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1"); 
  delay(2000);
}

void loop()
{
    PIRSensorState = digitalRead(PIRsensor); 
    if(PIRSensorState == HIGH)
    {
     digitalWrite(LED_BUILTIN, HIGH);
     Serial.println("AT+CMGF=1"); 
     delay(200);
     Serial.println("AT+CMGS=\"8802313594\"\r"); //phone number
     delay(200);
     Serial.println("Intruder Person Detected"); //type message
     delay(200);
     Serial.write(26); 
     delay(3000);
     digitalWrite(LED_BUILTIN, LOW);
    }
    
     //check for serial data
    while(Serial.available()) 
    {
    if(Serial.find("@"))//begin
    {
    delay(1000);
    while (Serial.available()) 
    {
    char inChar=Serial.read();
    str[i++]=inChar;
    if(inChar=='*')//terminator
    {
    temp=1;    
    return;
    } 
    } 
    }
    }

    if(temp==1)
    {
    check();
    temp=0;
    i=0;
    }
}

void check()
{
  if(!(strncmp(str,"ON1",3))) //Relay1 ON
  {
  digitalWrite(Relay1, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("AT+CMGF=1"); 
  delay(200);
  Serial.println("AT+CMGS=\"8802313594\"\r"); 
  delay(200);
  Serial.println("Load-1 'ON'"); //type message
  delay(200);
  Serial.write(26); 
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  } 

  if(!(strncmp(str,"ON2",3))) //Relay2 ON
  {
  digitalWrite(Relay2, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("AT+CMGF=1"); 
  delay(200);
  Serial.println("AT+CMGS=\"8802313594\"\r"); //phone number
  delay(200);
  Serial.println("Load-2 'ON'"); //type message
  delay(200);
  Serial.write(26); 
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  }

  if(!(strncmp(str,"OFF1",4))) //Relay1 OFF
  {
  digitalWrite(Relay1, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("AT+CMGF=1"); 
  delay(200);
  Serial.println("AT+CMGS=\"8802313594\"\r"); //phone number
  delay(200);
  Serial.println("Load-1 'OFF'"); //type message
  delay(200);
  Serial.write(26); 
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  }

  if(!(strncmp(str,"OFF2",4))) //Relay2 OFF
  {
  digitalWrite(Relay2, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("AT+CMGF=1"); 
  delay(200);
  Serial.println("AT+CMGS=\"8802313594\"\r"); //phone number
  delay(200);
  Serial.println("Load-2 'OFF'"); //type message
  delay(200);
  Serial.write(26); 
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  }
   
} 
 
   

  
