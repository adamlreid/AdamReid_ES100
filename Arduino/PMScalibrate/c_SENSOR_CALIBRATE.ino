// Based on airReport() function:

void sensorCalibrate() {

  // Calculate mean for calibration sampling (every minute)
  particles_03um_mean = (getMean(particles_03um[0], SAMPLE_SIZE) + getMean(particles_03um[1], SAMPLE_SIZE)) / 2; // Average samples from both sensors
  particles_05um_mean = (getMean(particles_05um[0], SAMPLE_SIZE) + getMean(particles_05um[1], SAMPLE_SIZE)) / 2;
  particles_10um_mean = (getMean(particles_10um[0], SAMPLE_SIZE) + getMean(particles_10um[1], SAMPLE_SIZE)) / 2;
  particles_25um_mean = (getMean(particles_25um[0], SAMPLE_SIZE) + getMean(particles_25um[1], SAMPLE_SIZE)) / 2;
  particles_50um_mean = (getMean(particles_50um[0], SAMPLE_SIZE) + getMean(particles_50um[1], SAMPLE_SIZE)) / 2; 
  particles_100um_mean = (getMean(particles_100um[0], SAMPLE_SIZE) + getMean(particles_100um[1], SAMPLE_SIZE)) / 2;
  pm10_env_mean = (getMean(pm10_env[0], SAMPLE_SIZE) + getMean(pm10_env[1], SAMPLE_SIZE)) / 2;
  pm25_env_mean = (getMean(pm25_env[0], SAMPLE_SIZE) + getMean(pm25_env[1], SAMPLE_SIZE)) / 2;
  pm100_env_mean = (getMean(pm100_env[0], SAMPLE_SIZE) + getMean(pm100_env[1], SAMPLE_SIZE)) / 2;

  Serial.print("PMdata:");

  Serial.print(particles_03um_mean); Serial.print(";");
  Serial.print(particles_05um_mean); Serial.print(";");
  Serial.print(particles_10um_mean); Serial.print(";");
  Serial.print(particles_25um_mean); Serial.print(";");
  Serial.print(particles_50um_mean); Serial.print(";");
  Serial.print(particles_100um_mean); Serial.print(";");
  Serial.print(pm10_env_mean); Serial.print(";");
  Serial.print(pm25_env_mean); Serial.print(";");
  Serial.print(pm100_env_mean); Serial.println(";");
  

  Serial.print("0.3um/0.1L: "); Serial.println(particles_03um_mean);
  
  Serial.print("0.5um/0.1L: "); Serial.println(particles_05um_mean);
  
  Serial.print("1.0um/0.1L: "); Serial.println(particles_10um_mean);
  
  Serial.print("2.5um/0.1L: "); Serial.println(particles_25um_mean);
  
  Serial.print("5.0um/0.1L: "); Serial.println(particles_50um_mean);
  
  Serial.print("10um/0.1L: "); Serial.println(particles_100um_mean);
  
  Serial.print("PM 1.0: "); Serial.println(pm10_env_mean);
  
  Serial.print("PM 2.5: "); Serial.println(pm25_env_mean);
   
  Serial.print("PM 10: "); Serial.println(pm100_env_mean);



  // Reset all mean data
  particles_03um_mean = 0;
  particles_05um_mean = 0;
  particles_10um_mean = 0;
  particles_25um_mean = 0;
  particles_50um_mean = 0; 
  particles_100um_mean = 0;
  pm10_env_mean = 0;
  pm25_env_mean = 0;
  pm100_env_mean = 0;

}


float getMean(int* data, int length) {
  float sum = 0;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  return sum / length;
}
