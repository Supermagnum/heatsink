A DIY cooling suit idea:
https://github.com/Supermagnum/heatsink/blob/main/Orlan_cooling_suit.JPG?raw=true
https://github.com/Supermagnum/heatsink/blob/main/WEB10864-2008h.jpg
Those are a cooling suits, used in the lowest layer on space suits.
It has hoses for circulation of cooling medium. 
A single layer of fabric may be used, with the tubing either on the inside directly contacting the wearer's skin, or on the outside separated by the fabric. If two layers of fabric are used, stitched channels can be formed which enclose the tubing between the two fabric layers. Where flame resistance is needed, the garment may be constructed out of materials such as nomex. 
If anyone has seen the apollo 13 movie, the boxes carried by  the astronauts on the way to the space capsule is a heat exhanger that provides cooling until the suits can be hooked up to the capsules internal cooling system.
That box also provides O2.

I think that NASA just used ice,battery and a pump in those boxes, and you need the capacity to at least transport 200W because the human body generates about 100W. One could rip out the heat exhanger from a car, the bit who heats air, make the suit out of spandex and sew in loops. A radiator for a CPU liquid cooler should be ideal.Hook that up to a aquarium pump or similar, and the heat exhanger/radiator that goes in a bucket of ice cubes and water. The pump will need to be able to flow around 4 liters per minute, and must run on 12V and accept PWM control.

The cooling loop is made of 
6 pvc hoses in parallel, measuring 6 mm ØID x 9 mm ØOD, length 4 meters per hose. Total internal surface of the hoses is 4524.7 cm². External surface 6789.6 cm2. The heat exchanger as well as hoses and pump contain 3 liters of water/glycol mix. 

Thermal calculation examples:
One cools 3 liters of water/glycol from 40 degrees to 18 degrees in 150 seconds.

How much heat must be removed:
Q = mc∆T
m = 3 kg.

specific heat capacity of water is 4.18 J/g°C, one liter of water is 1000 grams.

And we know that the temperature change of the water is 40 - 18 = 22 °C.

So by entering these values into the formula we get:
Q = 3 kg x 4180 J/kg°C x 22 °C Q = 275880 J

This means that the heat exchanger removes 275880 joules of heat from the cooling loop in 150 seconds.

To convert joules into watts= Joules/time in seconds.

Ice as a cooling medium for the coolant loop:

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

We know that the initial temperature of water is 40°C and it's being cooled to 0°C  in this case (assuming ice temperature). Solving for the mass (m):

m = Q / (c * ΔT)
m = 277320 J / (4.18 J/g°C * 40°C)
m ≈ 1658,6 g

Converting grams to kilograms:

m ≈ 1.658 kg

So, approximately 1.65 kilograms of ice (equivalent to the mass of water being cooled) would be needed to remove 1848.8 watts of energy from 3 liters of water/glycol mix at 40 degrees Celsius over a period of 150 seconds. 

It will take approximately 42.86 seconds to remove 275,880 joules of heat with a flow rate of 5 liters per minute.

Now, when the coolant has reached 18 degrees Celsius say we want to keep it at that temperature.

How one can calculate the amounts of ice needed per hour to keep the coolant liquid at 18 degrees Celsius if the ambient air temperature is 40 degrees Celsius:
First, we need to calculate the initial temperature difference between the water and the ambient air:

ΔT_initial = 40°C - 18°C = 22°C

Next, we calculate the heat transfer required to bring the water to its final temperature:

Q = m * c * ΔT_initial

Since we're interested in how much ice is needed to absorb this heat, we can also equate it to the heat absorbed by melting ice:

Q = m_ice * L_f

Where:
- m_ice is the mass of ice (in kilograms)
- L_f is the heat of fusion of ice (334,000 J/kg)

Combining the two equations:

m_ice * L_f = m * c * ΔT_initial

Solving for m_ice:

m_ice = (m * c * ΔT_initial) / L_f

Given that the density of water is approximately 1000 kg/m³, the mass of 3 liters of water is 3 kg.

m_ice = (3 kg * 4186 J/kg°C * 22°C) / 334000 J/kg ≈ 0,827 kg

