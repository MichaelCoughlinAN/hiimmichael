# Michael Coughlin
# hiimmichael.com
# Copywrite @ 2019

from flask import Flask, render_template, jsonify
from threading import Lock, Thread
import RPi.GPIO as GPIO
import threading
import atexit
import time
import logging
from datetime import datetime, timedelta
import os.path
import pyowm
from dateutil import parser, tz
import pytz


# Initialize logging
def init_logging():
	global version
	logging.basicConfig(format = '%(asctime)s %(message)s', datefmt = '%m/%d/%Y %I:%M:%S %p', filename = 'log.txt', level=logging.DEBUG)	
	logging.info('Starting Smart Ladder ' + version)


# Called on script exit event
def on_close():
	turn_off_all_gpio()
	GPIO.cleanup()
	
	print 'So long and thanks for all the fish!'


def write_date_to_file(days_between_waterings):
	present = datetime.now(pytz.utc) + timedelta(days=days_between_waterings)
	with open("date.txt", mode='w') as file:
		file.write(str(present))
			
#######################################################################
## Flask Web Server ######################################################	
#######################################################################

app = Flask(__name__)


@app.route('/')
def index():	
	global is_grow_light_on
	return render_template('index.html', light=is_grow_light_on, water=is_water_pump_on, auto=is_plant_sitter_mode_on)  

  
@app.route('/log')
def log():
	with open("log.txt", "r") as log:
		array = []
		
		for line in reversed(open("log.txt").readlines()):
				array.append(line)
    
    	return render_template('log.html',output=array)
    
    
@app.route('/water', methods=["GET", "POST"])
def pump_web_request():
	global is_water_pump_on,  pump_lock
	
	pump_on_time = 5
	
	pump_lock.acquire()
	is_water_pump_on = not is_water_pump_on
	pump_lock.release()
	
	if is_water_pump_on:
		Thread(target=turn_on_water_pump, args=(pump_on_time,)).start()
		blink_led_blue(pump_on_time)
			
	return jsonify({"is_water_pump_on": str(is_water_pump_on)})

def light_web_request_helper():
	global is_grow_light_on
	
	if is_grow_light_on:
		blink_button_led_green(2)
		turn_on_button_led_green()
	else:
		turn_off_button_led_green()


@app.route('/light', methods=["GET", "POST"])
def light_web_request():
	global is_grow_light_on, light_lock
		
	if not is_grow_light_button_pressed():
		light_lock.acquire()
		is_grow_light_on = not is_grow_light_on	
		light_lock.release()	
		
		Thread(target=light_web_request_helper).start()
		
		if is_grow_light_on:		
			turn_on_grow_lights()
		else:
			turn_off_grow_lights()
							
	return jsonify({"is_grow_light_on": str(is_grow_light_on)})


def auto_web_request_helper():
	global is_plant_sitter_mode_on		
	
	if is_plant_sitter_mode_on:
		blink_button_led_blue(2)
		turn_on_button_led_blue()
	else:
		turn_off_button_led_blue()


def start_plant_sitter():
	print 'Starting plant sitter'
	Thread(target=auto_grow_light_controller).start()
	Thread(target=auto_water_pump_controller).start()
	

def auto_grow_light_controller():
	global is_plant_sitter_mode_on, is_grow_light_on
	print 'Starting auto grow light controller thread'
	
	longitude = 44.986656
	latitude = -93.258133
	owm_api_key = ""
	
	owm = pyowm.OWM(owm_api_key)
	observation = owm.weather_at_coords(longitude, latitude)
	w = observation.get_weather()	
	
	from_zone = tz.gettz('UTC')
	to_zone = tz.gettz('America/Chicago')
	
	clouds = w.get_clouds()
	sunrise = (parser.parse(w.get_sunrise_time('iso')))	.replace(tzinfo=from_zone).astimezone(to_zone)
	sunset = (parser.parse(w.get_sunset_time('iso'))).replace(tzinfo=from_zone).astimezone(to_zone)
		
	present = datetime.now(pytz.utc)
	present = present.astimezone(to_zone)
			
	refresh_counter = 0
	refresh_limit = 60
	
	while is_plant_sitter_mode_on:	
		if refresh_counter == refresh_limit:
			refresh_counter = 0
			
			clouds = w.get_clouds()
			sunrise = (parser.parse(w.get_sunrise_time('iso')))	.replace(tzinfo=from_zone).astimezone(to_zone)
			sunset = (parser.parse(w.get_sunset_time('iso'))).replace(tzinfo=from_zone).astimezone(to_zone)
		
			present = datetime.now(pytz.utc)
			present = present.astimezone(to_zone)
	
			print 'Now ' + str(present)
			print 'Sunset is ' + str(sunset)
			print 'Sunrise is ' + str(sunrise)
			print 'Clouds ' + str(clouds)
	
		if present > sunrise and present < sunset:
			print 'It is daytime (Yay!)'
			
			if clouds > 50:
				if not is_grow_light_on:
					print 'It is cloudy, turning on grow lights!'
					is_grow_light_on = True
					turn_on_grow_lights()
			else:
				if is_grow_light_on and not is_grow_light_button_pressed():
					print 'It is not cloudy, turning off grow lights!'
					is_grow_light_on = False
					turn_off_grow_lights()
		else:
			if is_grow_light_on and not is_grow_light_button_pressed():
				print 'It is nighttime, no need for lights...'
				is_grow_light_on = False
				turn_off_grow_lights()
				
		refresh_counter = refresh_counter + 1
		time.sleep(1)
	
	print 'Auto Grow Light Controller Thread tuning out!'
	return
	
	
