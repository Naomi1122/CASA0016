#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <PMS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <Adafruit_PM25AQI.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

//Define neopixel initialization
//Connect button pin as pin 12 on board
#define PIN 12
#define NUMPIXELS 8
#define DELAYVAL 500

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);


#define DHTPIN 7     // DHT connected to pin7
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define ADDR_6713  0x15 // default I2C slave address

SoftwareSerial pmSerial(2, 3); // pin #3 is TX pin on sensor), pin #2 RX
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float co2;
float tvoc;
int data [4];
int CO2ppmValue;
 
SGP30 mySensor; //create an object of the SGP30 class
LiquidCrystal_I2C lcd(0x27,16,2);
 
void setup() 
{
// Wait for serial monitor to open
  Serial.begin(9600);
  while (!Serial) delay(10);

  Serial.println("Adafruit PMSA003I Air Quality Sensor");

  // Wait one second for sensor to boot up!
  delay(1000);

  pmSerial.begin(9600);
  if (! aqi.begin_UART(&pmSerial)) { // connect to the sensor over software serial 
    Serial.println("Could not find PM 2.5 sensor!");
    while (1) delay(10);
  }

  Serial.println("PM25 found!");
 
  // sensor baud rate is 9600
  //Serial.begin(9600);
  Wire.begin();
  //Initialize sensor
  if (mySensor.begin() == false) 
{
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to initAirQuality
  mySensor.initAirQuality();
  dht.begin();
  pixels.begin();
  Serial.begin(9600);
  Serial.println("Application Note AN161_ardunio_T6713_I2C");
  //lcd.setCursor(0, 0);  
  //lcd.print("Hello");
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Air Quality");
  lcd.setCursor(5, 1);
  lcd.print("Sensor");
  delay(500);
}
 
void loop() 
{  
    delay(20000); //delay 20 seconds
    //print humidity and temperature
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: " + String(hum) + "%");
    lcd.setCursor(0, 1);
    lcd.print("Temp: " + String(temp) + " Cel");
    delay(500);

    pixels.clear();
  if(hum<30 || hum>60){
    //Serial.print("111");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 0, 25, 25);
    pixels.show();
    delay(DELAYVAL);
    }    
  }else{
    //Serial.print("222");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 0, 50, 0);
    pixels.show();
    delay(DELAYVAL);
    }
  }

  //First few readings will be CO2: 400 ppm  TVOC: 0 ppb
  delay(2000); //Wait 2 second
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();

  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO2: " + String(mySensor.CO2) + " ppm");
  lcd.setCursor(0, 1);
  lcd.print("TVOC: " + String(mySensor.TVOC) + " ppb");
  delay(500);

  pixels.clear();
  if(mySensor.CO2>1000 || mySensor.TVOC>220){
    //Serial.print("111");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 25, 25, 0);
    pixels.show();
    delay(DELAYVAL);
    }    
  }else{
    //Serial.print("222");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 0, 50, 0);
    pixels.show();
    delay(DELAYVAL);
    }
  }

  delay(2000);
  int co2Value =readC02();
  {
    Serial.print("T6713 CO2 : ");
    Serial.println(CO2ppmValue);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T6713 Sensor");
    lcd.setCursor(0, 1);
    lcd.print("CO2: " + String(CO2ppmValue) + " ppm");
    delay(500);

    pixels.clear();
    if(CO2ppmValue>1000){
      //Serial.print("111");
      for(int i=0; i<=NUMPIXELS;i++){
      //pixels.clear();
      pixels.setPixelColor(i, 25, 0, 25);
      pixels.show();
      delay(DELAYVAL);
      }    
    }else{
      //Serial.print("222");
      for(int i=0; i<=NUMPIXELS;i++){
      //pixels.clear();
      pixels.setPixelColor(i, 0, 50, 0);
      pixels.show();
      delay(DELAYVAL);
      }
    }
    }
  


  PM25_AQI_Data data;
  
  if (! aqi.read(&data)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
    return;
  }
  Serial.println("AQI reading success");

  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("Concentration Units (standard)"));
  Serial.println(F("---------------------------------------"));
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm10_standard);
  Serial.print(F("\t\tPM 2.5: ")); Serial.print(data.pm25_standard);
  Serial.print(F("\t\tPM 10: ")); Serial.println(data.pm100_standard);
  Serial.println(F("Concentration Units (environmental)"));
  Serial.println(F("---------------------------------------"));
  Serial.print(F("PM 1.0: ")); Serial.print(data.pm10_env);
  Serial.print(F("\t\tPM 2.5: ")); Serial.print(data.pm25_env);
  Serial.print(F("\t\tPM 10: ")); Serial.println(data.pm100_env);
  Serial.println(F("---------------------------------------"));

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PM1  PM2.5  PM10");
  lcd.setCursor(0,1);
  lcd.print(data.pm10_standard);
  lcd.setCursor(5,1);
  lcd.print(data.pm25_standard);
  lcd.setCursor(12,1);
  lcd.print(data.pm100_standard);
  delay(3000);
  
  //Serial.print(F("Particles > 0.3um / 0.1L air:")); Serial.println(data.particles_03um);
  //Serial.print(F("Particles > 0.5um / 0.1L air:")); Serial.println(data.particles_05um);
  Serial.print(F("Particles > 1.0um / 0.1L air:")); Serial.println(data.particles_10um);
  Serial.print(F("Particles > 2.5um / 0.1L air:")); Serial.println(data.particles_25um);
  //Serial.print(F("Particles > 5.0um / 0.1L air:")); Serial.println(data.particles_50um);
  Serial.print(F("Particles > 10 um / 0.1L air:")); Serial.println(data.particles_100um);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dust Concentra");
    lcd.setCursor(0, 1);
    lcd.print("PM1.0 :" + String(data.particles_10um) + " (ug/m3)");
    delay(500);

  Serial.println(F("---------------------------------------"));

  pixels.clear();
  if(data.particles_25um>35 || data.particles_100um>50){
    //Serial.print("111");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 50, 0, 0);
    pixels.show();
    delay(DELAYVAL);
    }    
  }else{
    //Serial.print("222");
    for(int i=0; i<=NUMPIXELS;i++){
    //pixels.clear();
    pixels.setPixelColor(i, 0, 50, 0);
    pixels.show();
    delay(DELAYVAL);
    }
  }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PM2.5 :" + String(data.particles_25um) + " (ug/m3)");
    lcd.setCursor(0, 1);
    lcd.print("PM10  :" + String(data.particles_100um) + " (ug/m3)");
    delay(500);

}
// Function : int readCO2()
// Returns : CO2 Value upon success, 0 upon checksum failure
// Assumes : - Wire library has been imported successfully.
// - LED is connected to IO pin 13
// - CO2 sensor address is defined in co2_addr
///////////////////////////////////////////////////////////////////

int readC02()
{
  // start I2C
  Wire.beginTransmission(ADDR_6713);
  Wire.write(0x04); Wire.write(0x13); Wire.write(0x8B); Wire.write(0x00); Wire.write(0x01);
  // end transmission
  Wire.endTransmission();
  // read report of current gas measurement in ppm
  delay(2000);
  Wire.requestFrom(ADDR_6713, 4);    // request 4 bytes from slave device
  data[0] = Wire.read();
  data[1] = Wire.read();
  data[2] = Wire.read();
  data[3] = Wire.read();
    Serial.print("Func code: "); Serial.print(data[0],HEX);
    Serial.print(" byte count: "); Serial.println(data[1],HEX);
    Serial.print("MSB: 0x");  Serial.print(data[2],HEX); Serial.print("  ");
    Serial.print("LSB: 0x");  Serial.print(data[3],HEX); Serial.print("  ");
   CO2ppmValue = ((data[2] * 0xFF ) + data[3]);
}
