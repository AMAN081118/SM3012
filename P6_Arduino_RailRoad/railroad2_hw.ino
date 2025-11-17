// railroad2_hw.ino
// Implements RailroadSystem2 synchronous CPS on Arduino
// Tick = 100 ms
// One motor (West), LEDs for East

// INPUT BUTTONS
const int btnW = 2; // active LOW
const int btnE = 3; // active LOW

// OUTPUT LEDs
const int ledW_state = 6;
const int ledE_state = 7;
const int ledW_grant = 8;
const int ledE_grant = 9;

// MOTOR (West train only)
const int motorIn1 = 10;
const int motorIn2 = 11;
const int motorEn = 5; // PWM

const unsigned long TICK_MS = 100;

// ====== TRAIN VARIABLES ======
int st_w = 0, st_e = 0; // 0=away,1=wait,2=bridge
int req_w = 0, req_e = 0;
int onw = 0, one = 0;
int tcount_w = 0, tcount_e = 0;

// ====== CONTROLLER2 VARIABLES ======
int cur = 0; // 0=none,1=west,2=east
int last_side = 0;

// delayed grants (for causality)
int grant_w = 0, grant_e = 0;
int grant_w_d = 0, grant_e_d = 0;

unsigned long tickCount = 0;

void setup()
{
    pinMode(btnW, INPUT_PULLUP);
    pinMode(btnE, INPUT_PULLUP);

    pinMode(ledW_state, OUTPUT);
    pinMode(ledE_state, OUTPUT);
    pinMode(ledW_grant, OUTPUT);
    pinMode(ledE_grant, OUTPUT);

    pinMode(motorIn1, OUTPUT);
    pinMode(motorIn2, OUTPUT);
    pinMode(motorEn, OUTPUT);

    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);

    Serial.begin(115200);
    Serial.println("tick,approach_w,approach_e,state_w,state_e,grant_w,grant_e");
}

// TRAIN TRANSITION FUNCTION
int train_step(int approach, int grant_d, int *st, int *tcount, int *req, int *on_bridge)
{
    int st_prev = *st;
    int cnt_prev = *tcount;

    if (st_prev == 0)
    { // Away
        *req = 0;
        *on_bridge = 0;
        *tcount = 0;
        if (approach)
            *st = 1;
    }
    else if (st_prev == 1)
    { // Wait
        *req = 1;
        *on_bridge = 0;
        *tcount = 0;
        if (grant_d)
            *st = 2;
    }
    else if (st_prev == 2)
    { // Bridge
        *req = 0;
        *on_bridge = 1;
        *tcount = cnt_prev + 1;
        if (*tcount >= 3)
        {
            *st = 0;
            *tcount = 0;
        }
    }
    return *st;
}

// CONTROLLER2 TRANSITION FUNCTION
void controller2_step()
{
    int prev_cur = cur;
    int prev_last = last_side;

    if (onw && prev_cur == 1)
        cur = 1;
    else if (one && prev_cur == 2)
        cur = 2;
    else
    {
        if (req_w && req_e)
            cur = (prev_last == 1) ? 2 : 1;
        else if (req_w)
            cur = 1;
        else if (req_e)
            cur = 2;
        else
            cur = 0;
    }

    if (cur == 1)
        last_side = 1;
    else if (cur == 2)
        last_side = 2;
    else
        last_side = prev_last;

    grant_w = (cur == 1);
    grant_e = (cur == 2);
}

void loop()
{
    unsigned long start = millis();

    int approach_w = (digitalRead(btnW) == LOW);
    int approach_e = (digitalRead(btnE) == LOW);

    // TRAIN STEPS (using delayed grants)
    train_step(approach_w, grant_w_d, &st_w, &tcount_w, &req_w, &onw);
    train_step(approach_e, grant_e_d, &st_e, &tcount_e, &req_e, &one);

    // CONTROLLER STEP
    controller2_step();

    // Save delayed grants for next tick
    grant_w_d = grant_w;
    grant_e_d = grant_e;

    // OUTPUTS
    analogWrite(motorEn, (st_w == 2) ? 180 : 0);

    digitalWrite(ledW_state, (st_w == 2));
    digitalWrite(ledE_state, (st_e == 2));
    digitalWrite(ledW_grant, grant_w);
    digitalWrite(ledE_grant, grant_e);

    // Log
    Serial.print(tickCount);
    Serial.print(",");
    Serial.print(approach_w);
    Serial.print(",");
    Serial.print(approach_e);
    Serial.print(",");
    Serial.print(st_w);
    Serial.print(",");
    Serial.print(st_e);
    Serial.print(",");
    Serial.print(grant_w);
    Serial.print(",");
    Serial.println(grant_e);

    tickCount++;

    long elapsed = millis() - start;
    if (elapsed < TICK_MS)
        delay(TICK_MS - elapsed);
}
