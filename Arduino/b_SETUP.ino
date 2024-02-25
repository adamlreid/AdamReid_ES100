void setup() {
  
  // Initialize serial monitor
  Serial.begin(9600);

  // Define pin modes for Trig, Echo pins
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // Script begin, pass to Python
  Serial.println("***"); 
  Serial.println(TRAFFIC_SPACE);
  Serial.println(IMAGE_COUNT);
  Serial.println(IMAGE_DELAY);
  Serial.println("***");

}
