#include "mbed.h"
#include "C12832.h"

/* initialising Red led r pin23 and Green led g pin24 as Pulse Width Modulation
 PWM output initialising pot1 pin19 and pot2  pin20 as Analog input*/

PwmOut r(p23);
PwmOut g(p24);
AnalogIn pot1(p19);
AnalogIn pot2(p20);

C12832 lcd(p5, p7, p6, p8, p11); // initialising LCD pins

int main() {
  float p1, p2;

  lcd.set_auto_up(0);

  while (true) {
    p1 = pot1.read_u16(); // reading the analog input from pot 1 as unsigned 16
                          // bit integer
    p2 = pot2.read_u16(); // reading the analog input from pot 2 as unsigned 16
                          // bit integer

    lcd.locate(0, 3);
    lcd.printf("Pot 1 = %.2f",
               (float)pot1); // Analog input from pot1 is printed in LCD in the
                             // location (0,3)
    lcd.locate(0, 14);
    lcd.printf("Pot 2 = %.2f",
               (float)pot2); // / Analog input from pot2 is printed in LCD in
                             // the location (0,14)

    
    
    r.period(0.05);

    float p = 3 * p1;
    float q = 3 * p2;
// R LED and G LED colour intensity are varied based on analod pot 1 and pot 2 value
    r = 1.0 - ((p < 1.0) ? 1.0 - p1 : (p > 2.0) ? p - 2.0 : 0.0);
    g = 1.0 - ((q < 1.0) ? q : (q > 2.0) ? 0.0 : 2.0 - q);

    lcd.copy_to_lcd();
    wait(0.01);
  }
}
