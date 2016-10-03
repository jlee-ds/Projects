#include "AccelStepper.h"

#define NOTE_AS3 233

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define HALFSTEP 8

// motor pins
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define ON 1
#define OFF 0

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

int melody[] = {
  NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_D5, NOTE_AS4,
  NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_AS4,
  NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_AS4, NOTE_C4,
  NOTE_A4, NOTE_C5, NOTE_AS4, 0, //간주 1번
  NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_D5, NOTE_AS4,
  NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_AS4,
  NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_AS4, NOTE_C4,
  NOTE_A4, NOTE_C5, NOTE_AS4, 0, //간주 2번 반복
  0, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, //The sea weed is
  NOTE_A4, NOTE_C5, NOTE_AS4, NOTE_F4, //always greener
  0, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_D4, //in somebody
  NOTE_C4, NOTE_F4, NOTE_D4, 0, //else's lake
  0, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, //You dream about
  NOTE_A4, NOTE_C5, NOTE_AS4, NOTE_F4, //going up there
  0, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_D4, //But that is a
  NOTE_C4, NOTE_F4, NOTE_D4, 0, //big mistake
  0, NOTE_G4, NOTE_AS4, NOTE_AS4, NOTE_G4, //Just look at the
  NOTE_F4, NOTE_AS4, NOTE_F4, NOTE_AS4, //world around you
  0, NOTE_A4, NOTE_C5, NOTE_C5, NOTE_AS4, //right here on the
  NOTE_D5, NOTE_C5, NOTE_AS4, 0, //ocean floor
  0, NOTE_G4, NOTE_AS4, NOTE_AS4, NOTE_G4, //Such wonderful
  NOTE_F4, NOTE_AS4, NOTE_F4, NOTE_AS4, //things surround you
  0, NOTE_A4, NOTE_C5, NOTE_C5, NOTE_AS4, //What more is you
  NOTE_D5, NOTE_C5, NOTE_AS4, 0, //looking for?
  0, 0, NOTE_D5, NOTE_C5, NOTE_AS4, //under the
  NOTE_G4, 0, 0, //sea
  0, 0, NOTE_C5, NOTE_C5, NOTE_AS4, //under the
  NOTE_C5, 0, 0, //sea
  0, 0, NOTE_D5, NOTE_C5, NOTE_AS4, //Daling it's
  NOTE_G4, NOTE_F4, NOTE_D5, NOTE_C5, NOTE_AS4, //better down where it's
  NOTE_G4, NOTE_F4, NOTE_D5, NOTE_C5, NOTE_AS4, //weter. Take it from
  NOTE_D5, NOTE_D5, //me
  0, 0, NOTE_D5, NOTE_C5, NOTE_AS4, //Up on the
  NOTE_G4, NOTE_AS4, NOTE_AS4, NOTE_G4, NOTE_C5, //shore they work all day.
  0, 0, NOTE_C5, NOTE_AS4, NOTE_C5, //Out in the
  NOTE_D5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_AS4, //sun they slave a way.
  0, 0, NOTE_D5, NOTE_C5, NOTE_AS4, //While we de-
  NOTE_G4, NOTE_F4, NOTE_D5, NOTE_C5, NOTE_AS4, //voting full time to
  NOTE_G5, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_AS4, //floating under the
  NOTE_AS4, NOTE_AS4 //sea
};

