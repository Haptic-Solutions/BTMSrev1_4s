Open Source Universal Battery Controller
Test battery is 4S Lithium Ion Pack
16.8V 2.6Ah rated. 38.48Wh Nominal
Please note that this device is a prototype and all features are still being extensively tested, some features aren't fully implement, and others are awaiting further polishing. Please excuse our mess as we continue to develop this system, it's documentation, and source/design repository.
Watch your step! The workshop is messy. ;)

	Though, this pack is worn out a bit as these are recycled cells. No worries though, as this BMS, Charger, and Power Management System will measure, and account for performance variations between batteries and chemistry types. Features include, but are not limited to:

    • BUCK-BOOST charge input to accommodate a wide range of battery configurations and supports charge voltage inputs from 5v-25v
    • USB-PD and USB2.0 charge to support a wide range of USB chargers up to 100watt.
    • AUX CHARGE PORT for solar applications
    • 2S, 3S, OR 4S support via jumper on the cell inputs
    • POWER SWITCH MODES ranging from push-and-hold, to automatic power on when charger power disconnected
    • FULL ACCESS to a wide range of settings such as cell max voltage and current
    • REDUNDANT SAFETY SYSTEMS not just in firmware but in hardware via over-voltage detection, shutdown, and disabling once any cell reaches 4.3v
    • ERROR REPORTING and TELEMETRY in a simple to access single letter command set via built-in USB serial or AUX UART header accessed by a terminal emulator
    • LCD SUPPORT via UART output that is configurable
    • HEATER CONTROL for cold environments with board and battery temperature sensors

Specs:
    • 25V 5A max charge input
    • 18V 10A max battery output, 2s-4s configurations, max 4.3v/cell
    • Dual UART with one dedicated to USB FTDI
    • dsPIC30F4011 micro-controller ~14mips
    • C codebase
    • 0.015mA deep-sleep (diode leakage, we aim to improve this)

Stay tuned for developments. We've got a lot of ground to cover before we release this into the wild! Our goal is to help other hobbyists be safer with batteries while getting their max performance in a very wide range of supported applications and cell chemistry types!
Copyright (2024) Haptic Solutions Inc.