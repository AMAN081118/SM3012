// setspeed.ino
// Implements P1 SetSpeed behavior on Arduino (tick = 100 ms)

const int potPin = A0;
const int motorPwm = 3; // PWM
const int motorIn1 = 4;
const int motorIn2 = 5;
const int ledPwm = 6;

const unsigned long TICK_MS = 100;

int accel = 6; // max increase per tick (0-255)
int decel = 6; // max decrease per tick

int speed = 0; // current speed (0-255)
unsigned long tickCount = 0;

void setup()
{
    pinMode(motorPwm, OUTPUT);
    pinMode(motorIn1, OUTPUT);
    pinMode(motorIn2, OUTPUT);
    pinMode(ledPwm, OUTPUT);

    // motor forward default
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);

    Serial.begin(115200);

    // *** MODIFIED HEADER ***
    // We will log the actual 'delta' (the change) instead of accel/decel settings
    Serial.println("tick,cmd,delta,pause,speed");
}

void loop()
{
    unsigned long start = millis();

    // read cmd from potentiometer (0-1023) -> map to 0-255
    int raw = analogRead(potPin);
    int cmd = map(raw, 0, 1023, 0, 255);

    // compute delta
    int delta;
    if (speed < cmd)
    {
        int diff = cmd - speed;
        delta = (diff < accel) ? diff : accel;
    }
    else if (speed > cmd)
    {
        int diff = speed - cmd;
        delta = (diff < decel) ? -diff : -decel;
        if (delta > 0)
            delta = -delta; // ensure negative
    }
    else
    {
        delta = 0;
    }

    speed = speed + delta;
    if (speed < 0)
        speed = 0;
    if (speed > 255)
        speed = 255;

    // apply to motor (PWM)
    analogWrite(motorPwm, speed);
    analogWrite(ledPwm, 255 - speed);

    // no pause in P1 -> pause = 0
    int pause = 0;

    // *** MODIFIED SERIAL LOG ***
    // Log the 'delta' variable, which shows the actual change
    Serial.print(tickCount);
    Serial.print(",");
    Serial.print(cmd);
    Serial.print(",");
    Serial.print(delta);
    Serial.print(","); // Changed from accel/decel
    Serial.print(pause);
    Serial.print(",");
    Serial.println(speed);

    tickCount++;

    // wait remaining time to make 100 ms tick
    unsigned long elapsed = millis() - start;
    if (elapsed < TICK_MS)
        delay(TICK_MS - elapsed);
}