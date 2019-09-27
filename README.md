# Arduino Library for LCDs with Holtek HT1621 controller 


**WHY:**
The HT1621 is in many old lcd appliances and can be directly adressed to write to old salvaged lcds that are driven by this chip.
Most Chips are from holtek, but any 48-pin SSOP with 1621 on it's name is probably an HT
It has an integrated 2Khz/4Khz Buzzer
You can buy the chips from ebay from less than 20 cents a piece
*ebay search:* goo.gl/qw28xx

**WHAT**
The HT1621 is a 128 pattern (32x4), memory mapping, and multi-function LCD driver. 
The S/W configuration feature of the HT1621 makes it suitable for multiple LCD applications including LCD modules and display subsystems.
Only three or four lines are required for the interface between the host controller and the HT1621.
The HT1621 contains a power down command to reduce power consumption.
Operating voltage: 2.4V~5.2V

**Datasheet:** <http://www.seeedstudio.com/document/HT1621.pdf>

**HOW**
The idea is to reverse and reuse old salvaged LCDs that have the chip as a driver

---
**Links**
[Enumerating LCD segments with OpenCV for reverse-engineering](https://eleif.net/lcd-segmentation.html)
--- 

**Original source**: <https://macduino.blogspot.com/2015/02/HT1621.html>
