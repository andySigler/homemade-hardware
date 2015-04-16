#Homemade Arduino SMD
##A clone of the Arduino-Pro-Mini

This is a clone of the [Arduino Pro Mini](http://arduino.cc/en/Main/arduinoBoardProMini) made with the tools at ITP. It's design is 

###Features

* Arduino Uno bootloader
* 3.3 volts @ 16MHz
* Dimension: 3.5cm x 2cm (1.37" x 0.8")
* LED on pin 5 (not pin 13)
* FTDI programming headers
* Onboard reset button
* Solder points for [coin cell battery holder](http://www.digikey.com/product-detail/en/BA2032/BA2032-ND/257744)

###Pinouts

![Pins](https://github.com/andySigler/homemade-hardware/blob/master/Arduino-SMD/pinout.png)

###Parts List

* [ATMega328](http://www.digikey.com/product-detail/en/ATMEGA328-AUR/ATMEGA328-AURCT-ND/3440951) (this build does not use the [ATMega328p](http://www.digikey.com/product-detail/en/ATMEGA328P-AUR/ATMEGA328P-AURCT-ND/3789455))
* [3.3 Volt Regulator](http://www.digikey.com/product-detail/en/MIC5205-3.3YM5%20TR/576-1259-1-ND/771886)
* [16 MHz Resonator](http://www.digikey.com/product-detail/en/PRQC16.00SR1010V00L/1253-1339-1-ND/4879394)
* [10 uF Pol. Capacitor](http://www.digikey.com/product-detail/en/T491A106K006AT7280/399-10116-1-ND/3759233) x 2
* [0.1 uF Capacitor](http://www.digikey.com/product-detail/en/CC0603ZRY5V9BB104/311-1343-1-ND/2103127) x 3
* [10,000 Ohm Resistor](http://www.digikey.com/product-detail/en/RC0603JR-0710KL/311-10KGRCT-ND/729647) x 3
* [LED](http://www.digikey.com/product-search/en?pv7=2&k=160-1434-2-ND&mnonly=0&newproducts=0&ColumnSort=0&page=1&quantity=0&ptm=0&fid=0&pageSize=25) x 2
* [Tactile Switch](http://www.digikey.com/product-detail/en/8-1437565-1/450-1941-ND/529677)
* [Coin Cell Battery Holder](http://www.digikey.com/product-detail/en/BA2032/BA2032-ND/257744) (optional)

###Burning a Bootloader

This build uses the ATMega328, and not the more common ATMega328p, making the Arduino IDE unable to recognize the chip when burning a bootloader. This can be fixed by adding a new device signature to the Arduino IDE's 'avrdude.conf' file.

The steps below will guide you through adding the device signature for the ATMega328. However, these changes must be undone in order to send sketches to the Arduino after burning the bootloader.

#####Step 1
Quit the Arduino IDE if it is open.
#####Step 2
Find where you've installed Arduino, right-click it, and select `Show Package Contents`
#####Step 3
Navigate all the way into `Contents/Resources/Java/hardware/tools/avr/etc` and you'll find the `avrdude.conf` file
#####Step 4
Open `avrdude.conf` in a text editor, and find the following line for the ATMega328p:
```
signature   = 0x1e 0x95 0x0F;
```
#####Step 5
Comment that line out with an `#`, and add the new signature of the ATMega328. It should like like the following now:
```
# signature   = 0x1e 0x95 0x0F;
signature   = 0x1e 0x95 0x14;
```
#####Step 6
Restart the Arduino IDE, and you should be able to bootload the board.
#####Step 7
When you're done, change the `avrdude.conf` file back to it's original settings so that you can send your sketches to the board:
```
signature   = 0x1e 0x95 0x0F;
# signature   = 0x1e 0x95 0x14;
```





