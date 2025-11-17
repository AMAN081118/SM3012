// updated_setspeed.ino
// P2: Updated SetSpeed with pause input from HC-SR04
// Tick = 100 ms

const int potPin = A0;
const int motorPwm = 3; // PWM
const int motorIn1 = 4;
const int motorIn2 = 5;
const int ledPwm = 6;

const int trigPin = 8;
const int echoPin = 9;

const unsigned long TICK_MS = 100;

int accel = 10;
int decel = 10;
int speed = 0;
unsigned long tickCount = 0;

// distance threshold (cm) for pause
const int PAUSE_THRESHOLD_CM = 30;

void setup()
{
    pinMode(motorPwm, OUTPUT);
    pinMode(motorIn1, OUTPUT);
    pinMode(motorIn2, OUTPUT);
    pinMode(ledPwm, OUTPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);

    Serial.begin(115200);
    Serial.println("tick,cmd,accel,decel,pause,speed,effective_delta");
}

long readUltrasonicCM()
{
    // send trig pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms (max ~5m)
    if (duration == 0)
        return 9999;
    long cm = duration / 58; // approximate
    return cm;
}

void loop()
{
    unsigned long start = millis();

    int raw = analogRead(potPin);
    int cmd = map(raw, 0, 1023, 0, 255);

    long dist = readUltrasonicCM();
    int pause = (dist <= PAUSE_THRESHOLD_CM) ? 1 : 0;

    int delta = 0;
    if (pause)
    {
        delta = 0;
    }
    else
    {
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
                delta = -delta;
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
    }

    // apply outputs
    analogWrite(motorPwm, speed);
    analogWrite(ledPwm, speed);

    // serial log
    Serial.print(tickCount);
    Serial.print(",");
    Serial.print(cmd);
    Serial.print(",");
    Serial.print(accel);
    Serial.print(",");
    Serial.print(decel);
    Serial.print(",");
    Serial.print(pause);
    Serial.print(",");
    Serial.print(speed);
    Serial.print(",");
    Serial.println(delta);

    tickCount++;

    unsigned long elapsed = millis() - start;
    if (elapsed < TICK_MS)
        delay(TICK_MS - elapsed);
}
