# Force Measurement Using a (Cantilever) Load Cell

This repository can be found at:  
https://github.com/rlee32/arduino-tutorials/tree/master/load-cell  

## Description

This example uses a cantliever load cell for force measurement. 
It works by measuring the stretch of strain gauges attached to the surface of 
a bending beam. Assuming a linear relationship between the stretch and force 
applied allows us to estimate the magnitude of the force applied.  

The signal provided by the load cell must be amplified in order to be read 
accurately by the Arduino. According to the HX711 datasheet, there are a few 
programmable gain (signal multiplier) options: 128, 64, and 32. 
128 is the default and is what is used here.  

The HX711 Library was used. It can be installed from the Arduino IDE via 
'Sketch' > 'Manage Libraries...' and searching for the HX711 library. 
After installation, the appropriate header can be added via 
the 'Include Library...' popout menu.  

## Hardware

1. Arduino Uno  
2. Load cell: https://www.sparkfun.com/products/13329  
3. Load cell amplifier: https://www.sparkfun.com/products/13230  


