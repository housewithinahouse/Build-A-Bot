void exampleDrawing000(){
  draw();
  for(int i = 0; i<100; i++){
    int option = random(1,4);
    switch(option){
      case 1:
        up();
      break;
      case 2:
        down();
      break;
      case 3:
        left();
      break;
      case 4:
        right();
      default:
        down();
    }
  }
  lift();
}
void exampleDrawing002(){
  draw();
  for(int i = 0; i<100; i++){
    int option = random(1,20);
    switch(option){
      case 1:
        up();
        left();
        down();
      break;
      case 2:
        down();
        left();
        up();
      break;
      default:
        left();
    }
  }
  lift();
}

void exampleDrawing003(){
  draw();
  for(int i = 0; i<100; i++){
    int option = random(1,20);
    switch(option){
      case 1:
        halfcircle_left();
        halfcircle_right();
      break;
      case 2:
        halfcircle_right();
        halfcircle_left();
      break;
      default:
        left();
    }
  }
  lift();
}
void exampleDrawing004(){
  draw();
  for(int i = 0; i<100; i++){
    int option = random(1,5);
    switch(option){
      case 1:
        down();
        down();
        down();
        left();
        up();
        left();
        up();
        left();
        up();
      break;
      case 2:
        down();
        down();
        down();
        right();
        up();
        right();
        up();
        right();
        up();
      break;
      default:
        left();
    }
  }
  lift();
}
