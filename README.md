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


