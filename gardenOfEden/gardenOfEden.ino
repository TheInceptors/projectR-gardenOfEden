/*
  Garden Of Eden IoT Project with 4 Resistivity Levels
 */
 
int pinOut13 = 13;
int pinOut12 = 12;
int pinOut8 = 8;
int pinOut7 = 7;
int pinOut4 = 4;
int pinInA0 = A0;
int valueInA0 = 0;

void setup() {                
  Serial.begin(9600);
  
  pinMode(pinOut13, OUTPUT);                    // Setting Pin 13 as output
  pinMode(pinOut12, OUTPUT);                    // Setting Pin 12 as output
  pinMode(pinOut8, OUTPUT);                     // Setting Pin 12 as output
  pinMode(pinOut4, OUTPUT);
  pinMode(pinOut7, OUTPUT);                     // Setting Pin 12 as output
  pinMode(pinInA0, INPUT);                      // Setting analog pin A0 to input
    
}

void loop() {
  
  digitalWrite(pinOut13, HIGH);                  // Setting Pin 13 On
  delay(1000);                                   // Stabilizer delay
  valueInA0 = analogRead(pinInA0);               // Sensing voltage input in pin A0 and converting to integer values (0 - 1023)
  
      Serial.print(valueInA0);                   // Sensing the integer equivalent of voltage sensed 
      Serial.print("\n");
      Serial.print(valueInA0 * 5.0/1023.0);      // Converting integer to voltage
      Serial.print("\n");

/* Hydration Settings & Resolution

0.00V - 1.25V = 255   | Hydration is IN HIGH LEVEL    | 4  
1.25V - 2.50V = 510   | Hydration is IN GOOD LEVEL    | 3    
2.50V - 3.75V = 765   | Hydration is IN WARNING LEVEL | 2  
3.75V - 5.00V = 1023  | Hydration is IN DANGER LEVEL  | 1  

*/    
  
  if (valueInA0 < 255) {                                               
       digitalWrite(pinOut12, HIGH);             // HIGH LEVEL @ PIN 12
       digitalWrite(pinOut8, LOW);
       digitalWrite(pinOut7, LOW);
       digitalWrite(pinOut4, LOW);
  }

  else if (valueInA0 >=255 and valueInA0 <=510) {  
       digitalWrite(pinOut4, HIGH);              // NORMAL LEVEL @ PIN 4
       digitalWrite(pinOut7, LOW);
       digitalWrite(pinOut8, LOW);
       digitalWrite(pinOut12, LOW);
  }
  
  else if (valueInA0 >=510 and valueInA0 <=765) {
       digitalWrite(pinOut7, HIGH);              // WARNING LEVEL @ PIN 7
       digitalWrite(pinOut8, LOW);
       digitalWrite(pinOut12, LOW);
       digitalWrite(pinOut4, LOW);
  }
  
  else if (valueInA0 > 765) {                    
       digitalWrite(pinOut8, HIGH);              // DANGER LEVEL @ PIN 8
       digitalWrite(pinOut12, LOW);
       digitalWrite(pinOut7, LOW);
       digitalWrite(pinOut4, LOW);      
  }  
  
  
/* Notes on testing the system
    1. If the soil sensor legs are shorted (just connect them by wires), then it means the hydration is excellent as it 
    represents presence of water at 100% conductivity. PIN 12 LED must light and signals conductivity at HIGH LEVEL.
    2. If the soil sensor is open (just remove the wires between them), then it means, there is no conductivity in between and
    represents that the soil is extremely dry. PIN 8 LED must light and signals conductivity at DANGER LEVEL.
    3. Assemble a group of resistors that will yield 17k Ohm and connect it in between the legs of the sensor soil. Check the
    console for the integer and voltage reading/value. PIN 4 LED must light and signals conductivity at NORMAL LEVEL. 
    4. Assemble a group or resistors that will yield 20k Ohm and connect it in between the legs of the sensor soul. Check the 
    console for the integer and voltage reading/value. PIN 7 must light and signals conductivity at WARNING LEVEL.

}
	
	