def auto_water_pump_controller():
	global is_plant_sitter_mode_on
	print 'Start auto water pump controller thread'
	
	from_zone = tz.gettz('UTC')
	to_zone = tz.gettz('America/Chicago')
	
	if os.path.exists('./date.txt'):
		f = open("date.txt", "r")
		next_time = (parser.parse(f.read())).replace(tzinfo=from_zone).astimezone(to_zone)
	else:
		turn_on_water_pump(5)
		write_date_to_file(7)
		f = open("date.txt", "r")
		next_time = (parser.parse(f.read())).replace(tzinfo=from_zone).astimezone(to_zone)
					
	while is_plant_sitter_mode_on:
		present = datetime.now(pytz.utc)
		present = present.astimezone(to_zone)
		
		if present > next_time:
			print 'Time to auto water!'
			turn_on_water_pump(5)
			write_date_to_file(7)
			f = open("date.txt", "r")
			next_time = (parser.parse(f.read())).replace(tzinfo=from_zone).astimezone(to_zone)
		else:
			print 'No need to water yet, next watering will occur on ' + str(next_time)
					
		time.sleep(1)
	
	print 'Auto Water Pump Controller Thread tuning out!'
	return
	
	
@app.route('/auto', methods=["GET", "POST"])
def auto_web_request():
	global is_plant_sitter_mode_on, sitter_lock
	
	if not is_plant_sitter_button_pressed():
		sitter_lock.acquire()
		is_plant_sitter_mode_on = not is_plant_sitter_mode_on
		
		if is_plant_sitter_mode_on:		
			Thread(target=auto_web_request_helper).start()	
			start_plant_sitter()
		else:
			turn_off_button_led_blue()

		sitter_lock.release()

	return jsonify({"is_sitter_mode_enabled": str(is_plant_sitter_mode_on)})

#######################################################################
## RASPBERRY PI GPIO ##################################################	
#######################################################################
	
def turn_on_blue_led():
	global blue_led_gpio	
	GPIO.output(blue_led_gpio, True)


def turn_off_blue_led():
	global blue_led_gpio	
	GPIO.output(blue_led_gpio, False)


def blink_led_blue(number_times, interval = 0.5):
	blink_counter = 0
	
	while blink_counter < number_times:
		turn_on_blue_led()
		time.sleep(interval)
		turn_off_blue_led()		
		time.sleep(interval)
		blink_counter = blink_counter + 1
		
			
def turn_on_button_led_blue():
	global plant_sitter_button_led_gpio	
	GPIO.output(plant_sitter_button_led_gpio, True)

		
def turn_off_button_led_blue():
	global plant_sitter_button_led_gpio	
	GPIO.output(plant_sitter_button_led_gpio, False)


def blink_button_led_blue(number_times, interval = 0.5):
	blink_counter = 0
	
	while blink_counter < number_times:
		turn_on_button_led_blue()
		time.sleep(interval)
		turn_off_button_led_blue()		
		time.sleep(interval)
		blink_counter = blink_counter + 1


def turn_on_button_led_green():
	global grow_light_button_led_gpio	
	GPIO.output(grow_light_button_led_gpio, True)

		
def turn_off_button_led_green():
	global grow_light_button_led_gpio	
	GPIO.output(grow_light_button_led_gpio, False)


def blink_button_led_green(number_times, interval = 0.5):
	blink_counter = 0
	
	while blink_counter < number_times:
		turn_on_button_led_green()
		time.sleep(interval)
		turn_off_button_led_green()		
		time.sleep(interval)
		blink_counter = blink_counter + 1

		
def turn_off_grow_lights():
	global grow_light_gpio	
	GPIO.output(grow_light_gpio, True)


def turn_on_grow_lights():
	global grow_light_gpio	
	GPIO.output(grow_light_gpio, False)

		
def turn_off_water_pump():
	global pump_gpio, is_water_pump_on,  pump_lock
		
	pump_lock.acquire()
	is_water_pump_on = False
	pump_lock.release()
		
	GPIO.output(pump_gpio, True)


def turn_on_water_pump(interval = 30):
	global pump_gpio	
	counter = 0
	
	GPIO.output(pump_gpio, False)
	
	while counter < interval:
		time.sleep(1) 
		counter = counter + 1
	
	turn_off_water_pump()
	
		
def turn_off_all_gpio():
	turn_off_water_pump()
	turn_off_grow_lights()
	turn_off_blue_led()
	turn_off_button_led_blue()
	turn_off_button_led_green()
	

