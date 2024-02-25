// Function to obtain air data readings
// Total runtime should be ~3000ms

void airReport() {

  // First check if air data arrays are full
  // Calibrate, save if true
  if (fillCount == SAMPLE_SIZE){
    liveCalibrate(); // Get new multipliers
    resetReport(); // Package, reset arrays
    fillCount = 0; // Reset fill count

  }

  // Byte conversion
  PM25_AQI_Data PMdata;

  // Initialize serial for first PMS5003 sensor
  Serial1.begin(9600);

  // Display warning if PMS5003 does not properly connect
  if (! aqi.begin_UART(&Serial1)) {
    Serial.println("Could not find PMS5003 #1");
    while (1) delay(10);
  }

  // Include delay at beginning so PMS5003 readings don't overlap
  delay(REPORT_DELAY);

  // PMS5003 begin
  Serial.println("PMS5003 sensor 1");

  // Display error if PM readings were unsuccessful
  if (! aqi.read(&PMdata)) {
    Serial.println("PMdata not found");
    delay(100);
  }

  // Fill values from first sensor incrementally
  particles_03um[0][fillCount] = PMdata.particles_03um * multiOne;
  particles_05um[0][fillCount] = PMdata.particles_05um * multiOne;
  particles_10um[0][fillCount] = PMdata.particles_10um * multiOne;
  particles_25um[0][fillCount] = PMdata.particles_25um * multiOne;
  particles_50um[0][fillCount] = PMdata.particles_50um * multiOne;
  particles_100um[0][fillCount] = PMdata.particles_100um * multiOne;
  pm10_env[0][fillCount] = PMdata.pm10_env * multiOne;
  pm25_env[0][fillCount] = PMdata.pm25_env * multiOne;
  pm100_env[0][fillCount] = PMdata.pm100_env * multiOne;

  // End delay so readings don't overlap
  delay(REPORT_DELAY);

  // Turn off first PMS5003 sensor
  Serial1.end();

  // Record temperature and humidity
  delay(50);
  int check = DHT.read11(DHT11_PIN);
  temperature[fillCount] = DHT.temperature;
  humidity[fillCount] = DHT.humidity;
  delay(50);

  // Initialize serial for second PMS5003 sensor
  Serial2.begin(9600);

  // Display warning if PMS5003 does not properly connect
  if (! aqi.begin_UART(&Serial2)) {
    Serial.println("Could not find PMS5003 #2");
    while (1) delay(10);
  }

  // Include delay at beginning so PMS5003 readings don't overlap
  delay(REPORT_DELAY);

  // PMS5003 begin
  Serial.println("PMS5003 sensor 2");

  // Display error if PM readings were unsuccessful
  if (! aqi.read(&PMdata)) {
    Serial.println("PMdata not found");
    delay(100);
  }

  // Fill values from second sensor incrementally
  particles_03um[1][fillCount] = PMdata.particles_03um * multiTwo;
  particles_05um[1][fillCount] = PMdata.particles_05um * multiTwo;
  particles_10um[1][fillCount] = PMdata.particles_10um * multiTwo;
  particles_25um[1][fillCount] = PMdata.particles_25um * multiTwo;
  particles_50um[1][fillCount] = PMdata.particles_50um * multiTwo;
  particles_100um[1][fillCount] = PMdata.particles_100um * multiTwo;
  pm10_env[1][fillCount] = PMdata.pm10_env * multiTwo;
  pm25_env[1][fillCount] = PMdata.pm25_env * multiTwo;
  pm100_env[1][fillCount] = PMdata.pm100_env * multiTwo;

  // End delay so readings don't overlap
  delay(REPORT_DELAY);

  // Turn off first PMS5003 sensor
  Serial2.end();

  // Update fill count
  fillCount++;
  Serial.println(fillCount);

}
