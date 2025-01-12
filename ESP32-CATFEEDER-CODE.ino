#include <LiquidCrystal.h> //lcd
#include <Wire.h> // clock
#include <RTClib.h> //clock



const int rs = 14, en = 23, d4 = 5, d5 = 18, d6 = 19, d7 = 4;
const int  settings_b=27 ,up_b =12 ,down_b=34 ,select_b=13; 
  
int settings_b_state = 0, up_b_state = 0, down_b_state = 0, select_b_state = 0;
bool menu_state = true;
bool settings_state = false;
int count=0;
int newcount=1;
bool IsSelected= false;
bool IsSelectedSet= false;
int menucount=1;
int submenucount=1;
int m=0,h=0;
int startingH;
int portion, quantity;
int image = 1;

unsigned long previousMillis = 0; 
const long interval = 1000;  

RTC_DS1307 rtc;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte Cursor[8] =
{
0b10000,
0b11000,
0b11100,
0b11110,
0b11110,
0b11100,
0b11000,
0b10000
};

byte Cursori[8] =
{
0b00001,
0b00011,
0b00111,
0b01111,
0b01111,
0b00111,
0b00011,
0b00001
};


byte boneh1[8] =
{
0b01000,
0b10100,
0b10011,
0b01000,
0b10011,
0b10100,
0b01000,
0b00000
};


byte boneh2[8] =
{
0b00010,
0b00101,
0b11001,
0b00010,
0b11001,
0b00101,
0b00010,
0b00000
};


byte fishh1[8] =
{
0b00001,
0b00111,
0b01000,
0b10010,
0b10000,
0b01000,
0b00111,
0b00001
};


byte fishh2[8] =
{
0b00010,
0b10101,
0b01001,
0b00001,
0b00001,
0b01001,
0b10101,
0b00010
};


byte forkIcon[8] =
{
0b10101,
0b10101,
0b10101,
0b11111,
0b00100,
0b00100,
0b00100,
0b00000
};

byte spoon[8] =
{
0b01110,
0b10001,
0b10001,
0b11111,
0b00100,
0b00100,
0b00100,
0b00000
};


byte bowl1[8] =
{
0b00000,
0b00000,
0b11111,
0b10000,
0b10000,
0b01000,
0b00111,
0b00000
};


byte bowl2[8] =
{
0b00000,
0b00000,
0b11111,
0b00001,
0b00001,
0b00010,
0b11100,
0b00000
};

void setup() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  
  lcd.begin(16, 2);
  rtc.begin();
  
  pinMode(settings_b, INPUT); 
  pinMode(up_b, INPUT);
  pinMode(down_b, INPUT);
  pinMode(select_b, INPUT);
  
  lcd.createChar(0, Cursor);
  lcd.createChar(1, boneh1);
  lcd.createChar(2, boneh2);
  lcd.createChar(3, fishh1);
  lcd.createChar(4, fishh2);
  lcd.createChar(5, bowl1);
  lcd.createChar(6, bowl2);
  
  rtc.adjust(DateTime(0000, 0, 0, h, m, 0)); 


}

void menu() { 
  DateTime now = rtc.now();
  if(menu_state == true){
      lcd.setCursor(6, 0);
      lcd.print(now.hour(), DEC);
      lcd.print(":");
      lcd.print(now.minute(), DEC);
      lcd.print("     ");

      if(image == 1){
      lcd.setCursor(0, 1);
      lcd.write(byte(3));
    
      lcd.setCursor(1, 1);
      lcd.write(byte(4));
      }
      else if(image == 2){
      lcd.setCursor(0, 1);
      lcd.write(byte(1));
    
      lcd.setCursor(1, 1);
      lcd.write(byte(2));
      }
      
      lcd.setCursor(2, 1);
      lcd.print(quantity);
      lcd.print("g");
    
      lcd.setCursor(12, 1);
      lcd.write(byte(5));
      lcd.setCursor(14, 1);
      lcd.setCursor(13, 1);
      lcd.write(byte(6));
      lcd.print(portion);
      lcd.print("x");
       
    if (settings_b_state == HIGH){
      lcd.clear();
      settings_state = true;
        menu_state = false;
      delay(300);}
  }
 
}


