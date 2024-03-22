#define r_motor_encoder A2 // A1
#define l_motor_encoder A0 // A0

int threshold = 500;
int r_sensor_value;
int l_sensor_value;
int r_last = 0;
int r_ticks = 0;
int l_last = 0;
int l_ticks = 0;

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(20);
}

void loop(){
  r_sensor_value = analogRead(r_motor_encoder); 
  l_sensor_value = analogRead(l_motor_encoder);

  // RIGHT ENCODER
  if (r_last == 0 && r_sensor_value < threshold) {
    //white
    r_last = 1;
    r_ticks += 1;
  } else if (r_last == 1 && r_sensor_value > threshold) {
    //black
    r_ticks += 1;
    r_last = 0;
  }

  // LEFT ENCODER
  if (l_last == 0 && l_sensor_value < threshold) {
    //white
    l_last = 1;
    l_ticks += 1;
  } else if (l_last == 1 && l_sensor_value > threshold) {
    //black
    l_ticks += 1;
    l_last = 0;
  }

  Serial.print(r_ticks);
  Serial.print(", ");
  Serial.println(l_ticks);
}