# Poll GPIO Plant Sitter On/Off Button input for current state 		
def is_plant_sitter_button_pressed():
	global plant_sitter_button_gpio
	return GPIO.input(plant_sitter_button_gpio) == 1
	

# Poll GPIO Grow Light On/Off Button input for current state 		
def is_grow_light_button_pressed():
	global grow_light_button_gpio
	return GPIO.input(grow_light_button_gpio) == 1
	
	
# Setup Raspberry Pi GPIO mode and pins		
def init_rasp_pi_gpio():
	global pump_gpio, grow_light_gpio, plant_sitter_button_gpio, grow_light_button_gpio, grow_light_button_led_gpio, \
			   plant_sitter_button_led_gpio, blue_led_gpio
	
	print 'Initializing Raspberry GPIO'
		
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BCM)
	
	GPIO.setup(blue_led_gpio, GPIO.OUT)
	GPIO.setup(plant_sitter_button_led_gpio, GPIO.OUT) 
	GPIO.setup(grow_light_button_led_gpio, GPIO.OUT)
	GPIO.setup(grow_light_gpio, GPIO.OUT)
	GPIO.setup(pump_gpio, GPIO.OUT)
	GPIO.setup(plant_sitter_button_gpio, GPIO.IN, pull_up_down=GPIO.PUD_UP)
	GPIO.setup(grow_light_button_gpio, GPIO.IN, pull_up_down=GPIO.PUD_UP)
		
	turn_off_all_gpio()
					    	
#######################################################################
## GPIO Button Listener  ##################################################	
#######################################################################
		
def ladder_controller():
	global is_grow_light_on, is_plant_sitter_mode_on, \
			   light_lock, sitter_lock
	
	is_plant_sitter_mode_on_prev = False
	is_grow_light_on_prev = False
	
	try:
		blink_led_blue(3)
	
		while True:
			# User has pressed Plant Sitter Mode Button
			if is_plant_sitter_button_pressed() and not is_plant_sitter_mode_on:
				sitter_lock.acquire()
				print 'Plant Sitter Mode On'								
				is_plant_sitter_mode_on = True
				is_plant_sitter_mode_on_prev = True
				turn_on_button_led_blue()
				time.sleep(0.5)
				sitter_lock.release()
				
			# User has un-pressed Plant Sitter Mode Button			
			elif not is_plant_sitter_button_pressed() and is_plant_sitter_mode_on_prev:
				sitter_lock.acquire()
				print 'Plant Sitter Mode Off'			
				is_plant_sitter_mode_on_prev = False
				is_plant_sitter_mode_on = False		
				turn_off_button_led_blue()
				time.sleep(0.5)
				sitter_lock.release()
						
			# User has pressed Grow Light Button
			if is_grow_light_button_pressed() and not is_grow_light_on:
				light_lock.acquire()
				print ' Grow Light On'
				is_grow_light_on = True
				is_grow_light_on_prev = True
				turn_on_button_led_green()
				turn_on_grow_lights()
				time.sleep(0.5)
				light_lock.release()
				
			# User has un-pressed Grow Light Button			
			elif not is_grow_light_button_pressed() and is_grow_light_on_prev:
				light_lock.acquire()
				print ' Grow Light Off'
				is_grow_light_on = False
				is_grow_light_on_prev = False
				turn_off_button_led_green()
				turn_off_grow_lights()
				time.sleep(0.5)
				light_lock.release()
			
			time.sleep(1)
		
	except (KeyboardInterrupt, SystemExit):
		on_close()
	
#######################################################################
## Main  ###############################################################	
#######################################################################
		
def main():
	global is_grow_light_on, is_water_pump_on, is_plant_sitter_mode_on, is_overwater_protection_active,  \
			   pump_gpio, grow_light_gpio, plant_sitter_button_gpio, grow_light_button_gpio, grow_light_button_led_gpio, \
			   plant_sitter_button_led_gpio, blue_led_gpio, light_lock, pump_lock, sitter_lock, overwater_lock, version
          
	version = '1.0.0'
	init_logging()
	atexit.register(on_close)

	# Locks for thread synchronization
	light_lock = Lock()
	pump_lock = Lock()
	sitter_lock = Lock()
	overwater_lock = Lock()
	
	# Raspberry Pi GPIO pins 
	pump_gpio = 17 
	plant_sitter_button_gpio = 13
	plant_sitter_button_led_gpio = 26
	grow_light_gpio = 27
	grow_light_button_gpio = 04
	grow_light_button_led_gpio  = 19
	blue_led_gpio = 05
	
	# Booleans - represent state of buttons on index.html 
	is_grow_light_on = False
	is_water_pump_on = False
	is_plant_sitter_mode_on = False	
	is_overwater_protection_active = False
	
	init_rasp_pi_gpio()
	
	# Start GPIO button listener thread 
	ladder_controller_thread = threading.Thread(target=ladder_controller)
	ladder_controller_thread.daemon = True
	ladder_controller_thread.start()
	
	# Start Flask Web Server
	app.run(debug=True, host='0.0.0.0', port=80)


if __name__ == '__main__':
	main()    	
