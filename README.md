# Data Structures Project - Weather Data Sensing Network

This project was done as part of the "Data Structures and Program Design - 2" course at at the Computer Science and Engineering Department of VNIT, Nagpur, India.

It implements AVL Trees as the data structure for recording information coming from environment sensors, which are to record weather data like humidity, wind speed, AQI, etc.
The project focuses on using AVL trees for the problem statements given as part of the course, rather than other areas of a whole project.

#### Note:

The code is not final - it may be updated later.   

##Gist of the problem statement

Sensors are spread across a city. An "AQI" sensor is a special sensor 
that records pollutant concentrations and assigns it an AQI based on ranges. According to national standards,
8 pollutants are measured and the highest corresponding AQI is taken as the overall AQI.
Data coming from sensors has to be recorded at some central repository of information. This "repo"
records the actual value, the date and time of the record, and the ID of the sensor that sent the
information. For the sake of simplicity, the same repository was used to track the (overall) AQI, but not 
which pollutant was the factor.

Appropriate AVL data structures were made for the above 3, i.e "Sensor" to store properties of a sensor,
"AQI Sensor", an adapted version for AQI, and a "Central repository" for the actual data tracking.

###Various functionalities were implemented on the above:

Apart from the standard addition, deletion, searching of the above records:
* Installing a sensor in-between stations.
* Removing idle sensors (that haven't reported data for long)
* Displaying information on days where "Hazardous" AQI status was recorded
* Searching central repository data based on some sensor information 

##Project files

* declrns.h: Contains all structure and function declarations
* declrns.c: Additional Date-time input/output function definitions.
* sensor.c: Functions related to sensor database. 
* repo.c: Functions related to central repository.
* AQI.c: Functions related to both AQI sensor database and AQI repository.
* main.c: Just the driver code needed to demonstrate the above.

##Command-line commands

**Compilation:** gcc main.c declrns.c sensor.c repo.c AQI.c -o main

**Running:** .\main
