

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

double detect() {
    digitalWrite(TRIGGER, 1);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, 0);

    return (pulseIn(ECHO, 1) / 1000000.0) * 349 / 2.0;
}

double inputs[] = {0};
double weights[] = {random(1, 1000) / 1000.0,random(1, 1000) / 1000.0};
double bias = random(0, 1) / 100.0;

double sigmoid(double x) {
return 1.0 / (1.0 + exp(-x));
}

double feedforward(double i[]) {
double hidden = i[0] * weights[0] + i[1] * weights[1];
hidden += bias;
  double output = sigmoid(hidden);
  return output;
}

void train(double i[], double target) {
  double output = feedforward(i);
double error = target - output;
  double learningRate = 0.4;
 
    weights[0] += error * i[0] * learningRate;
  weights[1] += error * i[1] * learningRate;
  bias += error * learningRate;
}

void setup() {
    pinMode(MA1, OUTPUT);
    pinMode(MA2, OUTPUT);
   
    pinMode(MB1, OUTPUT);
    pinMode(MB2, OUTPUT);
   
    pinMode(ECHO, INPUT);
    pinMode(TRIGGER, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(13,0);

    double dataset[5][2][2] = {
        {{0.02}, 1.0},
        {{0.05}, 1.0},
        {{0.1}, 1.0},
        {{0.6}, 0.5},
        {{1.0}, 0.0}
    };
   
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 5; j++) {
            train(dataset[j][0], dataset[j][1][0]);
        }
    }
}

void loop() {
  double d = detect();
  inputs[0] = d;

  double guess = feedforward(inputs);
 
  if(guess > 0.9) {
    stop();
    delay(200);
    back();
    delay(200);
    if(rand() % 2 == 0) {
      right();
    }else {
      left();
    }
    delay(200);
    stop();
    d = detect();
    inputs[0] = d;
    guess = feedforward(inputs);
  }
    
  if( guess < 0.9 ){
    front();
  }else {
    stop();
  }
}

