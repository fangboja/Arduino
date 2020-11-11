/*voltage sensor*/
int analogInput = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int value = 0;
/*Acs712 sensor*/
const int ACS = A1;
int mVperAmp =100; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double current = 0;
double avgAmps=0;
/*time*/
int a=0;
/*Relay*/
int Relay1pin=3;
int Relay2pin=4;
/***************************************/
void setup() {
Serial.begin(9600);
pinMode(0, INPUT);
pinMode(Relay1pin,OUTPUT);
pinMode(Relay2pin,OUTPUT);
Serial.println("CLEARDATA"); //clears up any data left from previous projects

Serial.println("LABEL,Time,Voltage,Current"); //always write LABEL, so excel knows the next things will be the names of the columns (instead of Acolumn you could write Time for instance)
Serial.println("RESETTIMER"); //resets timer to 0
}
/***************************************/
void loop() {
/*Volge srensor*/
float sumVolts=0;
for (int i=0; i<100; i++) {
value = analogRead(0);
vout = (value * 4.98) / 1024.0; // see text
vin = vout / (R2/(R1+R2));
sumVolts += vin;
}
float avgVolts = sumVolts/100;
/*Acs712 average*/
float sumAmps=0;
for (int j=0; j<100; j++) {
int RawValue = analogRead(1);
float Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
float current = ((Voltage - ACSoffset) / mVperAmp);
sumAmps += current;
 }
float avgAmps = sumAmps/100;

/*Relay*/
if(avgVolts<0.7)
{
digitalWrite(Relay1pin,HIGH);/*1路開*/
digitalWrite(Relay2pin,LOW);/*2路關*/
}
if(avgVolts>5.4)
{
digitalWrite(Relay1pin,LOW);/*1路關*/
digitalWrite(Relay2pin,HIGH);/*2路開*/
}
/*PLX-DAQ2*/
Serial.print("DATA");
Serial.print(",");
Serial.print(a);
Serial.print(",");
Serial.print(avgVolts,2);
Serial.print(",");
Serial.print(avgAmps,2);
Serial.println("");
/*延遲5秒*/
a=a+5;
delay(5000);
}
