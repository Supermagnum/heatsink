Hello. I have dyscalculia, so maths is very difficult for me. That's why I have this question:

A heat exchanger draws heat out of a cooling loop flowing 20 liters per minute, the initial temperature of the water is 40 degrees Celsius. The cooling loop itself is not modeled in the attached link, but it is made of 6x 4 meter long pipes in parallel, each pipe has a diameter of 10mm. Total volume of coolant: 72 liters. The pipes are made of PVC with 10 mm ØID x 13 mm ØOD. 
The cooling loop is heated by 100W.
The heat exhanger has space for 4x  peltier elements that measures 40x40mm to draw heat out and into a perfect, infinite heat sink. The heat exhanger is made of aluminium, and has a internal surface of: 681.41square cm.
Elapsed time is 150 seconds. The cooling loop liquid temperature at the end of elapsed time is 18 degrees Celsius
The ambient temperature is 40 degrees Celsius.
What is the required amount of watt per peltier element?

The temperature drop across the heat exhanger may also be of interest to me.

Stl files and blueprints:
https://github.com/Supermagnum/heatsink

what it will be used for:

https://github.com/Supermagnum/heatsink/blob/main/Orlan_cooling_suit.JPG?raw=true

That is a cooling suit, used in the lowest layer on space suits.
It has hoses for circulation of cooling medium. 
If anyone has seen the apollo 13 movie, the boxes carried by the astronauts on the way to the space capsule is a heat exhanger that provides cooling until the suits can be hooked up to the capsules internal cooling system.
That box also provides O2.
I think that NASA just used ice water in those boxes, and you need the capacity to at least transport 200W because the human body generates about 100W. One could rip out the heat exhanger from a car, the bit who heats air, make the suit out of spandex and sew in 7 parallel loops. Hook that up to a aquarium pump or similar, and the heat exhanger that goes in a bucket of ice cubes and water. 

The issue with that is that the ice will melt,  and a ac compressor doesn't work if it is turned sideways.
Peltier elements is solid state,and the way to go.
They can be PWM controlled.

One could implement a PID loop to control the peltiers, and PWM control for the coolant pump, maybe combined with one or two temperature sensors in the coolant suit loop.
Theres no mention of the current draw, but say it pulls 8 Amps. To get Amp hours one just goes 8 X 6=48Ah. A 12 volt 48Ah LiFePo4 weights 5.5 kilos ( 12 lbs), and will keep you cool for 6 hours. LiFePo4 batteries are pretty safe, but the safest batteries are of the Lithium-titanate type. One can even get invidual cells, round or flat. One could put such a device inside a Stormtrooper suit and have one of those with a real, working cooling unit!
