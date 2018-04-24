  //initialize variables
  int n = 0;
  float tempAvg[5];
  float prevVolts =0;
  float activeVolts;
  
void setup() {
  //const float referenceVolts = 5.0; 
  const int batteryPin = 0;
  Serial.begin(9600);      // initialize serial communications with your computer
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
  float volts;
  float tempAvg[5];
  float prevVolts =0;
  float activeVolts;
}

void loop() {
  
  Serial.println();
  float rawVoltage = analogRead(A5); //Read voltage
  float tempF = rawVoltage / 1024 * 5000; //converts the voltage to temperature
  tempF /= 10; //convert millivolts
  
  if (n < 5){ //add to the array 
    tempAvg[n] = tempF;
    n += 1;
    delay(250);
  }
  if (n == 5){
    n = 0;
    tempF = tempAvg[0] + tempAvg[1] + tempAvg[2] + tempAvg[3] + tempAvg[4]; //add all the values in array
    tempF /= 5; //divide by 5 to get the average
    Serial.print(tempF); //print out the average to get an accurate temperature after 1.2 seconds
    Serial.println(" degrees Fahrenheit.");

    if (tempF > 122.0) //checks if temperature is higher than 122 fahrenheit
    {
      digitalWrite(12,LOW);
      Serial.println("Relay Off"); //turn off clipper motor
    }
    else
    {
      digitalWrite(12,HIGH);
      Serial.println("Relay On"); //keep clipper motor on
   }
   
   int val = analogRead(A0); // read the value from the sensor 
   Serial.print("Battery Voltage = ");
   float volts = (2 * (val / 1023.0) * 5) - 0.2; // calculate the ratio 
   
   if (prevVolts <= volts){ // prevVolts = 0 at first so should be high
    digitalWrite(5,HIGH);
    Serial.println("Relay ON");
    Serial.println(volts); // print the value in volts
    delay(1000);
    float prevVolts = volts; // holds previous value to reference
   }
   else { //if voltage is charging then turn relay off
    digitalWrite(5,LOW);
    Serial.println("Relay Off");
    Serial.println(volts); // print the value in volts
    delay(1000);
    float prevVolts = volts;  //holds previous value to reference
   }
   
  }
}

