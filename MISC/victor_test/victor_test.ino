/*
///////////
Victor Test
///////////

Matt Bull - Victor Test V.1
*/

#include <Servo.h>
#define VICTOR_PIN 9 // the pin that the victor's signal line is attached to

Servo victor;
int i;
int maxForward = 2000; // Choose a value from 1501 to 2000. Larger number is faster. Set to 0 to skip running in forward.
int maxReverse = 1000; // Choose a value from 1499 to 1000. Smaller number is faster. Set to 0 to skip running in reverse.
int atSpeed = 6000; //Time motor will stay at max speed. (in milliseconds)
int pause = 2000; //Time between motor stopping and reversing. (in milliseconds)
int continuous = 0; //set equal to 1 in order to create an endless loop

void setup()
{
  victor.attach(VICTOR_PIN);
  Serial.begin(115200); //This is necessary to be able to view the print statements in the serial monitor
  // initialize digital pin 13 as an output. Pin 13 controls the LED on the arduino itself.
  pinMode(13, OUTPUT);
}

void loop()
{
  victor.writeMicroseconds(1500); // drive STOP
  //delay(3000); // ensure there is 3 seconds before drive starts

  // Calls the forward function if maxForward is within limits.
  if (maxForward > 1500 && maxForward < 2001)
  {
   forward();
  }
  else {
    Serial.print("\r\n Forward skipped: Outside of acceptable forward values.");
  }

  // Calls the reverse function if maxReverse is within limits.
  if (maxReverse < 1500 && maxReverse > 999)
  {
    reverse();
  }
  else {
    Serial.print("\r\n Reverse skipped: Outside of acceptable reverse values.");
  }

  // Hold motor in stopped state.
  victor.writeMicroseconds(1500); // drive STOP
  Serial.print("\r\n Stop");
  //while (continuous != 1) {} //program stays in this loop FOREVER
}

void forward(void)
{
   for ( i = 1500; i < maxForward; i) //Slow ramp to set max forward speed.
    {
      victor.writeMicroseconds(i);
      delay(5);
      i += 1;
    }
    Serial.print("\r\n Forward");
    delay(atSpeed); // max forward for set time.

    for ( i = maxForward; i > 1500; i) //slow to stop
    {
      victor.writeMicroseconds(i);
      delay(5);
      i -= 1;
    }
    delay(pause); //allow motor to coast to a stop (If jumper on the victor is set to the left position the motor will stop immedietly)
}

void reverse(void)
{
  for ( i = 1500; i > maxReverse; i) // Slow ramp up to set reverse speed
    {
      victor.writeMicroseconds(i);
      delay(5);
      i -= 1;
    }
    Serial.print("\r\n Reverse");
    delay(atSpeed); // Run for set time at set max reverse.

    for ( i = maxReverse; i < 1500; i) // Slow ramp down to full stop.
    {
      victor.writeMicroseconds(i);
      delay(5);
      i += 1;
    }
    delay(pause); //Allow motor to coast to stop
}
