// Includes
#include <Adafruit_PM25AQI.h>
#include <Adafruit_I2CDevice.h>
#include <math.h>

// Declarations for airMeasure():
Adafruit_PM25AQI aqi = Adafruit_PM25AQI(); // Adafruit PMS5003 byte conversion

#define SAMPLE_SIZE 20 // Number of particle matter samples

const int REPORT_DELAY = 750; // Delay in-between PMS5003 readings (ms)
const int ROWS = 2; // Number of sensors
int fillCount = 0; // Counts how many times array filled
int particles_03um[ROWS][SAMPLE_SIZE];
int particles_05um[ROWS][SAMPLE_SIZE];
int particles_10um[ROWS][SAMPLE_SIZE];
int particles_25um[ROWS][SAMPLE_SIZE];
int particles_50um[ROWS][SAMPLE_SIZE];
int particles_100um[ROWS][SAMPLE_SIZE];
int pm10_env[ROWS][SAMPLE_SIZE];
int pm25_env[ROWS][SAMPLE_SIZE];
int pm100_env[ROWS][SAMPLE_SIZE];


// Declarations for sensorCalibrate():
float particles_03um_mean;
float particles_05um_mean;
float particles_10um_mean;
float particles_25um_mean;
float particles_50um_mean;
float particles_100um_mean;
float pm10_env_mean;
float pm25_env_mean;
float pm100_env_mean;



void airMeasure();
void sensorCalibrate();
void dataSend();
float getMean(int* data, int length);



void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  Serial.println("Calibration has begun");

}


void loop(){

  airMeasure();
  
}
