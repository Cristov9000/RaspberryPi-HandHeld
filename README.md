# SuperGameGirl
Hello Everyone!

Thank you for checking out my instructions on how to build your own SuperGameGirl. The SuperGameGirl is a Raspberry Pi powered handheld system that runs RetroPie giving you the ability to play games from the NES, SNES, Genesis, GameBoy, GameGear, Atari, Playstation, arcade games (MAME) and lots of other systems. In designing this handheld I made sure to include enough buttons for full Playstation emulation so there is a d-pad, start, select, A, B, X, Y, L1, R1, L2, and R2 buttons. The SuperGameGirl is powered by a 6000mAh LiPo battery that gives it around 7 hours battery life. The battery is rechargeable via microUSB on the bottom of the handheld with a status LED to showing charging and fully charged states. The power supply in the unit allows it to be charged while you are playing as well. A microcontroller distributes the power from the powersupply to the RaspberryPi, screen, amp, and other peripherals while ensuring that the Pi is shutdown properly when the switch its turned off. This is required to prevent SD card corruption and loosing your precious saved games! Using RetroPie allows the emulators to be quickly set-up, brings saving to systems that previously didn't have the ability to save games, allows the adding of games via USB and uses EmulationStation as a nice clean way to organize everything. If this sounds like fun, keep reading! The detailed instructions on how to assemble one can be found here:  https://imgur.com/a/gFhk7

Here you will find the .stl files that you will need to 3D print the case as well as the softwear that you will need to load onto the Pi and the ATTiny85.

****THE BOARDS ARE GOING BACK INTO PRODUCTION DUE TO AN INCREASE IN DEMAND.  PRE-ORDERS ARE OPEN!  I expect to have the boards in 4-5 weeks from 2/26/2016

One set of boards $28 including shipping and packaging to the lower 48 US states.
Each addition set of boards you want is $23.
Each Preprogrammed ATTiny85 shipped with the boards is $5
Shipping to Canada/Alaska/Hawaii add $3 to the total
Shipping to any other country that is not the USA or Canada add $5 to the total

Paypal to Cristov9000@gmail.com and please make sure your shipping address is included

For any questions do not hesitate to email me at Cristov9000@gmail.com

- 2/29/2016 - Another batch of boards were ordered.  I expect them in 25 days or less from today.  Boards are still available to order.
- 3/5/2016 - The boards are in production.  I expect them in 20 days or so.  There are still a few boards left in this batch available for order.

---------------------------------------------------------------------------------------------------------------------------------



Also, I am a mechanical engineer so I am always looking for coding and circuit recomendations from you software and EE people.  I would love to hear how to make this project better and more efficient!

Known Issues (I would love to hear a solution): 

1. On one unit there is a static/hum noise from the speaker at all times that the other unit doesn't have. I don't know why and figure out the difference. 

2. On one unit the display has some static on it, it doesn't effect the gameplay but you can see it if you are really looking for it and it is pissing me off. It is almost like the display is low on power. Maybe there is a little too much voltage drop across the MOSFET... I dunno 

3. I originally designed it to have the ATTiny run on 3.3V to make it easier to talk to the Pi and to save power (hence the second power supply) but I could not get it to switch the MOSFET and have the display still switch on and off with just 3.3V despite all data sheets saying it should work. Anyone know why? I turned it up to 5v and added a voltage divider to talk to the Pi and it works but probably not as efficiently as it should be.

Thank you everyone!
