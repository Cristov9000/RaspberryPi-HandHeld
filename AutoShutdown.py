#*************************************************************************
#
# autoshutdown.py  -  by: Chris Duerden
# Raspberry Pi safe shutdown program to interface with ATTiny85
# 9/8/2015      RevA - Initial Release
# 9/28/2015     RevB - removed ", pull_up_down = GPIO.PUD_UP" from input
#
# Function:  This program is designed to safely shut down a Raspberry Pi
# when a GPIO pin is brought low by a power management circuit
# 
#*************************************************************************

#Import
import RPi.GPIO as GPIO
import time
import os

#Setup
GPIO.setmode(GPIO.BCM) #Set Pin numbers to GPIO numbering  
GPIO.setup(18, GPIO.IN) #Set GPIO18 as input
GPIO.setup(23, GPIO.OUT, initial=GPIO.HIGH) #Set GPIO23 as constant output

#Define Program to shutdown RPi
def shutdown(pin):  
	os.system("sudo shutdown -h now")
	
#Setup Interrupt on GPIO18 when Grounded
GPIO.add_event_detect(18, GPIO.FALLING, callback = shutdown, bouncetime = 200)   

#Main
while 1:
        time.sleep(1) #Prevent Program for ending only
