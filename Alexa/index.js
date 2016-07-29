/**
 * App ID for the skill
 */
var APP_ID = //replace with "amzn1.echo-sdk-ams.app.[your-unique-value-here]";

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
    var speechOutput = "....skynet active..";
	
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
		var deviceSlot = intent.slots.device;
		var onoffSlot = intent.slots.onoff;
	
		var sensor = sensorSlot ? intent.slots.sensor.value : "";
		var device = deviceSlot ? intent.slots.device.value : "";
		var onoff = onoffSlot ? intent.slots.onoff.value : "off";
		var speakText = "";
		
		console.log("Sensor = " + sensor);
		console.log("Device = " + device);
		console.log("OnOff = " + onoff);
		
		var op = "";
		var pin = "";
		var pinvalue = "";
		
		// Replace these with action device id and access token
		var deviceid = "deviceid";
		var accessToken = "accessToken";
		
		var sparkHst = "api.particle.io";
		
		console.log("Host = " + sparkHst);
		
		// Check slots and call appropriate Particle Functions
		if(sensor == "moisture"){
			speakText = "moisture is 2800";
			op = "getWater";
		}
		else if(sensor == "door"){
			speakText = "door is open";
			op = "getDoor";
		}
		else if(device == "blinds")
		{
			pin = "D2";
		}

		// User is asking for temperature/pressure
		if(op.length &gt; 0)
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
		else if(pin.length &gt; 0){
			if(onoff == "open")
			{
				pinvalue = "";
			}
			else
			{
				pinvalue = "c";
			}
			
			var sparkPath = "/v1/devices/" + deviceid + "/servoHandle"+ pinvalue ;
			console.log("Path = " + sparkPath);
			var args =pinvalue;
		 
			makeParticleRequest(sparkHst, sparkPath, args, accessToken, function(resp){
				var json = JSON.parse(resp);
				
				console.log("Temperature: " + json.return_value);
				response.tellWithCard("OK, " + blinds +" are "+ onoff, "Particle", "Particle!");
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
    	//if(rand == 1)
    	response.ask("k");

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
	
	var postData = "access_token=" + accessToken + "&amp;" + "args=" + args;
	
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
