// Function to calibrate 0.3 micron particle readings

void liveCalibrate() {

  const int T_SCORE = 1.98; // 95% confidence, two-tailed, 120 DOF
  extern int particles_03um[ROWS][SAMPLE_SIZE];
  float mean[ROWS];
  float stdDev[ROWS];
  float pooledStdDev;
  
  // Calculate data associated with both samples
  for (int i = 0; i < ROWS; i++) {
    mean[i] = getMean(particles_03um[i], SAMPLE_SIZE); // Both sample means
    stdDev[i] = getStdDev(particles_03um[i], SAMPLE_SIZE, mean[i]); // Both sample standard deviations
  }
  
  // Calculate pooled standard deviation (same sample size)
  
  pooledStdDev = sqrt( ( (stdDev[0]*stdDev[0]) + (stdDev[1]*stdDev[1]) ) / 2);
  
  
  // Calculate confidence interval
  float errorMargin = T_SCORE * pooledStdDev * sqrt(1.0/SAMPLE_SIZE + 1.0/SAMPLE_SIZE);
  float lowerBound = (mean[0] - mean[1]) - errorMargin;
  float upperBound = (mean[0] - mean[1]) + errorMargin;
  
  // Calibrate if 0 is outside the confidence interval - multiplier
  if ((lowerBound < 0 && upperBound < 0) || (lowerBound > 0 && upperBound > 0)) {

    if ((upperBound < (-1) * pooledStdDev * 3) || (lowerBound > pooledStdDev * 3)) {
      Serial.println("Time to replace sensor");
      
    } else {
    Serial.println("Sensors calibrated");
    int averageMean = ((mean[0] + mean[1]) / 2);
    multiOne = averageMean / mean[0];
    Serial.println(multiOne);
    multiTwo = averageMean / mean[1];
    Serial.println(multiTwo);

    }
    
  } else {

    Serial.println("All sensors good");
    Serial.println(multiOne);
    Serial.println(multiTwo);
  }
  
}
