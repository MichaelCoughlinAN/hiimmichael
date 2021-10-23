# Smart Planter
[View the complete guide on my website!](https://blog.hiimmichael.com/articles/smart-planter.html)

Smart Planter is an open-source, autonomous irrigation and lighting system designed and created by [Michael Coughlin](https://hiimmichael.com).

### Download the files

Smart Planter application files must be structured like below:

    /App
        /app.py
        /templates
            /index.html
            /log.html
        /static
            /ajax_handler.js
            /script.js
            /style.css
            /jquery.gradientify.min.js
            /images
                /cloudy.png
                /drizzle.png
                /rain.png
                /snow.png
                /sunny2.png
                /thunderstrong.png
                /warning.png
            

# Prerequisites 

I recommend installing [Raspbian](https://www.raspberrypi.org/documentation/installation/) onto your Raspberry Pi. 
Raspbian comes with [Python](https://www.codecademy.com/articles/install-python) installed by default.

### Flask

Flask is a lightweight web application framework. It is designed
to make getting started quick and easy, with the ability to scale up to
complex applications. 

### Installing Flask

Install and update using [pip](https://pypi.org/project/pip/):

    pip install -U Flask

### A Simple Example

    from flask import Flask

    app = Flask(__name__)

    @app.route("/")
    def hello():
        return "Hello, World!"

    $ env FLASK_APP=hello.py flask run
     * Serving Flask app "hello"
     * Running on http://127.0.0.1:5000/ (Press CTRL+C to quit)

# Launch

To start the Smart Planter program, navigate into your project directory and issue the following command:

    sudo python app.py

# Donate

* [Buy me a coffee](https://www.buymeacoffee.com/WKToIkLyV)
* [Patreon](https://www.patreon.com/hiimmichael)

