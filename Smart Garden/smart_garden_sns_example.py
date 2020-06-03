from boto3.session import Session, boto3
import datetime
import time

number = '+12024561111'
watering_threshold = 100
moisture_level = 0

            
try:
	if moisture <= watering_threshold:
   		sns = boto3.client('sns')
    	sns.publish(PhoneNumber = number, Message="I'm dryin' up! Please water me soon.")
       	time.sleep(0.5)
     	sns.publish(PhoneNumber = number, Message="garden.hiimmichael.com")
except Exception as e:
	success = False

