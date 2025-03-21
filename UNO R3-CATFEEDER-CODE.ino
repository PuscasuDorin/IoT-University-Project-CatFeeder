#include <HX711_ADC.h> // scale

const int HX711_dout = 9;
const int HX711_sck = 8;
int motorpin1 = 10;
int motorpin2 = 11;

HX711_ADC LoadCell(HX711_dout, HX711_sck);

int m = 59, h = 0;
int startingH;
int portion, quantity;
bool food = true;

void FoodDispenser();

void setup() {
   Serial.begin(9600);
   LoadCell.begin();

   float calibrationValue;
   calibrationValue = 1095.84;
   LoadCell.start(2000, true);
   LoadCell.setCalFactor(calibrationValue);
   LoadCell.tareNoDelay();
   
   pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
}

void loop() {

   if (Serial.available()) {
       String data = Serial.readStringUntil('\n');
       
       // Parse the data using the comma as a delimiter
       int firstComma = data.indexOf(',');
       int secondComma = data.indexOf(',', firstComma + 1);
       int thirdComma = data.indexOf(',', secondComma + 1);
       int fourthComma = data.indexOf(',', thirdComma + 1);
       
       h = data.substring(0, firstComma).toInt();
       m = data.substring(firstComma + 1, secondComma).toInt();
       startingH = data.substring(secondComma + 1, thirdComma).toInt();
       portion = data.substring(thirdComma + 1, fourthComma).toInt();
       quantity = data.substring(fourthComma + 1).toInt();

       delay(1000); 
   }

    
   LoadCell.update();
   if (m == 0){
       food = true;
   }


   if (startingH == h && m == 1) {
       FoodDispenser();
   }

   if (portion == 2) {
       if (startingH + 12 == h && m == 1) {
           FoodDispenser();
       }
   }

   if (portion == 3) {
       if (((startingH + 8) == h || (startingH + 16) == h) && m == 1) {
           FoodDispenser();
       }
   }

   if (portion == 4) {
       if (((startingH + 6) == h || (startingH + 12) == h || (startingH + 18) == h) && m == 1) {
           FoodDispenser();
       }
   }
}

void FoodDispenser() {
   while (food == true) { 
    digitalWrite(motorpin1,   HIGH);
    digitalWrite(motorpin2, LOW);
       LoadCell.update();
       Serial.println(LoadCell.getData());
       if (LoadCell.getData() >= quantity / portion) {
           food = false;
       }
   }
}