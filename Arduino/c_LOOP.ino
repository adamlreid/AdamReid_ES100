// Operates traffic detection and air measurement logic
// Both occur simultaneously, at defined intervals, without interference

void loop() {

  unsigned long currentTime = millis();

  // Check if trafficDetect() returns true
  if (trafficDetect()) {
    // Reset all counters, interval
    lastTrafficDetect = currentTime; // Record time of traffic detect
    lastAirReport = currentTime; // Record time of air report
    firstInterval = 0;
    secondInterval = 0;
    thirdInterval = 0;
    delay(TRAFFIC_SPACE);
  }


  // First condition makes sure air data isn't being read more often than each defined interval space
  // Second condition determines whether enough air reads have occured to move on to the next interval
  
  if ((currentTime - lastAirReport >= FIRST_DELAY) && (firstInterval < FIRST_COUNT )) {
    airReport();
    firstInterval++;
    lastAirReport = currentTime;
    
  } else if ((currentTime - lastAirReport >= SECOND_DELAY) && (secondInterval < SECOND_COUNT )) {
    airReport();
    secondInterval++;
    lastAirReport = currentTime;
    
  } else if (currentTime - lastAirReport >= THIRD_DELAY) {
    thirdInterval++;
    lastAirReport = currentTime;
    if (thirdInterval == 2) { // Sketch doesn't like 60 second intervals so two 30 second ones instead
      airReport();
      thirdInterval = 0;
      lastAirReport = currentTime;
    }
  }

}
