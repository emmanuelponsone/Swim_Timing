# Swimming Races timing system
Timing project for Swimming Races

**Watch video of the system working on field:**

https://youtu.be/FMHkYDIDqnM


Complete development of software and hardware for a system designed to meet the precision timing requirements of the international swimming federation. 

The software development involved:
- Development of firmware in C for 1 master microcontroller and 8 slave microcontrollers (ARM LPC1343 - Cortex M3).
- The master microcontroller reads a high-frequency timebase which is then divided and distributed to the slaves for synchronization.
- The slave microcontrollers, one for each lane of the pool, receive the synchronization signal as an interrupt and measure the time between button presses at the ends of the pool. The time data is reported to the master microcontroller.
- The master microcontroller receives the data from the slaves and sends the data to a PC via USB port.

On the PC:
- The PC software is responsible for managing the database and runs on a web environment on a RAILS server.
- Development of software in Ruby on Rails to create and maintain the database and display information on a web browser.
- Creating new scenarios (pools, length of each lane, number of lanes, laps per competition)
- Managing swimmers (age, gender, category, time records for each swim style, etc.)
