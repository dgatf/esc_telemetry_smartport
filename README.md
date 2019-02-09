# ESC RPM telemetry to Smartport

The PWM or digital signal from ESC can be sent to Smartport and sent to the receiver. An Arduino Nano can convert this signal to Smartport protocol (FrSky)

## ESC telemetry

Either RPM digital out or PWM signal can be used. The signal is sent to Smartport as RPM sensor

- Digital signal does not need to be calibrated but only Hobbywing protocol is implemented (other protocols can be implemented)
- PWM signal can be from any ESC which has this output. The RPM value needs to be calibrated. To use the PWM signal from the ESC comment the sketch line *#define ESC_DIGITAL*

## Battery voltage

The Nano can be used also to measure th0e battery voltage. This can be done with a voltage divider (total voltage) or individual cells with a TL084

- Voltage divider needs to be calibrated in Opentx with multiplier in VFAT sensor
- Individual cells can measured with an op amp like TL084. Then uncomment line *#define BATT_SENSOR_CELLS* 

If voltage measurement is not needed comment line *#define BATT_SENSOR_VOLT*

## Voltage divider circuit

Metal resistors are recommended as gives more accurate readings and 0.1W or more
Arduino can read up to 5V and is optimized for readings inputs with signal impedance of 10K

To select R values apply formulas: 

*Vo=Vi\*R2/(R1+R2)<5V*  
*Z=1/((1/R1)+(1/R2))<10K*

![Image](./images/Resistive_divider.png?raw=true)

For 3S battery you can choose :

- R1 22K
- R2 12K

For more than 3S change R values or you may burn the Arduino!

## Wiring (with voltage divider):

- ESC Vcc to Arduino Vcc
- ESC Gnd to Arduino Gnd
- ESC Data to Arduino 2
- Receiver smartport to Arduino 8
- Voltage divider + to A4
- Voltage divider - to GND

<img src="./images/rmp_bb.png" width="400">
<img src="./images/nano1.jpg" width="400">
<img src="./images/nano2.jpg" width="400">

## Adjusting RPM value

If using digital RPM and leaving POLES 1 in the code, adjust RPM sensor in Opentx:

- Blades/poles: number of pair of poles * main gear teeth  
- Multiplies: pinion gear teeth

If using PWM, signal needs to be calibrated with a tachometer. Although max head speed can be estimated with the formula: 

*Head speed =(pack voltage \* motor kv)/(main gear/pinion)* 
Then apply an efficiency factor of 90%

It has to be measured without blades at full throttle (disable governor). Then adjust the value in Opentx with the divisor Poles/blades in RPM sensor

## Values average

The values sent to Smartport are averaged with 20 readings. This can be adjusted with:

*#define RPM_QUEUE_SIZE 20  
#define VOLT_QUEUE_SIZE 20*

## Flash to Arduino

If using Arduino IDE copy folder *rpm_volt_sensor* and open *rpm_volt_sensor.ino*. Select Arduino Nano and flash it

# [Youtube video](https://youtu.be/q-e1SoEPNao)
