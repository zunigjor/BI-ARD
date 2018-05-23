
/**
 * @file ARD_semestralni_prace.ino
 * @author Jorge Zuniga
 *
 * @brief Arduino automatic garden watering system project.
 *
 */
/**
 * Include files 
 */
#include "DHT.h"
/**
 * \defgroup const Constants
 * @{
 * @brief PINS connected to Arduino UNO
 */
// output
#define RED 13          ///< red RGB led PIN definition
#define GREEN 12        ///< green RGB led PIN definition
#define BLUE 11         ///< blue RGB led PIN definition
#define VALVEOPEN 10    ///< valve open PIN definition
#define VALVECLOSE 9    ///< valve close PIN definition
#define SOILDATA A0     ///< soil moisture meter PIN definition
#define TEMPDATA 5      ///< therometer PIN definition
/**@}*/
/**
 * \defgroup vars Global variables
 * @{
 * @brief Time from Arduino initialization in milisecons 
 */
unsigned long long int dataTime = 0;  ///< Time for measuring data
unsigned long long int soilTime = 0;  ///< Time for measuring soil moisture
DHT myDHT(TEMPDATA, DHT22);           ///< Thermometer/Air hum. sensor initioalization 
/**@}*/

/**
 * \defgroup fn Functions
 * @{
 * @brief Functions
 *
 *  This group contains all functions definitions
 */
/**
 * @brief Reads soil moisture
 * @retval int percentage of soil moisture, 0 = dry, 100 = wet
 */
int readSoilMoisture(){
  int x = analogRead(SOILDATA);
  x = map(x, 0, 1023, 100, 0);
  return x;
}
/**
 * @brief Reads light sensor data
 * @retval int percentage of humidity
 */
int readAirHum(){
  int x = myDHT.readHumidity();
  return x;
}
/**
 * @brief Reads light sensor data
 * @retval int temperature in C
 */
int readTemp(){
  int x = myDHT.readTemperature();
  return x;
}
/**
 * @brief Opens valve
 */
void openValve(){
  digitalWrite(VALVEOPEN, HIGH);
  digitalWrite(VALVECLOSE, LOW);
}
/**
 * @brief Closes valve
 */
void closeValve(){
  digitalWrite(VALVECLOSE, HIGH);
  digitalWrite(VALVEOPEN, LOW);
}
/**
 * @brief Turns ON BLUE led
 */
void blueON(){
 digitalWrite(BLUE,HIGH); 
}
/**
 * @brief Turns OFF BLUE led
 */
void blueOFF(){
 digitalWrite(BLUE,LOW); 
}
/**
 * @brief Turns ON GREEN led
 */
void greenON(){
 digitalWrite(GREEN,HIGH); 
}
/**
 * @brief Turns OFF GREEN led
 */
void greenOFF(){
 digitalWrite(GREEN,LOW); 
}
/**
 * @brief Prints weather data
 */
void printData(){
  int temp   = readTemp();
  int airHum = readAirHum();
  Serial.print("Temperature:   ");
  Serial.print(temp);
  Serial.print(" C\n");
  Serial.print("Air humidity:  ");
  Serial.print(airHum);
  Serial.print(" %\n");
}
/**
 * @brief Checks soil moisure, if under 40%, opens valve for 2 minutes
 */
void checkMoisture(){
  int soilMoisture = readSoilMoisture();
  Serial.print("Soil moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" %\n");
  if (soilMoisture < 40){               // if soil moisture is under 40%
    openValve();
    blueON();
    //delay(120000);                      // water on for 2 minutes -- 120000
    closeValve();
    blueOFF();
  }
}
/**@}*/
/**
* \defgroup base_fn Base functions
 * @{
 */
/**
 * @brief Initialize Arduino
 *
 */
void setup() {
  Serial.begin(9600);
  myDHT.begin();
  // OUTPUT
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(VALVEOPEN,OUTPUT);
  pinMode(VALVECLOSE,OUTPUT);
  // INPUT
  pinMode(SOILDATA, INPUT);
  pinMode(TEMPDATA, INPUT);
  closeValve();
}
/**
 * @brief Repeating code
 *
 */
void loop() {
  unsigned long long int thisTime = millis();
  if ( thisTime - soilTime > 3600000 ){      // check garden soil moisture every hour -- 3600000
    soilTime = thisTime;
    checkMoisture();
  }
  if ( thisTime - dataTime > 300000 ){        // print weather data every 5 minutes -- 300000
    dataTime = thisTime;
    greenON();
    printData();
    greenOFF();
  }
}
/**@}*/
