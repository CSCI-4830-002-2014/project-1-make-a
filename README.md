# Name
Niklas Fejes

# Hardware Photo
![image](image.jpg?raw=true)

# Data type
csv:
The data is stored as comma-separated values with three columns.
One with the time elapsed since startup (based on system clock),
one with the measured sound volume,
and one with the average analog input read.

# How did you get your prototype working?
To be able to find the serial port under Linux I had to run the Arduino software as root user.
To get the code to access the SD card I had to change the variable `chipSelect` from `4` to `8`.

# Arduino Code
filename: `sound_sensor_p1_v2.ino`
The code has been changed so that a new file is used every time the logging starts. The index is
replaced with the elapsed time since startup, and the `silent` is determined by the average read of
the previous measure.

# Data Sample
`data.csv`

This sample data is recorded over 24 hours. I plan to do a longer measurement from Thursday to Sunday, but wont be able to submit it
until Monday.

# How did you collect this data?
The data is the measured noise level from the parking lot outside my window, which I will try to use to determine at what time of the day 
the parking lot is the most active.

# What signal do you think is in your data?
I think there will be a signal that is periodic over 24 hours, that will have peaks at some specific times of the day.

# How fun was this mini-project? 
7

# How hard was it? 
5

# How much did you learn from the experience?
7
