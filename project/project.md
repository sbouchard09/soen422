# SOEN 422 Group Project

Contributors: Scott Bouchard, Batoul (Betty) Afsharimoghadam  

Arduino code (in C++) controls the motors; there are two Arduino Nanos connected to the BeagleBone Black which, when a signal is received, will either stop or start the motors on its side (left or right) to drive the robot. 
  
BeagleBone code (in Python); receives data from one of three sensors (one on either side of the robot and one at the front) for the robot to be able to detect where it is, whether it needs to stop or continue going and if it's stopped, which direction to turn. Sends a signal to the Arduino Nanos based on the data received from the sensors.
