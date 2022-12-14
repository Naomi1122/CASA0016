# CASA0016 DIY indoor air quality monitor

## Motivation

According to statistics, people spend more than 90% of their time indoors. Unlike outdoors, there are stations to give out air quality data, we have to measure the air quality indoors by ourselves. By knowing the data of the air quality we can then proceed actions to improve the air quality, for example, open the windows and open air humidifier.

The deterioration of the outdoor environment and the uneven quality of interior decoration especially newlly built ones have brought about more and more serious indoor pollution problems, which have adversely affected the physical and mental health of residential residents, cause diseases such as respiratory diseases. Our UCL East site and my studio is a good example as it's newly built therefore it's good for monitoring.

## Aim

The aim for this project is to collect all the parameters of indoor air quality in real time which are Indoor PM1.0, PM2.5, PM10 concentration, CO2 concentration, TVOC concentration, temperature and humidity. The value of each parameter is measured every 30 seconds and displayed on the LCD screen. Furthermore, for each parameter, a suitable value/range is set. If actual measured value within the value/range, the Neopixel LED is used to indicate by show green LEDs, if exceed, the LEDs change to different colours.


## Construction of the physical prototype sensor

| Hardware | Description |
| --- | --- |
| Arduino Uno | Useful libraries and has 5v and 3.3v for multiple use |
| DHT22 | Sensor for temperature and humidity |
| SGP30 | a digital multi-pixel gas sensor outputs equivalent CO2 in ppm and Total Volatile Organic Compounds (TVOC) in ppb |
| T6713 CO2 sensor | latest generation of compact non‐dispersive infrared (NDIR) carbon dioxide sensors |
| PMS5003 | digital and universal particle concentration sensor, which can be used to obtain the number of suspended particles in the air, i.e. the concentration of particles |
| Neopixel | 8 RGB LED light bulbs |
| LCD HD44780 16x2 | display digitals to visualise the data |


### Detailed assembly

#### Pin connection

| Hardware | Pin | Pin | Pin | Pin | Pin|
| --- | --- | --- | --- | --- | --- |
| DHT22 | GND | VCC | DAT -> pin7|
| SGP30 | GND | VCC | SDA | SCL |
| T6713 CO2 sensor | GND | GND | VCC | SDA | SCL |
| PMS5003 | GND | VCC | TX -> 2 | RX -> 3 |
| Neopixel | GND | VCC | DAT -> 2 |
| LCD HD44780 16x2 | GND | VCC | SDA | SCL |

Female headers are soldered into copper stripboard for extension of the pins.
![3691671012518_ pic](https://user-images.githubusercontent.com/78373920/207567884-369e55c7-f75c-40a2-a964-f65a3deef746.jpg)

LCD Display
![3731671012649_ pic](https://user-images.githubusercontent.com/78373920/207567647-e5d4b9df-1ba7-4569-95e0-0da03de65e97.jpg)
![3661671012507_ pic](https://user-images.githubusercontent.com/78373920/207567648-c38c4f09-3ce7-4c56-a9ad-704266f7ca8d.jpg)

#### Outer Case

I used 3d printer to print the LCD holder and neopixel holder, and attached those two on the top of the sensor container.



The sensor container is made from a plastic box as I don't have time to 3d print a suitable case for now. I have punched holes on the plastic box so that the sensors are able to sense the air outside and the power wires are able to reach out.



## Result displayed photos

#### DHT22 Humidity and Temperature
The comfortable humidity for the human body is 30%-60%, therefore, if the humidity in the room is out of the range, blue LEDs showed on the neopixel, if not, green LEDs shows.
![3701671012518_ pic](https://user-images.githubusercontent.com/78373920/207567974-dc191776-676c-4ba2-873a-3b206c4b270a.jpg)


#### SGP30 CO2 and TVOC
Volatile organic compounds (VOCs) are a group of compounds with high vapor pressure and low water solubility. In other words, these substances won’t easily bind to themselves (volatile) or dissolve in water (organic). VOCs are emitted as gasses from everyday products such as building materials, maintenance equipment, and custodial products. Many VOCs are harmful to human health, especially over the long term. 
![3721671012521_ pic](https://user-images.githubusercontent.com/78373920/207568090-1ffab4bd-dd2a-4b22-bfb6-26e073099dbd.jpg)

For a good safety level of CO2 and TVOC, the level is set to CO2 < 1000 ppm and TVOC < 220 ppb accroding to FItwel's Enhanced Indoor Air Quality Testing and Monitoring Protocol. If the reading is out of range for either CO2 or TVOC, yellow LEDs showed, if not, green LEDs showed.


#### T6713 CO2
As we know from the principle of the SGP30 that it's not measure the actual CO2 in the air, but this sensor is. The CO2 value measured by T6713 is displayed on the LCD and the safety value is set to 1000 as well. If exceed, purple LEDs showed. I added this sensor with SGP30 as an indicator to test the accuracy of the SGP30 sensor, the accuracy is displayed on the LCD and if the accuracy is less than 85%, orange LEDs showed.
![3681671012515_ pic](https://user-images.githubusercontent.com/78373920/207568132-05273a8e-4720-457f-97da-82591a028832.jpg)

#### PMS5003
This sensor can outputs data as follow:
PM1.0, PM2.5 and PM10.0 concentration in both standard & environmental units
Particulate matter per 0.1L air, categorized by 0.3um, 0.5um, 1.0um, 2.5um, 5.0um and 10um sizes
![3711671012520_ pic](https://user-images.githubusercontent.com/78373920/207568038-1b0165b0-04e3-436d-9613-86d164851b6f.jpg)

For my project, I found that the standard units is the same as the environmental units for all PM1.0, PM2.5 and PM10.0 concentration, so I just diaplayed once on the LCD.
Then, I displayed particles smaller than 1.0um, 2.5um and 10um per 0.1L air. Set the range to 10um/0.1L <50 and 2.5um/0.1L <35, if exceed either condition, the LEDs goes to red, otherwise, green LEDs.

## Future Development
* Better outter cases
* uploaded through Lora to the Things network and to set alarm and visualise through phones.
