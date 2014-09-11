# Name
Niklas Fejes

# Hardware Photo
![image](image.jpg?raw=true)

# Data type
csv:
The data is stored as comma-separated values, with one column being the time elapsed since startup
(based on system clock) and the other being the measured sound volume.

# How did you get your prototype working?
To be able to find the serial port under Linux I had to run the Arduino software as root user. To get the code to access the SD card I had to change the variable `chipSelect` from `4` to `8`.

# Arduino Code
filename: `sound_sensor_p1_v2.ino`
The code has been changed so that a new file is used every time the logging starts. The index is
replaced with the elapsed time since startup.

# Data Sample
[Replace the sample data file in this repo with your data file, then put the name of your file here]

# How did you collect this data?
The data is the measured noise level from the parking lot outside my window, which I will try to use to determine at what time of the day it is most active.

# What signal do you think is in your data?
I think there will be a signal that is cyclic over 24 hours, that will have peaks at some specific times of the day.

# How fun was this mini-project? 
7

# How hard was it? 
5

# How much did you learn from the experience?
7
