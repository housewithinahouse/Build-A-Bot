/*
 * These are all of the basic movement functions that we wrote for the drawing robot. 
 * I pulled them out into their own file for organizational reasons. Also, because I
 * think that this code could be reusable in the future. 
 */



//servo control
void draw() {
  servo.write(180);
  delay(300);
}

void lift() {
  servo.write(130);
  delay(300);
}


//basic movements
void up() {
  L_MOTOR->setSpeed(ForwardSpeed);
  R_MOTOR->setSpeed(ForwardSpeed);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(BACKWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void down() {
  L_MOTOR->setSpeed(ReverseSpeed);
  R_MOTOR->setSpeed(ReverseSpeed);
  L_MOTOR->run(FORWARD);
  R_MOTOR->run(FORWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void right() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(FORWARD);
  R_MOTOR->run(BACKWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void left() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(FORWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void halfcircle_right() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(FORWARD);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(FORWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void up_halfcircle_right() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(BACKWARD);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void halfcircle_left() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(BACKWARD);
  delay(SegmentLength);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void up_halfcircle_left() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(BACKWARD);
  delay(SegmentLength);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(SegmentLength);
}

void diagonal_right() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(FORWARD);
  R_MOTOR->run(RELEASE);
  delay(300);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(150);
}
void up_diagonal_right() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(RELEASE);
  delay(300);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(150);
}

void diagonal_left() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(FORWARD);
  delay(300);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(150);
}

void up_diagonal_left() {
  L_MOTOR->setSpeed(TurningSpeed);
  R_MOTOR->setSpeed(TurningSpeed);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(BACKWARD);
  delay(300);
  L_MOTOR->run(RELEASE);
  R_MOTOR->run(RELEASE);
  delay(150);
}

// compound movements
void writeDrawy(){
  //"D"
  draw();
  up();
  up();
  diagonal_right();
  diagonal_left();
  lift();
  right();
  //"R"
  draw();
  up();
  up();
  halfcircle_right();
  diagonal_right();
  lift();
  //"A"
  draw();
  up();
  up();
  right();
  down();
  down();
  lift();
  up();
  draw();
  left();
  lift();
  down();
  right();
  //"W"
  up();
  up();
  draw();
  down();
  down();
  right();
  up();
  down();
  right();
  up();
  up();
  lift();
  down();
  down();
  //"Y"
  up();
  up();
  draw();
  diagonal_right();
  lift();
  up();
  draw();
  diagonal_left();
  diagonal_left();
  diagonal_left();
  lift();
  //go away a bit
  down();
  down();
  down();
}

//do cool stuff

