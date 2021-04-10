# ESP32_BLE_Mouse_AutoClicker
My 6 year old son asked for a sort of AutoClicker for his iPad. Some of his Roblox games just needed nonstop clicking on the screen.
This code uses an ESP32 which acts as a Bluetooth BLE mouse that can be paired with most PC, phone and tablets. When active, the ESP32 sends a click signal with a changeable delay. The click is centered on screen.

The build in LED toggles with the click speed.
When powered on, the ESP32 creates a Acess point with captive portal. By logging in to the AP (Password 12345678), a slider changes the click speed and saves it to memmory.
After 15 seconds without WiFi connected devices, WiFi is shut off and BLE in initiated, and awaits pairing.

In real life my son just needs to prepare the game on his iPad, he then turns the AutoClicker on, after ~1 minute they pair and the clicking starts. He stops the clicker by turning off the AutoClicker.

The code is fast and dirty, but works reliable.

In Arduino IDE Remember to set App to Large

# Dependencies
https://github.com/T-vK/ESP32-BLE-Mouse  nice simple BLE mouse usage
https://github.com/me-no-dev/ESPAsyncWebServer   I found this to generate the most stable captive portal for the ESP32
https://github.com/me-no-dev/AsyncTCP Used by ESPAsyncWebServer