int tempo[] = {
  200, 200, 200, 400, 400, 200,
  400, 400, 400, 400,
  200, 200, 200, 400, 400, 200,
  400, 400, 400, 400, //간주 1번
  200, 200, 200, 400, 400, 200,
  400, 400, 400, 400,
  200, 200, 200, 400, 400, 200,
  400, 400, 400, 400, //간주 2번 반복
  400, 200, 400, 400, 200, //The seaweed is
  400, 400, 400, 400, //always greener
  400, 200, 400, 400, 200, //in somebody
  400, 400, 400, 400, //else's lake.
  400, 200, 400, 400, 200, //You dream about
  400, 400, 400, 400, //going up there.
  400, 200, 400, 400, 200, //But that is a
  400, 400, 400, 400, //big mistake.
  400, 200, 400, 400, 200, //Just look at the
  400, 400, 400, 400, //world around you,
  400, 200, 400, 400, 200, //right here on the
  400, 400, 400, 400, //ocean floor.
  400, 200, 400, 400, 200, //Such wonderful
  400, 400, 400, 400, //things surround you.
  400, 200, 400, 400, 200, //What more is you
  400, 400, 400, 400, //looking for?
  400, 200, 400, 200, 400, //under the
  400, 400, 800, //sea
  400, 200, 400, 200, 400, //under the
  400, 400, 800, //sea
  400, 200, 400, 200, 400, //Darling it's
  200, 400, 400, 200, 400, //better down where it's
  200, 400, 400, 200, 400, //weter. Take it from
  800, 800, //me.
  400, 200, 400, 400, 200, //Up on the
  400, 200, 400, 200, 400, //shore they work all day.
  400, 200, 400, 400, 200, //Out in the
  400, 200, 400, 200, 400, //sun they slave a way.
  400, 200, 400, 200, 400, //While we de-
  200, 400, 400, 200, 400, //voting full time to
  200, 400, 400, 200, 400, //floating under the
  800, 800 //sea
};

int box_flag = OFF; //total flag
int led_flag = ON;
int music_flag = ON;
int melody_length = sizeof(melody) / sizeof(int);

void setup() {
  pinMode(2, OUTPUT); //buzzer
  pinMode(13, OUTPUT); //lightbulb1

  Serial.begin(9600);

  delay(3000); //sime time to put the robot down after swithing it on
  stepper1.setMaxSpeed(2000.0);
  stepper1.move(1);  // I found this necessary
  stepper1.setSpeed(1000);

}

void push_button() {
  int input = Serial.read();
  if (input == 65) {
    box_flag = 1;
    Serial.println("start box button was pushed!");
  }
  else if (input == 66) {
    box_flag = 0;
    Serial.println("stop box button was pushed!");
  }
  else if (input == 67) {
    Serial.println("start music button was pushed!");
    music_flag = 1;
  }
  else if (input == 68) {
    music_flag = 0;
    Serial.println("stop music button was pushed!");
  }
  else if (input == 69) {
    led_flag = 1;
    Serial.println("turn on led button was pushed!");
  }
  else if (input == 70) {
    led_flag = 0;
    Serial.println("turn off led button was pushed!");
  }
}

void music_box() {
  if (box_flag) {
    Serial.println("start box!");
    if (led_flag) digitalWrite(13, HIGH);
   // if (!led_flag) digitalWrite(13, LOW);

    for (int thisNote = 0; thisNote < melody_length; thisNote++) {
      if (Serial.available()) push_button();

      if (led_flag) digitalWrite(13, HIGH);
      if (!led_flag) digitalWrite(13, LOW);
      if (!box_flag) {
        Serial.println("stop box!");
        digitalWrite(13, LOW);
        noTone(2);
        break;
      }
      if (music_flag) {
        Serial.println(thisNote);
        tone(2, melody[thisNote], tempo[thisNote]);
        for (int delay_motor = 0; delay_motor < tempo[thisNote] * 21000; delay_motor++) {
          stepper1.move(6600);
          stepper1.setSpeed(1000);
          stepper1.runSpeedToPosition();

        } //for loop for step motor
      }
      if (!music_flag) {
        thisNote = -1;
        stepper1.move(6600);
        stepper1.setSpeed(1000);
        stepper1.runSpeedToPosition();
      }
    } //for loop for buzzer

  }
  else {
    Serial.println("stop box!");
    digitalWrite(13, LOW);
    noTone(2);
  }
}
void loop() {
    push_button();
    music_box();
  }
