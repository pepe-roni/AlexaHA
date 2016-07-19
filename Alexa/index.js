/**
 * App ID for the skill
 */
var APP_ID ="amzn1.echo-sdk-ams.app.48e38aaa-e6a4-40f1-8f3f-26b3c2567de5"; //replace with "amzn1.echo-sdk-ams.app.[your-unique-value-here]";

/**
 * The AlexaSkill prototype and helper functions
 */

var http = require('https');
var AlexaSkill = require('./AlexaSkill');

/*
 *
 * Particle is a child of AlexaSkill.
 *
 */
var Particle = function () {
    AlexaSkill.call(this, APP_ID);
};

// extend
Particle.prototype = Object.create(AlexaSkill.prototype);
Particle.prototype.constructor = Particle;

Particle.prototype.eventHandlers.onSessionStarted = function (sessionStartedRequest, session) {
    console.log("Particle onSessionStarted requestId: " + sessionStartedRequest.requestId + ", sessionId: " + session.sessionId);
};

Particle.prototype.eventHandlers.onLaunch = function (launchRequest, session, response) {
    console.log("Particle onLaunch requestId: " + launchRequest.requestId + ", sessionId: " + session.sessionId);
    var speechOutput = "17 percent of the time this app works 100 percent of the time.";
	
    response.ask(speechOutput);
};

Particle.prototype.eventHandlers.onSessionEnded = function (sessionEndedRequest, session) {
    console.log("Particle onSessionEnded requestId: " + sessionEndedRequest.requestId + ", sessionId: " + session.sessionId);
};

Particle.prototype.intentHandlers = {
    // register custom intent handlers
    ParticleIntent: function (intent, session, response) 
    {
    	
		var sensorSlot = intent.slots.sensor;
		var lightSlot = intent.slots.light;
		var onoffSlot = intent.slots.onoff;
	
		var sensor = sensorSlot ? intent.slots.sensor.value : "";
		var light = lightSlot ? intent.slots.light.value : "";
		var onoff = onoffSlot ? intent.slots.onoff.value : "off";
		
		
		var speakText = "";
		
		console.log("Sensor = " + sensor);
		console.log("Light = " + light);
		console.log("OnOff = " + onoff);
		
		var op = "";
		var pin = "";
		var pinvalue = "";
		
		// Replace these with action device id and access token
		var deviceid = "2d003b001947353236343033";
		var accessToken = "c52c2cffdc48a8b3a2b6847bd4b8102cbb078116";
		
		var sparkHst = "api.particle.io";
		
		console.log("Host = " + sparkHst);
		
		if(sensor == "moisture")
		{
			op = "getWater";
		}
		else 
		{
			//temporary handler
			op= "getWaterTwo";
		}
		/*
		// Check slots and call appropriate Particle Functions
		if(sensor == "temperature"){
			speakText = "Temperature is 69°";
			
			op = "gettmp";
		}
		else if(sensor == "humidity"){
			speakText = "Humidity is 75%";
			
			op = "gethmd";
		}
		else if(light == "red"){
			pin = "D2";
		}
		else if(light == "green"){
			pin = "D6";
		}
		*/
		// User is asking for temperature/pressure
		if(op.length > 0)
		{
			var sparkPath = "/v1/devices/" + deviceid + "/" + op;
			
			console.log("Path = " + sparkPath);
		
			makeParticleRequest(sparkHst, sparkPath, "", accessToken, function(resp)
			{
				var json = JSON.parse(resp);
				
				console.log(sensor + ": " + json.return_value);
				
				response.tellWithCard("soil sensor " + sensor + " has a moisture of " + json.return_value , "Particle", "Particle!");
			});
		}
		// User is asking to turn on/off lights
		else if(pin.length > 0){
			if(onoff == "on"){
				pinvalue = "HIGH";
			}
			else{
				pinvalue = "LOW";
			}
			
			var sparkPath = "/v1/devices/" + deviceid + "/ctrlled";
			
			console.log("Path = " + sparkPath);
			
			var args = pin + "," + pinvalue;
		 
			makeParticleRequest(sparkHst, sparkPath, args, accessToken, function(resp){
				var json = JSON.parse(resp);
				
				console.log("Temperature: " + json.return_value);
				
				response.tellWithCard("OK, " + light + " light turned " + onoff, "Particle", "Particle!");
				response.ask("Continue?");
			});
		}
		else{
			response.tell("Sorry, I could not understand what you said");
		}
    },
    HelpIntent: function (intent, session, response) 
    {
    	var rand = Math.floor((Math.random()*4)+1);
    	if(rand == 1)
        	response.ask("why don't you tell me why north korea exists huh?");
    	else if(rand == 2)
    		response.ask("kay mate");
    	else if(rand == 3)
    		response.ask("if you name is eric drink bleach");
    	else 
    		response.ask("get good");
    }
};

// Create the handler that responds to the Alexa Request.
exports.handler = function (event, context) {
    // Create an instance of the Particle skill.
    var particleSkill = new Particle();
    particleSkill.execute(event, context);
};

function makeParticleRequest(hname, urlPath, args, accessToken, callback){
	// Particle API parameters
	var options = {
		hostname: hname,
		port: 443,
		path: urlPath,
		method: 'POST',
		headers: {
			'Content-Type': 'application/x-www-form-urlencoded',
			'Accept': '*.*'
		}
	}
	
	var postData = "access_token=" + accessToken + "&" + "args=" + args;
	
	console.log("Post Data: " + postData);
	
	// Call Particle API
	var req = http.request(options, function(res) {
		console.log('STATUS: ' + res.statusCode);
		console.log('HEADERS: ' + JSON.stringify(res.headers));
		
		var body = "";
		
		res.setEncoding('utf8');
		res.on('data', function (chunk) {
			console.log('BODY: ' + chunk);
			
			body += chunk;
		});
		
		res.on('end', function () {
            callback(body);
        });
	});

	req.on('error', function(e) {
		console.log('problem with request: ' + e.message);
	});

	// write data to request body
	req.write(postData);
	req.end();
}