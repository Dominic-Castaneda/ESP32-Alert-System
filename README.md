Project Inspiration
While working as a host at Urban Air Adventure Park, I realized it was awkward to stand silently in the party room waiting for guests to need something. If I left to prepare food, wristbands, or retrieve something, guests would sometimes have to go looking for me. This made me think to create a wireless button system they could press to call me back when needed in a discreet, simple, and effective way.

Overview
This is a one-way communication system built using two ESP32 boards. When a button is pressed on the client-side board, it sends a signal to the server-side board, which triggers a buzzer and LED.

Hardware + Code
I used two ESP32 microcontrollers connected over Wi-Fi. The client has a push button that sends an HTTP request to the server. The server listens for incoming requests and activates a buzzer and LED when triggered. The code is written in C++ using the Arduino IDE.

Challenges
The biggest barrier was the physical design. I didn’t finish the CAD housing or battery mount to make the system portable and clean-looking. But in terms of functionality, the system worked exactly as intended, and I was proud to bring the concept to life despite limited resources.

What I Learned
I learned how to set up Wi-Fi communication between two ESP32s, use simple web servers to send signals, and manage pin logic and debounce buttons. It sparked my interest in building smarter environments with small, helpful tools.
