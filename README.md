# Trashck
<h2> Scheme and Circuit </h2>
<img src="https://github.com/mxy963/Trashck/blob/main/Photos/scheme.png">
<img src="https://github.com/mxy963/Trashck/blob/main/Photos/circuit.png"> 
<h2> Devices </h2>
<h3> Node Mcu </h3>
<img src="https://github.com/mxy963/Trashck/blob/main/Photos/mcu.png">
<h3> Ultrasonic Sensor </h3>
<img src="https://github.com/mxy963/Trashck/blob/main/Photos/ultrasonic.png">
<h3> Leds </h3>
<img src="https://github.com/mxy963/Trashck/blob/main/Photos/leds.png"> # Trashck: IoT Trash Bin Monitoring System

## Objective
To monitor the fill levels of trash bins to optimize cleaning services and achieve more efficient waste management.

## Technologies
- ESP8266 WiFi Module
- Ultrasonic Sensor (HC-SR04)
- NodeMCU
- mDNS
- Web Server

## Achievements
1. **Fill Level Monitoring:** The ultrasonic sensor measures the fill level of the trash bin and transmits this data to a web interface via the ESP8266 WiFi module.
2. **Real-Time Monitoring and Reporting:** The web server allows real-time monitoring of the trash bin's fill level. Users can view the fill status of the trash bin at [http://iot.local](http://iot.local).
3. **LED Indicator:** Visual indication of fill level with red and green LEDs. A red LED lights up when the fill level exceeds 70%, while a green LED lights up below this threshold.
4. **Easy Access:** User-friendly web interface displays the fill level as a percentage and uses colored icons, enabling waste management teams to make quick decisions.
5. **Increased Efficiency:** This system determines when trash bins need to be emptied, reducing unnecessary trips and fuel consumption, thus improving the efficiency of cleaning services.

## Project Description
This project aims to monitor the fill levels of trash bins using IoT technology. The ultrasonic sensor (HC-SR04) measures the distance inside the trash bin, and this data is transmitted to a web server via the ESP8266 module. The web server allows users to check the fill status of the trash bin from any device at any time. LED indicators provide visual alerts on-site, enabling quick response based on the fill level. This system makes trash collection operations more efficient and enhances environmental cleanliness.

## Photos
<h2> Scheme and Circuit </h2>
<p align="center">
  <img src="https://github.com/mxy963/Trashck/blob/main/Photos/scheme.png" width="300"/> 
  <img src="https://github.com/mxy963/Trashck/blob/main/Photos/circuit.png" width="300"/> 
</p>
<h2> Technologies </h2>
<p align="center">
  <img src="https://github.com/mxy963/Trashck/blob/main/Photos/NodeMCU.png" width="300"/> 
  <img src="https://github.com/mxy963/Trashck/blob/main/Photos/Ultrasonic.png" width="300"/> 
  <img src="https://github.com/mxy963/Trashck/blob/main/Photos/leds.png" width="300"/> 
</p>

 
## How to Use
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/trashck.git

