int incomingByte[100] ;
char k ;
int col = 2;
int row = 0;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
Serial.begin(9600);
lcd.begin(16,2);
}
void newsetup(char k)
{
  lcd.setCursor(row,col);
        // print the letter:
   lcd.write(k);
   row++;
}
// for incoming serial data
// opens serial port, sets data rate to 9600 bps
void loop()
{

int i = 0;
char name[10] = {};
//k = 0;
while (Serial.available() > 0)
{
k = Serial.read();
name[i] = k;
i++;

 if ( k == 'z' )
{
  delay(2000) ;
  lcd.begin(20,4);
  row = 2 ;
  col = 0 ;
  lcd.setCursor(row,col);
  lcd.write("FACE RECOGNIZED!!");
  row = 5;
  col = 2;
  continue ;
}

lcd.display();
newsetup(k);
Serial.print(k);
//k =k+1 ;
delay(100) ;
}


lcd.display();
}

