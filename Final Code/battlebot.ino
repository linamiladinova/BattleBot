#include <XBOXRECV.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

int weapon = 1;
int front_right_In1 = 2; //en1 FORWARD
int front_right_In2 = 3; //en1 BACKWARD
int back_right_In3 = 4; //en2 FORWARD
int back_right_In4 = 7; //en2 BACKWARD
int front_right_EnA = 6;
int back_right_EnB = 5;

int front_left_EnA = 11;
int back_left_EnB = 10;
int front_left_In1 = 8;  //en3 FORWARD
int front_left_In2 = 9;  //en3 BACKWARD
int back_left_In3 = 12; //en4 FORWARD
int back_left_In4 = 13;  //en4 BACKWARD

int speed = 0;

void setup()
{
  Serial.begin(9600);

  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }

  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

  pinMode(back_right_EnB, OUTPUT);
  pinMode(front_right_EnA, OUTPUT);
  pinMode(front_left_EnA, OUTPUT);
  pinMode(back_left_EnB, OUTPUT);

  pinMode(front_right_In1, OUTPUT);
  pinMode(front_right_In2, OUTPUT);
  pinMode(back_right_In3, OUTPUT);
  pinMode(back_right_In4, OUTPUT);

  pinMode(front_left_In1, OUTPUT);
  pinMode(front_left_In2, OUTPUT);
  pinMode(back_left_In3, OUTPUT);
  pinMode(back_left_In4, OUTPUT);
}

void loop()
{
  Usb.Task();
  if (Xbox.XboxReceiverConnected && Xbox.Xbox360Connected[0])
  {
    if (Xbox.getButtonPress(R2, 0))
    {
      Serial.print("R2: ");
      speed = Xbox.getButtonPress(R2, 0);
      Serial.print(speed);
      Serial.print("\n");

      // if (speed <= 150)
      // {
      //   speed = 0;
      // }

      forward(speed);
    }

    if (Xbox.getButtonPress(L2, 0))
    {
      Serial.print("L2: ");
      speed = Xbox.getButtonPress(L2, 0);
      Serial.print(speed);
      Serial.print("\n");


      // if (speed <= 150)
      // {
      //   speed = 0;
      // }

      backward(speed);
    }

    int leftHatXValue = Xbox.getAnalogHat(LeftHatX, 0);

    Serial.print("Left hat X: ");
    Serial.println(leftHatXValue);

    if ( leftHatXValue < -7500 )
    {
      Serial.print("Turning left\n");
      turn_left();
    }
    else if (leftHatXValue > 7500)
    {
      Serial.print("Turning right\n");
      turn_right();
    }
    else
    {
      stop_moving();
    }

    if (Xbox.getButtonClick(A, 0))
    {
      Serial.print(F("A\n"));
      weaponOn();
    }

    if (Xbox.getButtonClick(B, 0))
    {
      Serial.print(F("B\n"));
      weaponOff();
    }

  }
}

void forward(int en_value)
{
  analogWrite(front_left_EnA, en_value);
  analogWrite(front_right_EnA, en_value);
  analogWrite(back_left_EnB, en_value);
  analogWrite(back_right_EnB, en_value);

  Serial.println(en_value);

  digitalWrite(front_right_In1, HIGH);
  digitalWrite(front_right_In2, LOW);
  digitalWrite(back_right_In3, HIGH);
  digitalWrite(back_right_In4, LOW);

  digitalWrite(front_left_In1, HIGH);
  digitalWrite(front_left_In2, LOW);
  digitalWrite(back_left_In3, HIGH);
  digitalWrite(back_left_In4, LOW);
}

void backward(int en_value)
{
  Serial.println(en_value);
  analogWrite(front_left_EnA, en_value);
  analogWrite(front_right_EnA, en_value);
  analogWrite(back_left_EnB, en_value);
  analogWrite(back_right_EnB, en_value);

  digitalWrite(front_right_In1, LOW);
  digitalWrite(front_right_In2, HIGH);
  digitalWrite(back_right_In3, LOW);
  digitalWrite(back_right_In4, HIGH);

  digitalWrite(front_left_In1, LOW);
  digitalWrite(front_left_In2, HIGH);
  digitalWrite(back_left_In3, LOW);
  digitalWrite(back_left_In4, HIGH);
}

void turn_left()
{
  analogWrite(front_left_EnA, 255);
  analogWrite(front_right_EnA, 255);
  analogWrite(back_left_EnB, 255);
  analogWrite(back_right_EnB, 255);

  digitalWrite(front_left_In1, LOW);
  digitalWrite(front_left_In2, HIGH);
  digitalWrite(back_left_In3, LOW);
  digitalWrite(back_left_In4, HIGH);

  digitalWrite(front_right_In1, HIGH);
  digitalWrite(front_right_In2, LOW);
  digitalWrite(back_right_In3, HIGH);
  digitalWrite(back_right_In4, LOW);
}

void turn_right()
{
  analogWrite(front_left_EnA, 255);
  analogWrite(front_right_EnA, 255);
  analogWrite(back_left_EnB, 255);
  analogWrite(back_right_EnB, 255);

  digitalWrite(front_left_In1, HIGH);
  digitalWrite(front_left_In2, LOW);
  digitalWrite(back_left_In3, HIGH);
  digitalWrite(back_left_In4, LOW);

  digitalWrite(front_right_In1, LOW);
  digitalWrite(front_right_In2, HIGH);
  digitalWrite(back_right_In3, LOW);
  digitalWrite(back_right_In4, HIGH);
}

void stop_moving()
{
  analogWrite(front_left_EnA, 0);
  analogWrite(front_right_EnA, 0);
  analogWrite(back_left_EnB, 0);
  analogWrite(back_right_EnB, 0);

  digitalWrite(front_left_In1, LOW);
  digitalWrite(front_left_In2, LOW);
  digitalWrite(back_left_In3, LOW);
  digitalWrite(back_left_In4, LOW);

  digitalWrite(front_right_In1, LOW);
  digitalWrite(front_right_In2, LOW);
  digitalWrite(back_right_In3, LOW);
  digitalWrite(back_right_In4, LOW);
}

void weaponOn()
{
  digitalWrite(weapon, HIGH);
}

void weaponOff()
{
  digitalWrite(weapon, LOW);
}
