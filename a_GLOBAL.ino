// Includes
#include <Adafruit_PM25AQI.h> // These libraries from Adafruit convert the byte values outputted by the 
#include <Adafruit_I2CDevice.h> // PM sensors into integer values corresponding to PM counts
#include <dht.h>
#include <math.h>

#define SAMPLE_SIZE 61 // Number of 0.3um particle samples
#define DHT11_PIN 7


// Declarations for void loop():
unsigned long lastTrafficDetect = 0;  // Time when trafficDetect() last returned true
unsigned long lastAirReport = 0;  // Time when action() was last called
const int FIRST_DELAY = 2700; // First delay between traffic detect and air reports
const int SECOND_DELAY = 17000; // Second delay between air reports
const int THIRD_DELAY = 28500; // Third delay between air reports, until next traffic read
const int FIRST_COUNT = 1; // Number of air reports for first delay
const int SECOND_COUNT = 6; // Number of air reports for second delay
int firstInterval = 0; // Initialize counter for first interval
int secondInterval = 0; // Initialize counter for second interval
int thirdInterval = 0; // Initialize counter for third interval
const int IMAGE_COUNT = 5; // Image count to be passed to Python
const float IMAGE_DELAY = 0.02; // Image delay to be passed to Python


// Declarations for trafficDetect():
int Trig = 8; // Trig Pin (HC-SR04)
int Echo = 9; // Echo Pin (HC-SR04)
long duration, mm; // Current sensor distance (microseconds/mm)
const int THRES_HIGH = 2000; // Max distance to car (mm)
const int THRES_LOW = 1000; // Min distance to car (mm)
const int REQ_COUNT = 3; // Counter of times to measure over threshold
const int TRAFFIC_SPACE = 500; // Expected minimum spacing between cars (ms)
const int DETECT_DELAY = 50; // Delay in-between HC-SR04 readings (ms)
int successCount = 0; // Successful measurement counter


// Declarations for airReport():
Adafruit_PM25AQI aqi = Adafruit_PM25AQI(); // Adafruit PMS5003 byte conversion
dht DHT; // DHT11 sensor data conversion
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
int temperature[SAMPLE_SIZE];
int humidity[SAMPLE_SIZE];


// Declarations for liveCalibrate();
float multiOne = 1.0;
float multiTwo = 1.0;


// Declare functions
bool trafficDetect();
void airReport();
void liveCalibrate();
void resetReport();
float getMean(int* data, int length);
float getStdDev(int* data, int length, float mean);
