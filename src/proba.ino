#include <Jana_ard_lib.h>

#define SCLK_PIN 7
#define RCLK_PIN 6
#define DIO_PIN 5

Jana_ard_lib display(RCLK_PIN, SCLK_PIN, DIO_PIN);

void setup(){

display.begin();



}

void loop(){

display.print(1234);
display.delay(2000);

display.print("JANA");
display.delay(2000);

display.printTime(10, 34);
display.delay(2000);

display.loop();

}