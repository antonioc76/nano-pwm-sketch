#include <AVR_PWM.h>

#define PWM_PIN 10

#define DS_0 0
#define PWM_FREQUENCY 490.0
#define SECONDS_TO_MICROSECONDS 1000000.0

AVR_PWM* PWM_Instance;


void setup() {
  if (PWM_Instance) {
    PWM_Instance->setPWM(PWM_PIN, PWM_FREQUENCY, 0);
  }

  Serial.begin(9600);

  while (!Serial) {}

  Serial.println("Input throttle (0 to 1): ");
}

void clear_receive_buffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

void loop() {
  if (Serial.available()) {
    float throttle = Serial.parseFloat();

    float pulse_us = 1000.0 + 1000.0 * throttle;
    float duty = pulse_us / (SECONDS_TO_MICROSECONDS / PWM_FREQUENCY) * 100.0;

    Serial.println(duty);

    clear_receive_buffer();

    PWM_Instance->setPWM(PWM_PIN, PWM_FREQUENCY, duty);
    Serial.print("Sending throttle: ");
    Serial.println(throttle);
    
    Serial.println("Input throttle (0 to 1): ");
  }
}
