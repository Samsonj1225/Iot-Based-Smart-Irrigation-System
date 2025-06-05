# Iot-Based-Smart-Irrigation-System

This project is a Smart Irrigation System built using a NodeMCU (ESP8266), Soil Moisture Sensor, and Submersible Pump, designed to automatically water plants based on real-time soil moisture data. It also sends notifications via Blynk and IFTTT, with voice alerts using the Shouter app. The system helps conserve water, provides remote control through the Blynk app, and delivers instant alerts when the soil is dry.

Hardware Components Used:
•	NodeMCU (ESP8266)
•	Soil Moisture Sensor
•	Relay Module
•	Submersible Pump
•	Jumper wires, Breadboard
•	Power source for pump

Steps for Blynk Setup:
1.	Go to https://blynk.cloud and create a free account.
2.	Create a new template and note down the Auth Token.
3.	Add two widgets to the dashboard:
o	Gauge (Virtual Pin V0) – to show moisture percentage.
o	Button (Virtual Pin V1) – to manually control the pump.
4.	Download the Blynk IoT app on your phone and log in to view and control the system.

Steps for IFTTT Webhook Setup:
1.	Visit https://ifttt.com and sign in.
2.	Click on “Create” to start a new applet.
3.	For the IF This part:
o	Choose Webhooks → Select Receive a web request
o	Name the event (e.g., plant_alert)
4.	For the Then That part:
o	Choose Notifications or SMS
o	Configure the message (e.g., "Soil moisture is low! Time to water the plants.")
5.	Click Finish.
6.	Go to https://ifttt.com/maker_webhooks → Click Documentation to get your IFTTT Key.
7.	Note down the Webhook URL:
http://maker.ifttt.com/trigger/plant_alert/with/key/YOUR_IFTTT_KEY

Steps for Shouter App Setup (Voice Notifications):
1.	Install Shouter App from the Google Play Store.
2.	Open the app and grant the necessary permissions.
3.	Enable Notification Reader.
4.	Turn on “App Notification Reading”.
5.	Select Blynk or your IFTTT/SMS app under the list of monitored apps.
6.	Customize how the app reads out the message (e.g., repeat, pitch, speed).
7.	Now, whenever an alert is triggered, Shouter will speak the alert message aloud.

Steps to Connect and Upload Code (Arduino IDE):
1.	Open Arduino IDE.
2.	Install the following libraries via Library Manager:
o	Blynk
o	ESP8266WiFi
o	BlynkSimpleEsp8266
o	ESP8266HTTPClient
3.	Go to Tools > Board and select NodeMCU 1.0 (ESP-12E Module).
4.	Select the correct COM Port under Tools > Port.
5.	Paste the provided code into a new sketch.
6.	Replace the placeholders:
o	auth[] → your Blynk Auth Token
o	ssid[] & pass[] → your Wi-Fi credentials
o	IFTTT_KEY → your IFTTT webhook key
o	eventName → event name (e.g., plant_alert)
7.	Upload the code to your NodeMCU.
8.	If the level drops below 30%, the pump is activated automatically.
9.	Simultaneously, an IFTTT alert is triggered, sending a notification to your phone.
10.	The Shouter app reads out the message loud.
11.	The moisture value is sent to Blynk and displayed live.
12.	You can also manually control the pump from Blynk's Button Widget .


