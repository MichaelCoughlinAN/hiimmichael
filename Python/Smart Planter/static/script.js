// Michael Coughlin
// hiimmichael.com
// 2019 

/*
Declaring Variables:
*/
const getWeather = document.getElementById("getWeatherButton"),
			userInput = document.getElementById("userInput"),
			error = document.getElementById("error"),
			result = document.getElementById("results"),
			closeButtons = document.getElementsByClassName('close');

/*
Declaring Functions:
*/

// pairs buttons with parent to close on click
const pairCloseButtons = (elements) =>{
	for(let each of elements){
		each.onclick = function(){
			this.parentElement.style.display = "none";
		}
	}
} 

// show the error elements when there is an error
const showErrors = (element) => {
	for(let each of element){
		each.style.display = "block";
	}
}

// temp from openweathermap comes in K, 
// we need USA Units (deg. F)
const convertTemp = K => ((1.8*(K - 273)) + 32).toFixed(2);

// Converts from other time (uk in this case)
// to the local time (only hours change)
const convertTime = time => {
	let re = /(?:[01]\d|2[0123]):(?:[012345]\d):(?:[012345]\d)/g,
	 		h = `${new Date().getHours()}`,
	 		oH = re.exec(time)[0].split(':')[0];
			let newTime = time.replace(oH, h)
	return newTime
}

// To convert our city name to proper case
// regardless of how it is input:
String.prototype.toProperCase = function () {
    return this.replace(/\w\S*/g, function(txt){return txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase();});
};

// Api does it for us, but we should be extra sure and replace 
// whitespace in city names as %20
String.prototype.fixWhiteSpace = function(){
	return this.replace(/ /g, '%20');
}

window.onload=function(){
	pairCloseButtons(closeButtons);
	getWeatherData();
}

const getWeatherData = () =>{
	let publicKey = ``;
	let apiCall = `https://api.openweathermap.org/data/2.5/weather?zip=55111,us&APPID=${publicKey}`;

	fetch(apiCall).then(response => response.json())
	.catch(e => {console.log(e)})
		.then(data => {	 
			console.log(data.weather[0].main);
			
			switch (data.weather[0].main) {
          			case "Clouds":
          				document.getElementById('wicon').src = "/static/images/cloudy.png";
            				break;
          			case "Clear":
          				document.getElementById('wicon').src ="/static/images/sunny2.png";
            				break;
          			case "Thunderstorm":
          				document.getElementById('wicon').src = "/static/images/thunderstorm.png"            
          	    			break;
          			case "Drizzle":
             				document.getElementById('wicon').src = "/static/images/drizzle.png";
            				break;
          			case "Rain":
          				document.getElementById('wicon').src = "/static/images/rain.png";
            				break;
          			case "Mist":
          				document.getElementById('wicon').src = "/static/images/rain.png";
            				break;
          			case "Snow":
            				document.getElementById('wicon').src = "/static/images/snow.png";
            				break;
          			case "Extreme":
             				document.getElementById('wicon').src = "/static/images/warning.png";
            				break;
        	}
  			  			
       		document.getElementById("temp").innerHTML = (Math.round((1.8*(data.main.temp- 273)) + 32)) + ' &deg;F ' ;
	   		document.getElementById("expect").innerHTML =  data.weather[0].description;
  			document.getElementById("hi_and_lo").innerHTML =  (Math.round((1.8*(data.main.temp_max - 273)) + 32))  + ' / '  + (Math.round((1.8*(data.main.temp_min- 273)) + 32))  
  			document.getElementById("humidity").innerHTML =   'Humidity: '+ data.main.humidity + '%'; 
			document.getElementById("wind").innerHTML = 'Wind: ' + (Math.round(data.wind.speed * 2.237))  + ' mph';
			document.getElementById("clouds").innerHTML = 'Cloudiness: ' + data.clouds.all + '%';
  				   	   
        	var sunriseDt = new Date(data.sys.sunrise  * 1000); 	
        	var rise = (sunriseDt.getHours()>12?(sunriseDt.getHours()-12):sunriseDt.getHours()).toString() + ":" + ((sunriseDt.getMinutes() < 10 ? '0' : '').toString() + sunriseDt.getMinutes().toString()) + (sunriseDt.getHours() < 12 ? ' AM' : ' PM').toString();
  
        	var sunsetDt = new Date (data.sys.sunset  * 1000);
     		var sset = (sunsetDt.getHours()>12?(sunsetDt.getHours()-12):sunsetDt.getHours()).toString() + ":" + ((sunsetDt.getMinutes() < 10 ? '0' : '').toString() + sunsetDt.getMinutes().toString()) + (sunsetDt.getHours() < 12 ? ' AM' : ' PM').toString();
     
     		var updatedDt = new Date (data.dt * 1000);
     		var updated = (updatedDt.getHours()>12?(updatedDt.getHours()-12):updatedDt.getHours()).toString() + ":" + ((updatedDt.getMinutes() < 10 ? '0' : '').toString() + updatedDt.getMinutes().toString()) + (updatedDt.getHours() < 12 ? ' AM' : ' PM').toString();

		document.getElementById("sunrise").innerHTML = ' ' + rise;
		document.getElementById("sunset").innerHTML = ' ' + sset;
		document.getElementById("updated").innerHTML = ' Last updated: ' + updated;
	}).catch(e => {})}