void settings(){
  
  
  if (settings_state == true){
    
    if (IsSelected == false)
  {
      if (up_b_state == HIGH){
    lcd.clear();
    newcount = count-1;
    delay(300);}

    if (down_b_state == HIGH){
      lcd.clear();
        newcount = count+1;
        delay(300);}


    if (select_b_state == HIGH){
      lcd.clear();
      count = 0;
      IsSelected = true;
      IsSelectedSet = false;
      select_b_state = LOW;
      delay(300);}
    
  switch (newcount) {
    case 1:
      count = 1;
   
    lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("Set Time        ");

      lcd.setCursor(0, 1);
      lcd.print("Set Portions    ");
    
      
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("Set Time        ");

      lcd.setCursor(1, 1);
      lcd.print("Set Portions    ");
    break;
    
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("Set Quantity    ");

      lcd.setCursor(0, 1);
      lcd.print("Food Icon       ");
    break;
    
    case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("Set Quantity    ");

      lcd.setCursor(1, 1);
      lcd.print("Food Icon       ");
    break;

    case 5:
      count = 5;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("ServingStarterH ");

      lcd.setCursor(0, 1);
      lcd.print("EXIT            ");
    break;
    
    case 6:
      count = 6;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("ServingStarterH ");

      lcd.setCursor(1, 1);
      lcd.print("EXIT            ");
    break;
    
    default:
      newcount = 1;
    
   }    
  }
  //SET TIME MENU 
  if (IsSelectedSet == false && IsSelected == true && newcount == 1)
  {
    if (up_b_state == HIGH){
      lcd.clear();
      menucount = count-1;
      delay(300);}

    if (down_b_state == HIGH){
      lcd.clear();
      menucount = count+1;
      delay(300);}

    if (select_b_state == HIGH && (count == 1 || count == 2)){
      lcd.clear();
      count = 0;
      newcount = 1;
      IsSelectedSet = true;
      select_b_state = LOW;
      delay(300);}

    if (select_b_state == HIGH && count == 3){
      lcd.clear();
      count = 0;
      newcount = 1;
      menucount = 1;
      IsSelectedSet = false;
      IsSelected = false;
      select_b_state = LOW;
      delay(300);}
    
  switch (menucount) {
    case 1:
      count = 1;
   
    lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("HOUR            ");

      lcd.setCursor(0, 1);
      lcd.print("MINUTE          ");
    
      
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("HOUR            ");

      lcd.setCursor(1, 1);
      lcd.print("MINUTE          ");
    break;

    case 3:
      count = 3;
   
    lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("BACK            ");

      lcd.setCursor(0, 1);
      lcd.print("                ");
   
    break;
    
    default:
      menucount = 1;
    
  }
 }     
  
  //SET PORTIONS MENU
  if (IsSelectedSet == false && IsSelected == true && newcount == 2){
    if (up_b_state == HIGH){
        menucount = count-1;
        delay(300);}

    if (down_b_state == HIGH){
        menucount = count+1;
        delay(300);}

    if (select_b_state == HIGH){
      lcd.clear();
      portion = count ;
      count = 0;
      newcount = 1;
      IsSelectedSet = false;
      IsSelected = false;
      select_b_state = LOW;
      delay(300);}
    

    switch (menucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("One Portion     ");  // 24h/1portie

      lcd.setCursor(0, 1);
      lcd.print("Two Portions    ");  // 24h/2portii
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("One Portion     "); // 24h/1portie

      lcd.setCursor(1, 1);
      lcd.print("Two Portions    ");  // 24h/2portii
    break;
    
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("Three Portions  "); // 24h/3portii

      lcd.setCursor(0, 1);
      lcd.print("Four Portions   ");  // 24h/4portii
    break;
      
      case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("Three Portions  "); // 24h/3portii

      lcd.setCursor(1, 1);
      lcd.print("Four Portions   "); // 24h/4portii
    break;

    default:
      menucount = 1;
    
    }
  }
    //SET QUANTITY MENU (total quantity of food) - quantiti/portions 
  if (IsSelectedSet == false && IsSelected == true && newcount == 3){
    if (up_b_state == HIGH){
        menucount = count-1;
        delay(300);}

    if (down_b_state == HIGH){
        menucount = count+1;
        delay(300);}

    if (select_b_state == HIGH){
        lcd.clear();
        count = 0;
        newcount = 1;
        IsSelectedSet = false;
        IsSelected = false;
        select_b_state = LOW;
        delay(300);}
      

    switch (menucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("20g             ");

      lcd.setCursor(0, 1);
      lcd.print("30g             ");

      quantity = 20;
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("20g             ");

      lcd.setCursor(1, 1);
      lcd.print("30g             ");
      
      quantity = 30;
    break;
    
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("40g             ");

      lcd.setCursor(0, 1);
      lcd.print("50g             ");

      quantity = 40;
    break;
      
      case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("40g             ");

      lcd.setCursor(1, 1);
      lcd.print("50g             ");

      quantity = 50;
    break;

      case 5:
      count = 5;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("60g             ");

      lcd.setCursor(0, 1);
      lcd.print("70g             ");

      quantity = 60;
    break;
      
      case 6:
      count = 6;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("60g             ");

      lcd.setCursor(1, 1);
      lcd.print("70g             ");

      quantity = 70;
    break;

        case 7:
      count = 7;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("80g             ");

      lcd.setCursor(0, 1);
      lcd.print("90g             ");

      quantity = 80;
    break;
      
      case 8:
      count = 8;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("80g             ");

      lcd.setCursor(1, 1);
      lcd.print("90g             ");

      quantity = 90;
    break;

        case 9:
      count = 9;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("100g            ");

      lcd.setCursor(0, 1);
      lcd.print("110g            ");

      quantity = 100;
    break;
      
      case 10:
      count = 10;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("100g            ");

      lcd.setCursor(1, 1);
      lcd.print("110g            ");

      quantity = 110;
    break;

        case 11:
      count = 11;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("120g            ");

      lcd.setCursor(0, 1);
      lcd.print("130g            ");

      quantity = 120;
    break;
      
      case 12:
      count = 12;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("120g            ");

      lcd.setCursor(1, 1);
      lcd.print("130g            ");

      quantity = 130;
    break;

        case 13:
      count = 13;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("140g            ");

      lcd.setCursor(0, 1);
      lcd.print("150g            ");

      quantity = 140;
    break;
      
      case 14:
      count = 14;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("140g            ");

      lcd.setCursor(1, 1);
      lcd.print("150g            ");

      quantity = 150;
    break;

    default:
      menucount = 1;
    }
  }

  //SET ICON
  if (IsSelectedSet == false && IsSelected == true && newcount == 4){
    if (up_b_state == HIGH){
        menucount = count-1;
        delay(300);}

    if (down_b_state == HIGH){
        menucount = count+1;
        delay(300);}

    if (select_b_state == HIGH && (count == 1 || count == 2)){
      if (count == 1) {image = 1;}
      if (count == 2) {image = 2;}
      lcd.clear();
      count = 0;
      newcount = 1;
      IsSelectedSet = false;
      IsSelected = false;
      select_b_state = LOW;
      delay(300);}
    

    switch (menucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      
      lcd.setCursor(1, 0);
      lcd.write(byte(3));
    
      lcd.setCursor(2, 0);
      lcd.write(byte(4));
      lcd.print("             ");

      lcd.setCursor(0, 1);
      lcd.write(byte(1));
    
      lcd.setCursor(1, 1);
      lcd.write(byte(2));
      lcd.print("              ");
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.write(byte(3));
    
      lcd.setCursor(1, 0);
      lcd.write(byte(4));
      lcd.print("              ");

      lcd.setCursor(1, 1);
      lcd.write(byte(1));
    
      lcd.setCursor(2, 1);
      lcd.write(byte(2));
      lcd.print("            ");
    break;
  
    default:
      menucount = 1;
    }
  }

  
    //ServingStarterH
    if (IsSelectedSet == false && IsSelected == true && newcount == 5){
      if (up_b_state == HIGH){
          menucount = count-1;
          delay(300);}
  
      if (down_b_state == HIGH){
          menucount = count+1;
          delay(300);}
  
      if (select_b_state == HIGH){
        lcd.clear();
        if(count == 24){startingH=0;}
        else{startingH = count;}
        count = 0;
        newcount = 1;
        IsSelectedSet = false;
        IsSelected = false;
        select_b_state = LOW;
        delay(300);}
    

    switch (menucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("1               ");

      lcd.setCursor(0, 1);
      lcd.print("2               ");
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("1               ");

      lcd.setCursor(1, 1);
      lcd.print("2               ");
    break;
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("3               ");

      lcd.setCursor(0, 1);
      lcd.print("4               ");
    break;
    
    case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("3               ");

      lcd.setCursor(1, 1);
      lcd.print("4               ");
    break;

    case 5:
      count = 5;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("5               ");

      lcd.setCursor(0, 1);
      lcd.print("6               ");
    break;
    
    case 6:
      count = 6;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("5               ");

      lcd.setCursor(1, 1);
      lcd.print("6               ");
    break;

    case 7:
      count = 7;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("7 ");

      lcd.setCursor(0, 1);
      lcd.print("8 ");
    break;
    
    case 8:
      count = 8;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("7 ");

      lcd.setCursor(1, 1);
      lcd.print("8 ");
    break;

    case 9:
      count = 9;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("9 ");

      lcd.setCursor(0, 1);
      lcd.print("10 ");
    break;
    
    case 10:
      count = 10;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("9 ");

      lcd.setCursor(1, 1);
      lcd.print("10 ");
    break;

    case 11:
      count = 11;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("11 ");

      lcd.setCursor(0, 1);
      lcd.print("12 ");
    break;
    
    case 12:
      count = 12;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("11 ");

      lcd.setCursor(1, 1);
      lcd.print("12 ");
    break;

    case 13:
      count = 13;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("13 ");

      lcd.setCursor(0, 1);
      lcd.print("14 ");
    break;
    
    case 14:
      count = 14;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("13 ");

      lcd.setCursor(1, 1);
      lcd.print("14 ");
    break;

    case 15:
      count = 15;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("15 ");

      lcd.setCursor(0, 1);
      lcd.print("16 ");
    break;
    
    case 16:
      count = 16;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("15 ");

      lcd.setCursor(1, 1);
      lcd.print("16 ");
    break;

    case 17:
      count = 17;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("17 ");

      lcd.setCursor(0, 1);
      lcd.print("18 ");
    break;
    
    case 18:
      count = 18;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("17 ");

      lcd.setCursor(1, 1);
      lcd.print("18 ");
    break;

    case 19:
      count = 19;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("19 ");

      lcd.setCursor(0, 1);
      lcd.print("20 ");
    break;
    
    case 20:
      count = 20;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("19 ");

      lcd.setCursor(1, 1);
      lcd.print("20 ");
    break;

    case 21:
      count = 21;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("21 ");

      lcd.setCursor(0, 1);
      lcd.print("22 ");
    break;
    
    case 22:
      count = 22;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("21 ");

      lcd.setCursor(1, 1);
      lcd.print("22 ");
    break;

    case 23:
      count = 23;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("23 ");

      lcd.setCursor(0, 1);
      lcd.print("00 ");
    break;
    
    case 24:
      count = 24;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("23 ");

      lcd.setCursor(1, 1);
      lcd.print("00 ");
    break;

    default:
      menucount = 1;
    
    }
   }

    
    //exit
  if (IsSelected == true && newcount == 6){
      lcd.clear();
      newcount = 1;
      settings_state = false;
      menu_state = true;
      IsSelected = false;
      delay(300);}


   //Time-menu -> SET HOUR
   if (IsSelectedSet == true && menucount == 1){
    if (up_b_state == HIGH){
        lcd.clear();
        submenucount = count-1;
        delay(300);}

    if (down_b_state == HIGH){
        lcd.clear();
        submenucount = count+1;
        delay(300);}

    if (select_b_state == HIGH){
        lcd.clear();
        if(count == 24){h=0;}
        else{h = count;}
        count = 0;
        menucount = 1;
        submenucount = 1;
        IsSelectedSet = false;
        IsSelected = true;
        select_b_state = LOW;
        rtc.adjust(DateTime(0000,0,0,h,m,0));
        delay(300);}

    switch (submenucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("1               ");

      lcd.setCursor(0, 1);
      lcd.print("2               ");
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("1 ");

      lcd.setCursor(1, 1);
      lcd.print("2 ");
    break;
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("3 ");

      lcd.setCursor(0, 1);
      lcd.print("4 ");
    break;
    
    case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("3 ");

      lcd.setCursor(1, 1);
      lcd.print("4 ");
    break;

    case 5:
      count = 5;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("5 ");

      lcd.setCursor(0, 1);
      lcd.print("6 ");
    break;
    
    case 6:
      count = 6;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("5 ");

      lcd.setCursor(1, 1);
      lcd.print("6 ");
    break;

    case 7:
      count = 7;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("7 ");

      lcd.setCursor(0, 1);
      lcd.print("8 ");
    break;
    
    case 8:
      count = 8;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("7 ");

      lcd.setCursor(1, 1);
      lcd.print("8 ");
    break;

    case 9:
      count = 9;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("9 ");

      lcd.setCursor(0, 1);
      lcd.print("10 ");
    break;
    
    case 10:
      count = 10;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("9 ");

      lcd.setCursor(1, 1);
      lcd.print("10 ");
    break;

    case 11:
      count = 11;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("11 ");

      lcd.setCursor(0, 1);
      lcd.print("12 ");
    break;
    
    case 12:
      count = 12;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("11 ");

      lcd.setCursor(1, 1);
      lcd.print("12 ");
    break;

    case 13:
      count = 13;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("13 ");

      lcd.setCursor(0, 1);
      lcd.print("14 ");
    break;
    
    case 14:
      count = 14;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("13 ");

      lcd.setCursor(1, 1);
      lcd.print("14 ");
    break;

    case 15:
      count = 15;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("15 ");

      lcd.setCursor(0, 1);
      lcd.print("16 ");
    break;
    
    case 16:
      count = 16;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("15 ");

      lcd.setCursor(1, 1);
      lcd.print("16 ");
    break;

    case 17:
      count = 17;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("17 ");

      lcd.setCursor(0, 1);
      lcd.print("18 ");
    break;
    
    case 18:
      count = 18;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("17 ");

      lcd.setCursor(1, 1);
      lcd.print("18 ");
    break;

    case 19:
      count = 19;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("19 ");

      lcd.setCursor(0, 1);
      lcd.print("20 ");
    break;
    
    case 20:
      count = 20;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("19 ");

      lcd.setCursor(1, 1);
      lcd.print("20 ");
    break;

    case 21:
      count = 21;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("21 ");

      lcd.setCursor(0, 1);
      lcd.print("22 ");
    break;
    
    case 22:
      count = 22;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("21 ");

      lcd.setCursor(1, 1);
      lcd.print("22 ");
    break;

    case 23:
      count = 23;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("23 ");

      lcd.setCursor(0, 1);
      lcd.print("00 ");
    break;
    
    case 24:
      count = 24;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("23 ");

      lcd.setCursor(1, 1);
      lcd.print("00 ");
    break;

    default:
      submenucount = 1;
    
    }
   }
   //Time-menu -> SET MINUTE
   if (IsSelectedSet == true && menucount == 2){
    if (up_b_state == HIGH){
      lcd.clear();
        submenucount = count-1;
        delay(300);}

    if (down_b_state == HIGH){
      lcd.clear();
        submenucount = count+1;
        delay(300);}

    if (select_b_state == HIGH){
      lcd.clear();
      m = count-1;
      count = 0;
      menucount = 1;
      submenucount = 1;
      IsSelectedSet = false;
      IsSelected = true;
      select_b_state = LOW;
      rtc.adjust(DateTime(0000,0,0,h,m,0));
      delay(300);}

switch (submenucount) {
    case 1:
      count = 1;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("0               ");

      lcd.setCursor(0, 1);
      lcd.print("1               ");
    break;
    
    case 2:
      count = 2;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("0 ");

      lcd.setCursor(1, 1);
      lcd.print("1 ");
    break;
    case 3:
      count = 3;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("2 ");

      lcd.setCursor(0, 1);
      lcd.print("3 ");
    break;
    
    case 4:
      count = 4;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("2 ");

      lcd.setCursor(1, 1);
      lcd.print("3 ");
    break;

    case 5:
      count = 5;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("4 ");

      lcd.setCursor(0, 1);
      lcd.print("5 ");
    break;
    
    case 6:
      count = 6;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("4 ");

      lcd.setCursor(1, 1);
      lcd.print("5 ");
    break;

    case 7:
      count = 7;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("6 ");

      lcd.setCursor(0, 1);
      lcd.print("7 ");
    break;
    
    case 8:
      count = 8;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("6 ");

      lcd.setCursor(1, 1);
      lcd.print("7 ");
    break;

    case 9:
      count = 9;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("8 ");

      lcd.setCursor(0, 1);
      lcd.print("9 ");
    break;
    
    case 10:
      count = 10;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("8 ");

      lcd.setCursor(1, 1);
      lcd.print("9 ");
    break;

    case 11:
      count = 11;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("10 ");

      lcd.setCursor(0, 1);
      lcd.print("11 ");
    break;
    
    case 12:
      count = 12;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("10 ");

      lcd.setCursor(1, 1);
      lcd.print("11 ");
    break;

    case 13:
      count = 13;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("12 ");

      lcd.setCursor(0, 1);
      lcd.print("13 ");
    break;
    
    case 14:
      count = 14;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("12 ");

      lcd.setCursor(1, 1);
      lcd.print("13 ");
    break;

    case 15:
      count = 15;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("14 ");

      lcd.setCursor(0, 1);
      lcd.print("15 ");
    break;
    
    case 16:
      count = 16;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("14 ");

      lcd.setCursor(1, 1);
      lcd.print("15 ");
    break;

    case 17:
      count = 17;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("16 ");

      lcd.setCursor(0, 1);
      lcd.print("17 ");
    break;
    
    case 18:
      count = 18;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("16 ");

      lcd.setCursor(1, 1);
      lcd.print("17 ");
    break;

    case 19:
      count = 19;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("18 ");

      lcd.setCursor(0, 1);
      lcd.print("19 ");
    break;
    
    case 20:
      count = 20;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("18 ");

      lcd.setCursor(1, 1);
      lcd.print("19 ");
    break;

    case 21:
      count = 21;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("20 ");

      lcd.setCursor(0, 1);
      lcd.print("21 ");
    break;
    
    case 22:
      count = 22;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("20 ");

      lcd.setCursor(1, 1);
      lcd.print("21 ");
    break;

    case 23:
      count = 23;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("22 ");

      lcd.setCursor(0, 1);
      lcd.print("23 ");
    break;
    
    case 24:
      count = 24;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("22 ");

      lcd.setCursor(1, 1);
      lcd.print("23 ");
    break;

    case 25:
      count = 25;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("24 ");

      lcd.setCursor(0, 1);
      lcd.print("25 ");
    break;
    
    case 26:
      count = 26;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("24 ");

      lcd.setCursor(1, 1);
      lcd.print("25 ");
    break;
    case 27:
      count = 27;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("26 ");

      lcd.setCursor(0, 1);
      lcd.print("27 ");
    break;
    
    case 28:
      count = 28;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("26 ");

      lcd.setCursor(1, 1);
      lcd.print("27 ");
    break;

    case 29:
      count = 29;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("28 ");

      lcd.setCursor(0, 1);
      lcd.print("29 ");
    break;
    
    case 30:
      count = 30;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("28 ");

      lcd.setCursor(1, 1);
      lcd.print("29 ");
    break;

    case 31:
      count = 31;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("30 ");

      lcd.setCursor(0, 1);
      lcd.print("31 ");
    break;
    
    case 32:
      count = 32;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("30 ");

      lcd.setCursor(1, 1);
      lcd.print("31 ");
    break;

    case 33:
      count = 33;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("32 ");

      lcd.setCursor(0, 1);
      lcd.print("33 ");
    break;
    
    case 34:
      count = 34;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("32 ");

      lcd.setCursor(1, 1);
      lcd.print("33 ");
    break;

    case 35:
      count = 35;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("34 ");

      lcd.setCursor(0, 1);
      lcd.print("35 ");
    break;
    
    case 36:
      count = 36;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("34 ");

      lcd.setCursor(1, 1);
      lcd.print("35 ");
    break;

    case 37:
      count = 37;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("36 ");

      lcd.setCursor(0, 1);
      lcd.print("37 ");
    break;
    
    case 38:
      count = 38;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("36 ");

      lcd.setCursor(1, 1);
      lcd.print("37 ");
    break;

    case 39:
      count = 39;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("38 ");

      lcd.setCursor(0, 1);
      lcd.print("39 ");
    break;
    
    case 40:
      count = 40;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("38 ");

      lcd.setCursor(1, 1);
      lcd.print("39 ");
    break;

    case 41:
      count = 41;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("40 ");

      lcd.setCursor(0, 1);
      lcd.print("41 ");
    break;
    
    case 42:
      count = 42;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("40 ");

      lcd.setCursor(1, 1);
      lcd.print("41 ");
    break;

    case 43:
      count = 43;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("42 ");

      lcd.setCursor(0, 1);
      lcd.print("43 ");
    break;
    
    case 44:
      count = 44;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("42 ");

      lcd.setCursor(1, 1);
      lcd.print("43 ");
    break;

    case 45:
      count = 45;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("44 ");

      lcd.setCursor(0, 1);
      lcd.print("45 ");
    break;
    
    case 46:
      count = 46;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("44 ");

      lcd.setCursor(1, 1);
      lcd.print("45 ");
    break;

    case 47:
      count = 47;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("46 ");

      lcd.setCursor(0, 1);
      lcd.print("47 ");
    break;
    
    case 48:
      count = 48;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("46 ");

      lcd.setCursor(1, 1);
      lcd.print("47 ");
    break;

    case 49:
      count = 49;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("48 ");

      lcd.setCursor(0, 1);
      lcd.print("49 ");
    break;

    case 50:
      count = 50;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("48 ");

      lcd.setCursor(1, 1);
      lcd.print("49 ");
    break;
    
    case 51:
      count = 51;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("50 ");

      lcd.setCursor(0, 1);
      lcd.print("51 ");
    break;

    case 52:
      count = 52;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("50 ");

      lcd.setCursor(1, 1);
      lcd.print("51 ");
    break;
    
    case 53:
      count = 53;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("52 ");

      lcd.setCursor(0, 1);
      lcd.print("53 ");
    break;

    case 54:
      count = 54;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("52 ");

      lcd.setCursor(1, 1);
      lcd.print("53 ");
    break;
    
    case 55:
      count = 55;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("54 ");

      lcd.setCursor(0, 1);
      lcd.print("55 ");
    break;

    case 56:
      count = 56;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("54 ");

      lcd.setCursor(1, 1);
      lcd.print("55 ");
    break;
    
    case 57:
      count = 57;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("56 ");

      lcd.setCursor(0, 1);
      lcd.print("57 ");
    break;

     case 58:
      count = 58;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("56 ");

      lcd.setCursor(1, 1);
      lcd.print("57 ");
    break;

        case 59:
      count = 59;

      lcd.setCursor(0, 0);
      lcd.write(byte(0));

      lcd.setCursor(1, 0);
      lcd.print("58 ");

      lcd.setCursor(0, 1);
      lcd.print("59 ");
    break;

     case 60:
      count = 60;

      lcd.setCursor(0, 1);
      lcd.write(byte(0));

      lcd.setCursor(0, 0);
      lcd.print("58 ");

      lcd.setCursor(1, 1);
      lcd.print("59 ");
    break;

    default:
      submenucount = 1;
    }
   }
  }
 }

void loop() {
   up_b_state = digitalRead(up_b);  
  down_b_state = digitalRead(down_b);
  select_b_state = digitalRead(select_b);
  settings_b_state = digitalRead(settings_b);  

DateTime now = rtc.now();
  h = now.hour();
  m = now.minute();
  
  unsigned long currentMillis = millis();  // Get current time
  // Check if the interval has passed (500ms in this example)
  if (currentMillis - previousMillis >= interval) {
    // Save the last time data was sent
    previousMillis = currentMillis;
  // Send all data in a single line with a delimiter (e.g., commas)
  Serial2.print(h);
  Serial2.print(",");
  Serial2.print(m);
  Serial2.print(",");
  Serial2.print(startingH);
  Serial2.print(",");
  Serial2.print(portion);
  Serial2.print(",");
  Serial2.println(quantity); // End the data with a newline character
  Serial.println("A");
 
  }
    
  menu();
  settings();  

}



  
  