So, approximately 0,827 kilograms ( 827 grams) of ice per hour would be needed to keep 3 liters of water at 18 degrees Celsius when the ambient air temperature is 40 degrees Celsius.
But, one needs to include that a human body generates maximum 100W of heat, so the mass of ice needed per hour is ≈ 2 kg
The flow rate for that is around 2.5 liters per minute.

Liquid to ice heat exhanger:
To extract 275,880 J of heat from water ice over 150 seconds using a 10 mm OD and 0.8 mm wall thickness copper tube with a temperature difference of 40 degrees Celsius and a convective heat transfer coefficient of 200 W/m²·K, the required length of the copper tube is approximately 7.32 meters. That is a inner surface of 1,848 square metres, and 2,198 square metres.

Keep in mind that these calculations assumes ideal heat transfer and doesn't consider other factors that might affect the cooling process, loss to the environment, heat exhanger loss and so on..

They also assumes that I haven't made any mathematical bloopers.

I suggest using Cold Gel Packs, Campingaz or similar brand as they supposedly lasts longer that ice cubes.

You can make something similar yourself:
https://m.youtube.com/watch?v=Nqxjfp4Gi0k
The heat capacity of the salts and water mixture is approximately 5451.5 J/°C.
In latent heat that is around 
3.39J/g°C.
The total weight of the mixture is 1695 grams. Be aware that it might expand slightly when frozen.
The heat capacity of 1695 grams of water ice is approximately 3543.55 J/°C.


Also,look at:
https://www.thermalcustompackaging.com/pcm/

The heat capacity of the 2 kg mixture is approximately 6432.92 J/°C.
The heat capacity of 2 kg of water ice is 4180 J/°C.
2 kilos of the mixture will last about 3 hours.
Much better than water ice.



How does one keep the temperature of the coolant at 18 degrees Celsius, 0 degrees coolant is uncomfortable!
There's also a risk of hyperthermia!

One can use a automotive NTC temperature sensor like this, and a arduino to control the temperature:
https://www.bosch-motorsport.com/content/downloads/Raceparts/Resources/pdf/Data%20sheet_70101387_Temperature_Sensor_NTC_M12.pdf
One then can monitor the temperature of the suits output and use PWM control to  control the speed of a pump.

Why water/glycol mix? So that the liquid in the coolant loop does not freeze or turn to slush in the heat exchanger.

Preliminary firmware for Arduino and the mentioned temperature sensor:
It has two switches, to adjust the coolant temperature between 15 degrees and 25 degrees Celsius in 5 degree steps.
One for up, one for down. 
I also has another switch to start the pump.
It has 2 relay outputs, one activates if the coolant temperature goes over 30 degrees Celsius for a set time. It can be used to activate a buzzer to signal out of ice.
It also puts out the wanted temperature, sensed temperature and current pump pwm to a 4 line lcd screen.
https://github.com/Supermagnum/heatsink/tree/main/firmware


### Required Hardware:
1. Arduino board (e.g., Arduino Uno)
2. NTC thermistor, Bosch M12.
3. Resistor (50k ohms)
4. 4-line LCD (compatible with LiquidCrystal library)
5. Three guarded stsp switches (for temperature up, temperature down, and relay control)
6. Pump controlled via PWM
7. Two relays,12V
8. Breadboard and connecting wire
9.3 10K resistors.
10. hose clamps.
11. Assorted size adapters and tube barbs.
12: optional small valves to control "zones".

### Connections:
- NTC thermistor and 50k resistor form a voltage divider.
- LCD connected to appropriate digital pins.
- Switches connected to digital pins with pull-down resistors.
- PWM pin connected to pump control input.
- Digital pins connected to relay control inputs.

### Notes:
1. **Debouncing**: The debounce logic ensures that button presses are not registered multiple times due to mechanical bounce.
2. **Temperature Calculation**: The resistance of the NTC is converted to a temperature value using a linear interpolation method between calibration points.
3. **PWM Control**: The PWM value is adjusted based on the difference between the target temperature and the read temperature, with a minimum PWM of 10%.
4. **LCD Display**: The LCD shows the target temperature, the read temperature, the current PWM value, and the state of the relay.


### Adjustments:
- Ensure that the LCD pin connections in the code match your actual connections.
- Modify pin numbers if you use different pins for buttons, relays, or the NTC sensor.
- If the NTC thermistor has different calibration values, adjust the `tempValues` and `resistanceValues` arrays accordingly.







