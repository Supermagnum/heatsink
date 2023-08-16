A cooling suit idea:
https://github.com/Supermagnum/heatsink/blob/main/Orlan_cooling_suit.JPG?raw=true
That is a cooling suit, used in the lowest layer on space suits.
It has hoses for circulation of cooling medium. 
If anyone has seen the apollo 13 movie, the boxes carried by the astronauts on the way to the space capsule is a heat exhanger that provides cooling until the suits can be hooked up to the capsules internal cooling system.
That box also provides O2.

I think that NASA just used ice in those boxes, and you need the capacity to at least transport 200W because the human body generates about 100W. One could rip out the heat exhanger from a car, the bit who heats air, make the suit out of spandex and sew in loops. Hook that up to a aquarium pump or similar, and the heat exhanger that goes in a bucket of ice cubes and water. 

It needs a aluminium heat exhanger, that is connected to a cooling loop sewn into a spandex suit. The cooling loop is made of 
6 hoses in parallel, measuring 6 mm ØID x 9 mm ØOD, length 4 meters per hose. Total internal surface of the hoses is 4524.7 cm². External surface 6789.6 cm2. The heat exchanger as well as hoses and pump contain 3 liters of water/glycol mix. 

Thermal calculation:
One cools 3 liters of water/glycol from 40 degrees to 18 degrees in 150 seconds.

How much heat must be removed:
Q = mc∆T
m = 3 kg.

specific heat capacity of water is 4.18 J/g°C, one liter of water is 1000 grams.

And we know that the temperature change of the water is 40 - 18 = 22 °C.

So by entering these values into the formula we get:
Q = 3 kg x 4180 J/kg°C x 22 °C Q = 277,320 J

This means that the heat exchanger removes 277,320 joules of heat from the cooling loop in 150 seconds.

Peltier cooling;
P is required to remove this amount of heat using Peltier elements. We can use another formula: P = Q / t where P is the power in watts, Q is the heat transfer in joules, and t is the time in seconds.
P = Q / t P = 277,320 / 150 s ≈ 1848.8 watts

However, this is not the actual effect the Peltier elements must have as a minimum, because they are not 100% efficient. In fact, they use more power than they transmit, because some of the input power is converted into waste heat on both sides of the element.

The COP can be calculated using a complex formula involving many parameters, or it can be obtained from a data sheet from the manufacturer of the Peltier element. For simplicity, let's assume we have a typical Peltier element with a COP of about 0.53.
So, dividing watts by COP, we get: P / COP = 1848.8 / 0.5 ≈ 1848.8 W

Since there are four Peltier elements in the heat exchanger, one can divide this power by four to get watts per element:
P / COP / 4 = 1848.8 / 4 ≈ 462.2

So each Peltier element needs about 462.2 watts to cool down the cooling loop from 40°C to 18°C in 150 seconds.

As the cooling loop is heated with 100W, you must have peltier elements with a minimum power of a total of 562 W.
That is going to need some serious amount of power, the battery will be expensive, and  the  Peltier elements also.


How if one instead uses ice as a cooling medium for the coolant loop?

To calculate the amount of ice needed to remove 1848.8 watts of energy from 3 liters of water at 40 degrees Celsius over a period of 150 seconds, we can use the formula:

Q = P * t

Where:
Q = Heat energy (in Joules)
P = Power (in watts)
t = Time (in seconds)

Given that P = 1848.8 watts and t = 150 seconds, we can calculate Q:

Q = 1848.8 W * 150 s
Q = 277320 J

Now, let's use the specific heat capacity formula to determine the mass of water being cooled:

Q = m * c * ΔT

Where:
Q = Heat energy (in Joules) = 277320 J
m = Mass of the substance (in kilograms)
c = Specific heat capacity of water (approximately 4.18 J/g°C)
ΔT = Change in temperature (final temperature - initial temperature)

We know that the initial temperature of water is 40°C and it's being cooled to 0°C (assuming ice temperature). Solving for the mass (m):

m = Q / (c * ΔT)
m = 277320 J / (4.18 J/g°C * 40°C)
m ≈ 1656.63 g

Converting grams to kilograms:

m ≈ 1.65663 kg

So, approximately 1.66 kilograms of ice (equivalent to the mass of water being cooled) would be needed to remove 1848.8 watts of energy from 3 liters of water/glycol mix at 40 degrees Celsius over a period of 150 seconds. 

Now, when the coolant has reached 18 degrees Celsius say we want to keep it there for 4 hours as a example.

To calculate the amount of ice needed, we can use the formula:(Q = m \c \Delta T),
where:
(Q) is the heat absorbed by the ice (in Joules),
(m) is the mass of the ice (in kilograms),(c) is the specific heat capacity of ice (about 2.09 J/g°C),
(\Delta T) is the temperature change (in °C).

Given that the temperature change is from 0°C to -18°C, we have (\Delta T = -18°C - 0°C = -18°C).

The heat (Q) absorbed by the ice is also given by:
(Q = P \cdot t),where:(P) is the power (100W),(t) is the time (4 hours, which is 14,400 seconds).

So, around 4 kilos of ice is needed.

Keep in mind that this calculation assumes ideal heat transfer and doesn't consider other factors that might affect the cooling process, loss to the environment, heat exhanger loss and so on..


How does one keep the temperature of the coolant at 18 degrees Celsius?

One can use a automotive NTC temperature sensor like this, and a arduino to control the temperature:
https://www.bosch-motorsport.com/content/downloads/Raceparts/Resources/pdf/Data%20sheet_70101387_Temperature_Sensor_NTC_M12.pdf
One then can monitor the temperature of the suits output and use PWM control to  control the speed of a pump.


Why water/glycol mix? So that the liquid in the coolant loop does not freeze or turn to slush in the heat exchanger.





