# Arduino library to work with LCD via Holtek HT1621 controller

**WHY:**
The HT1621 chip is in many old LCD appliances and can be directly adressed to write to old salvaged LCDs that are driven by this chip.
Most Chips are from Holtek, but any 48-pin SSOP with 1621 in it's name is probably an HT.
It has an integrated 2Khz/4Khz buzzer.
You can buy the chips from [ebay for less than 20 cents a piece](goo.gl/qw28xx).

**WHAT**
The HT1621 is a 128 pattern (32x4), memory mapping, and multi-function LCD driver. 
The S/W configuration feature of the HT1621 makes it suitable for multiple LCD applications including LCD modules and display subsystems.
Only 3 or 4 lines are required for the interface between the host controller and the HT1621.
The HT1621 contains a power down command to reduce power consumption.
Operating voltage is 2.4V~5.2V

**HOW**
The idea is to reverse and reuse old salvaged LCDs that have the chip as a driver

## Links

- **Datasheet:** <http://www.seeedstudio.com/document/HT1621.pdf>
- [Enumerating LCD segments with OpenCV for reverse-engineering](https://eleif.net/lcd-segmentation.html)
- **Original source code and idea**: <https://macduino.blogspot.com/2015/02/HT1621.html>
