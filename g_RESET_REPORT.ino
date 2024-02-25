// Function to package and reset air data arrays

void resetReport() {

  float particles_03um_mean;
  float particles_05um_mean;
  float particles_10um_mean;
  float particles_25um_mean;
  float particles_50um_mean;
  float particles_100um_mean;
  float pm10_env_mean;
  float pm25_env_mean;
  float pm100_env_mean;
  
  float particles_03um_stdDev;
  float particles_05um_stdDev;
  float particles_10um_stdDev;
  float particles_25um_stdDev;
  float particles_50um_stdDev;
  float particles_100um_stdDev;
  float pm10_env_stdDev;
  float pm25_env_stdDev;
  float pm100_env_stdDev;
  
  float temperature_mean;
  float humidity_mean;
  
  float temperature_stdDev;
  float humidity_stdDev;


  // Average first sensor data, find standard deviation, use multiplier
    
  particles_03um_mean = getMean(particles_03um[0], SAMPLE_SIZE) * multiOne;
  particles_05um_mean = getMean(particles_05um[0], SAMPLE_SIZE) * multiOne;
  particles_10um_mean = getMean(particles_10um[0], SAMPLE_SIZE) * multiOne;
  particles_25um_mean = getMean(particles_25um[0], SAMPLE_SIZE) * multiOne;
  particles_50um_mean = getMean(particles_50um[0], SAMPLE_SIZE) * multiOne;
  particles_100um_mean = getMean(particles_100um[0], SAMPLE_SIZE) * multiOne;
  pm10_env_mean = getMean(pm10_env[0], SAMPLE_SIZE) * multiOne;
  pm25_env_mean = getMean(pm25_env[0], SAMPLE_SIZE) * multiOne;
  pm100_env_mean = getMean(pm100_env[0], SAMPLE_SIZE) * multiOne;

  particles_03um_stdDev = getStdDev(particles_03um[0], SAMPLE_SIZE, particles_03um_mean);
  particles_05um_stdDev = getStdDev(particles_05um[0], SAMPLE_SIZE, particles_05um_mean);
  particles_10um_stdDev = getStdDev(particles_10um[0], SAMPLE_SIZE, particles_10um_mean);
  particles_25um_stdDev = getStdDev(particles_25um[0], SAMPLE_SIZE, particles_25um_mean);
  particles_50um_stdDev = getStdDev(particles_50um[0], SAMPLE_SIZE, particles_50um_mean);
  particles_100um_stdDev = getStdDev(particles_100um[0], SAMPLE_SIZE, particles_100um_mean);
  pm10_env_stdDev = getStdDev(pm10_env[0], SAMPLE_SIZE, pm10_env_mean);
  pm25_env_stdDev = getStdDev(pm25_env[0], SAMPLE_SIZE, pm25_env_mean);
  pm100_env_stdDev = getStdDev(pm100_env[0], SAMPLE_SIZE, pm100_env_mean);

  temperature_mean = getMean(temperature, SAMPLE_SIZE);
  humidity_mean = getMean(humidity, SAMPLE_SIZE);

  temperature_stdDev = getStdDev(temperature, SAMPLE_SIZE, temperature_mean);
  humidity_stdDev = getStdDev(humidity, SAMPLE_SIZE, humidity_mean);
  
  // Print sensor 1 data to serial

  Serial.println("Summary:");

  Serial.print("0.3um/0.1L: "); Serial.print(particles_03um_mean);
  Serial.print("; "); Serial.println(particles_03um_stdDev);
  
  Serial.print("0.5um/0.1L: "); Serial.print(particles_05um_mean);
  Serial.print("; "); Serial.println(particles_05um_stdDev);
  
  Serial.print("1.0um/0.1L: "); Serial.print(particles_10um_mean);
  Serial.print("; "); Serial.println(particles_10um_stdDev);
  
  Serial.print("2.5um/0.1L: "); Serial.print(particles_25um_mean);
  Serial.print("; "); Serial.println(particles_25um_stdDev); 
  
  Serial.print("5.0um/0.1L: "); Serial.print(particles_50um_mean);
  Serial.print("; "); Serial.println(particles_50um_stdDev);
  
  Serial.print("10um/0.1L: "); Serial.print(particles_100um_mean);
  Serial.print("; "); Serial.println(particles_100um_stdDev); 
  
  Serial.print("PM 1.0: "); Serial.print(pm10_env_mean);
  Serial.print("; "); Serial.println(pm10_env_stdDev); 
  
  Serial.print("PM 2.5: "); Serial.print(pm25_env_mean);
  Serial.print("; "); Serial.println(pm25_env_stdDev);
   
  Serial.print("PM 10: "); Serial.print(pm100_env_mean);
  Serial.print("; "); Serial.println(pm100_env_stdDev);  

  Serial.print("Temperature: "); Serial.print(temperature_mean);
  Serial.print("; "); Serial.println(temperature_stdDev);

  Serial.print("Humidity: "); Serial.print(humidity_mean);
  Serial.print("; "); Serial.println(humidity_stdDev);

    

  // Reset the data
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < SAMPLE_SIZE; j++) {
      particles_03um[i][j] = 0;
      particles_05um[i][j] = 0;
      particles_10um[i][j] = 0;
      particles_25um[i][j] = 0;
      particles_50um[i][j] = 0;
      particles_100um[i][j] = 0;
      pm10_env[i][j] = 0;
      pm25_env[i][j] = 0;
      pm100_env[i][j] = 0;

      temperature[j] = 0;
      humidity[j] = 0;
    }
  }
}

float getMean(int* data, int length) {
  float sum = 0;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  return sum / length;
}

float getStdDev(int* data, int length, float mean) {
  float variance = 0;
  for (int i = 0; i < length; i++) {
    variance += pow(data[i] - mean, 2);
  }
  variance /= length;
  return sqrt(variance);
}
