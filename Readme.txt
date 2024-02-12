Battery Charge/Discharge and Heater Controller for small electric vehicles.

This system provides Battery telemetry services such as Voltage, Current, and Temperature. 

It also regulates charge/discharge voltages, limits current when battery temps are too high or too low, controls a battery heater for cold environments, and basic cooling fan control.
Works with lithium ion batteries, but does not provide cell ballancing. That must be done with a dedicated BMS.
The circuit provided should handle up to 30 amps with proper cooling. It also does basic error logging and will shut down the system on events such as under/over voltage, over current, temps out of range, internal CPU errors, etc. with room to expand.

At this time, Feb 19, 2022, Testing and verifying operation of circuit and firmware. System seems to be working as intended, but I'm still working on features and a few bugs here and there.

Heater circuit needs a higher current inductor to prevent smoke release.

Output side MOSFET drive circuit needs some fine tuning for effecientcy, but otherwise works and has been tested up to 1300 watts a few times on a 15min ride.

Charge circuit seems to work as intended, but all relays need bigger start capacitors, or better start circuits to succesfully latch.

Firmware needs display and monitoring routines written and reimplemented, and needs refactoring of several routines such as but not limited to the regulation routine for the purpose of saving code space, speed, and readability.