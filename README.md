#SK720 State Converter

Convert Skookum SK720(BE) LED states into distinct voltages for easy transfer via telemetry.
This way one can setup alarms etc. on the radio based on the different states of the SK720(BE).

#Manual
##SK720(BE) states

#Hardware

#Development setup

##Downloads
* Download Eclipse Arduino from http://eclipse.baeyens.it (v2.3)
* Download Arduino 1.6.1
* Download the ATtiny Arduino core from here http://highlowtech.org/?p=1695
* Download TinyDebugSerial Arduino library for debugging: https://github.com/jscrane/TinyDebugSerial

##Setup
* Merge the ATtiny core into 1.6.1 folder (until the eclipse arduino plugin works with this library out of the box)
* Setup avrdude for attiny:

Project properties -> C/C++ Build -> Environment

Change A.TOOLS.AVRDUDE.UPLOAD.PATTERN from:
"${A.CMD.PATH}" "-C${A.CONFIG.PATH}" ${A.UPLOAD.VERBOSE} -p${A.BUILD.MCU} -c${A.UPLOAD.PROTOCOL} -P${A.SERIAL.PORT} -b${A.UPLOAD.SPEED} -D "-Uflash:w:${A.BUILD.PATH}/${A.BUILD.PROJECT_NAME}.hex:i"

to:
"${A.CMD.PATH}" "-C${A.CONFIG.PATH}" ${A.UPLOAD.VERBOSE} -p${A.BUILD.MCU} -c${A.UPLOAD.PROTOCOL}  "-Uflash:w:${A.BUILD.PATH}/${A.BUILD.PROJECT_NAME}.hex:i"

Add variable
A.UPLOAD.PROTOCOL = usbtiny

