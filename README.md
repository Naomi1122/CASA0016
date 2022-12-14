# CASA0016 DIY indoor air quality monitor

## Motivation

According to statistics, people spend more than 90% of their time indoors. Unlike outdoors, there are stations to give out air quality data, we have to measure the air quality indoors by ourselves. By knowing the data of the air quality we can then proceed actions to improve the air quality, for example, open the windows and open air humidifier.

The deterioration of the outdoor environment and the uneven quality of interior decoration especially newlly built ones have brought about more and more serious indoor pollution problems, which have adversely affected the physical and mental health of residential residents, cause diseases such as respiratory diseases. Our UCL East site is a good example as it's newly built therefore it's good for monitoring.

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


## Result displayed photos

#### DHT22 Humidity and Temperature
The comfortable humidity for the human body is 30%-60%, therefore, if the humidity in the room is out of the range, blue LEDs showed on the neopixel, if not, green LEDs shows.


#### SGP30 CO2 and TVOC
Volatile organic compounds (VOCs) are a group of compounds with high vapor pressure and low water solubility. In other words, these substances won’t easily bind to themselves (volatile) or dissolve in water (organic). VOCs are emitted as gasses from everyday products such as building materials, maintenance equipment, and custodial products. Many VOCs are harmful to human health, especially over the long term. 

For a good safety level of CO2 and TVOC, the level is set to CO2 < 1000 ppm and TVOC < 220 ppb accroding to FItwel's Enhanced Indoor Air Quality Testing and Monitoring Protocol. If the reading is out of range for either CO2 or TVOC, yellow LEDs showed, if not, green LEDs showed.


#### T6713 CO2
As we know from the principle of the 

