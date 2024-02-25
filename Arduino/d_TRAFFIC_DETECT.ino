// Function for traffic detection

bool trafficDetect() {
    
  // Trigger HC-SR04 with HIGH pulse of at least 10 microseconds
  // Give short LOW pulse first to ensure clean HIGH pulse
  digitalWrite(Trig, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
 
  // HC-SR04 sends HIGH pulse; duration is time in microseconds
  // between ping send and echo receive from an object
  pinMode(Echo, INPUT);
  duration = pulseIn(Echo, HIGH);
 
  // Convert time (microseconds) to distance
  mm = (duration/2) / 2.91; // Divide by 2.91 or multiply by 0.343
  
  // Serial.println(mm); // Use for distance debugging

  // Check if distance meets threshold
  if (mm >= THRES_LOW && mm <= THRES_HIGH) {
    successCount++;
    // Send over serial "autoDetect" after required count met (likely car is present)
    if (successCount >= REQ_COUNT) {
      Serial.println("autoDetect");
      successCount = 0;
      return true;
    }
    // If condition not met, reset counter
  } else {     
    successCount = 0;
  }
  
  // Time delay in-between sensor readings
  delay(DETECT_DELAY);
  
  return false;

}
