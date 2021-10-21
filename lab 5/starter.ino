// Program to simulate a ticker tape display
#define DISPLAY_LEN 16  // LCD display width
#define LINE_1 0        // LCD LINE 1 
#define LINE_2 1        // LCD LINE 2

#include <SoftwareSerial.h>
const int rxpin = 2;
const int txpin = 3;
int buzzer = 8;        // I/O pin for controlling the buzzer
SoftwareSerial serial_display(rxpin, txpin);

char p[] = "Welcome CS341 Students! ";
int string_length = 24;
char data[DISPLAY_LEN+1];
char timeblock[10];
int position=0;

 
void setup() {
  // set up the LCD's number of columns and rows:
 serial_display.begin(9600);           // setup port at 9600bps
  serial_display.write(0x0c);           // ASCII Form Feed - clear display
  delay(10);                            // delay required
}

void loop() {
  int start, j;
  // print the number of seconds on line 2 
  // starting at the middle:
  int time;
  tone(buzzer,1500);
  delay(100);
  noTone(buzzer);
  time = millis()/1000; 
  
  // turn on the buzzer for a tone =1500 hz
  tone(buzzer,1500);
  delay(10);
  
  // turn the buzzer off
  noTone(buzzer);
  serial_display.write(0x9b);  // set cursor to line 1 pos 7
  serial_display.write(itoa(time, timeblock, 10)); // convert time to ascii for print
  
 // implement a circular buffer in the for loop:
 // populate p[] with 16 chars of the string 
 // use position to track where in the string you are
    for (j=0; j < DISPLAY_LEN; j++)
    {
      data[j] = p[j];
    }
    position =(position +1)% string_length;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    serial_display.write(0x80);  //set cursor to line 0 position 0
    serial_display.write(data);  //output data
     
    delay(400);
    //serial_display.write(0x0c);  
}
