#define TRIGGER A1
#define ECHO A0

#define MA1 2
#define MA2 3

#define MB1 4
#define MB2 5

void back() {
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
}

void front() {
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);

  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
}

void stop() {
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
}

void right() {
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
}

void left() {
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);

  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
}

float detect() {
  digitalWrite(TRIGGER, 1);

  delayMicroseconds(2);
  digitalWrite(TRIGGER, 0);

  return (pulseIn(A0, 1) * 0.01715);
}

void setup() {
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);

  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);

  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);

  while (1) {
    float d = detect();

    float ds[] = {0, 0};

    if (d < 20) {
      stop();
      delay(100);
      back();
      delay(400);
      stop();
      delay(100);

      right();
      delay(300);
      stop();
      delay(100);
      ds[0] = detect();

      left();
      delay(600);
      stop();
      delay(100);
      ds[1] = detect();

      right();
      delay(300);
      stop();
      delay(100);

      if (ds[0] > ds[1] && ds[0] > 20) {
        right();
        delay(300);
      } else if (ds[0] < ds[1] && ds[1] > 20) {
        left();
        delay(300);
      }
      stop();
    }

    if ( d > 20) {
      front();
    } else {
      stop();
    }
  }
}
