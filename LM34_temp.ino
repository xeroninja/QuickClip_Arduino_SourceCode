  int n = 0;
  float tempAvg[5];

void setup() {
  const float referenceVolts =5.0;
  const int batteryPin = 0;
  Serial.begin(9600);      // initialize serial communications with your computer
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
  float volts;
  float tempAvg[5];

}

void loop() {
  // read the temperature sensor in Celsius, then Fahrenheit:
  //int celsius = Esplora.readTemperature(DEGREES_C);
  //int fahrenheit = Esplora.readTemperature(DEGREES_F);

  // print the results:
  //Serial.print("Temperature is: ");
  //Serial.print(celsius);
  //Serial.print(" degrees Celsius, or ");
  //Serial.print(fahrenheit);
  //Serial.println(" degrees Fahrenheit.");
  //Serial.println("     Fahrenheit = (9/5 * Celsius) + 32");
  //int val = analogRead();// wait a second before reading again:

  Serial.println();
  float rawVoltage = analogRead(A5);
  float tempF = rawVoltage / 1024 * 5000;
  tempF /= 10;
  if (n < 5){
    tempAvg[n] = tempF;
    n += 1;
    delay(250);
  }
  if (n == 5){
    n = 0;
    tempF = tempAvg[0] + tempAvg[1] + tempAvg[2] + tempAvg[3] + tempAvg[4];
    tempF /= 5;
    Serial.print(tempF);
    Serial.println(" degrees Fahrenheit.");

    if (tempF > 122.0)
    {
      digitalWrite(12,LOW);
      Serial.println("Relay Off");
    }
    else
    {
      digitalWrite(12,HIGH);
      Serial.println("Relay On");
   }
    int val = analogRead(A0); // read the value from the sensor 
   Serial.print("Battery Voltage = ");
   float volts = (2 * (val / 1023.0) * 5) - 0.2; // calculate the ratio 
   Serial.println(volts); // print the value in volts
  }
}

