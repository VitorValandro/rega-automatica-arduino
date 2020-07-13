const int soil_sensor1 = A0; //defining ports of sensor 1 and 2
const int soil_sensor2 = A1;
const int water_level = 2;   //defining port of cistern level sensor
const int rele_valve1 = 4;   //defining ports of solenoid valves
const int rele_valve2 = 5;
const int rele_pump = 6;     //defining port of water pump 
const int dry_limit = 80;    //defining percentual of soil dryness
int humidity_sensor1 = 0;    //defining percentual of humidity maped by sensors
int humidity_sensor2 = 0;
const int watering_time = 10000;   //10 seconds of watering

void setup() { //defining I/O ports
  Serial.begin(9600);
  pinMode(rele_valve1, OUTPUT);
  pinMode(rele_valve2, OUTPUT);
  pinMode(rele_pump, OUTPUT);
  pinMode(water_level, INPUT);
}

void loop() { //main loop of the system
  humidity_sensor1=map(analogRead(soil_sensor1), 0, 1023, 0, 100); //maping the humidity measured by the sensors to percentual
  humidity_sensor2=map(analogRead(soil_sensor2), 0, 1023, 0, 100);

  while (digitalRead(water_level) == LOW) { // if cistern water level is low turns on the water pump
    digitalWrite(rele_pump, HIGH);
  }
  if (digitalRead(water_level) == HIGH ) { // turns off the water pump
    digitalWrite(rele_pump, LOW);
  }
  if (humidity_sensor1 < dry_limit || humidity_sensor2 < dry_limit) { //turns on the solenoid valve if sensor points to a dry soil
    if (humidity_sensor1 < dry_limit) { 
      digitalWrite(rele_valve1, HIGH);
  }
    if (humidity_sensor2 < dry_limit) {
      digitalWrite(rele_valve2, HIGH);
  }

  delay(watering_time);  //waits for 10 sec of watering
  digitalWrite(rele_valve1, LOW); //turns off the valve
  digitalWrite(rele_valve2, LOW);
  }
    
  delay(15000); // waits to repeat the cicle (15 sec for tests)
}