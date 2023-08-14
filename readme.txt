A cooling suit idea:

It needs a aluminium heat exhanger, that is connected to a cooling loop sewn into a spandex suit. The cooling loop is made of 
6 hoses in parallel, measuring 6 mm ØID x 9 mm ØOD, length 4 meters per hose. Total internal surface of the hoses is 4524.7 cm². External surface 6789.6 cm2. The heat exchanger as well as hoses and pump contain 3 liters of water. 

The aluminum heat exchanger has an internal surface of 681.41 square cm. 
It has a 10mm thick bottom, top and walls. It has connected 6 PVC hoses in parallel.

Thermal calculation: 
One cools 3 liters of water from 40 degrees to 18 degrees in 150 seconds. How much heat must be removed: Q = mc∆T m = 3 kg. specific heat capacity of water is 4.18 J/g°C. And we know that the temperature change of the water is 40 - 18 = 22 °C. 

So by entering these values into the formula we get: Q = 3 kg x 4.18 J/g°C x 22 °C Q = 2794.6 J 

This means that the heat exchanger removes 2794.6 joules of heat from the cooling loop in 150 seconds. 

P is required to remove this amount of heat using Peltier elements. We can use another formula: P = Q / t where P is the power in watts, Q is the heat transfer in joules, and t is the time in seconds. P = Q / t P = 2794.6 J / 150 s ≈ 18.6 watts 

However, this is not the actual effect the Peltier elements must have as a minimum, because they are not 100% efficient. In fact, they use more power than they pump, because some of the input power is converted into waste heat on both sides of the element. 

The COP can be calculated using a complex formula involving many parameters, or it can be obtained from a data sheet from the manufacturer of the Peltier element. 

For simplicity, let's assume we have a typical Peltier element with a COP of about 0.53. So, dividing watts by COP, we get: P / COP = 18.63 / 0.5 ≈ 37.2 W Since there are four Peltier elements in the heat exchanger, one can divide this power by four to get watts per element: P / COP / 4 = 37.26 / 4 ≈ 9.3 So each Peltier element needs about 9.31 watts to cool the cooling loop from 40°C to 18°C in 150 seconds. As the cooling loop is heated with 100W, you must have peltier elements with a minimum power of 150W in total. Those 100W are what a human body generates at maximum.
These calculations does not include cooling losses to the environment.

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
Say a peltier element pulls 8 Amps. To get Amp hours one just goes 8 X 6=48Ah. A 12 volt 48Ah LiFePo4 weights 5.5 kilos ( 12 lbs), and will keep you cool for 6 hours. LiFePo4 batteries are pretty safe, but the safest batteries are of the Lithium-titanate type. One can even get invidual cells, round or flat. 

One could put such a device inside a Stormtrooper suit and have one of those with a real, working cooling unit!
