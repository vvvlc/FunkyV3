FOTA/Wireless Programming for Funky V3

\

I wanted to have [FOTA](http://en.wikipedia.org/wiki/Over-the-air_programming)/[Wireless programming](http://lowpowerlab.com/blog/category/moteino/wireless-programming/) capability for my project. Unfortunately [RFM](https://github.com/LowPowerLab/RFM69)[69 ](https://github.com/LowPowerLab/RFM69)[library](https://github.com/LowPowerLab/RFM69) does not fit 4kB [bootloader](http://www.hackersworkbench.com/intro-to-bootloaders-for-avr) area therefore I could not follow [standard self-programming mechanism](http://www.engineersgarage.com/embedded/avr-microcontroller-projects/How-to-Use-SPM-for-Flash-to-Flash-Programming) (store data comming from a serial stream to internal flash). I wanted to reuse [Felix's wireless programming library](https://github.com/LowPowerLab/WirelessProgramming) however [F](http://harizanov.com/wiki/wiki-home/funky-v3/)[unky ](http://harizanov.com/wiki/wiki-home/funky-v3/)[V3](http://harizanov.com/wiki/wiki-home/funky-v3/) does not have external [spi flash](http://www.instructables.com/id/How-to-Design-with-Discrete-SPI-Flash-Memory/). Therefore I had to change layout of the internal 32kB flash. I was influenced by video: [Intermediate memory bootloaders](https://www.youtube.com/watch?v=jbLy6kE-Szg).

Standard layout for atmega32u4 with Caterina bootloader has two main sections. The application section (aps) 0x0000-0x6FFF (28KB) and bootloader section (bls) 0x7000-0x7FFF (4KB). 

I split aps into two equal areas. First is an app area 0x0000-0x37FF (14KB) and the rest 0x3800-0x7FFF (14KB) is something like external spi flash area, let's call it temp area. The first disadvantage is clear we have only 14KB instead of 28KB for our application code. To be honest it is even worst. 12KB out of 14KB is occupied by RFM69 driver and wireless programing code. The bottom line is that we have around 1KB for our app. It may seem to be ridiculously small but it is sufficient for my app that is supposed to count led flashes on my watt-meter and send them via RFM69 to [RFM69PI V3](https://wiki.openenergymonitor.org/index.php/RFM69Pi_V3) gateway for further processing. Later on I would like to measure other things such as temperature voltage of battery, … and I don't have easy access to Funky node therefore FOTA is needed.

Changes in Bootloader {.western lang="zxx"}
=====================

-   

<!-- -->

-   

\

The only remaining piece is the update of temp area with firmware coming over the air.

Changes in Wireless Programming Library {.western lang="zxx"}
=======================================

Modified wireless programming library writes firmware coming from the air into temp area instead of external spi flash. I removed all debugging messages to shrink size of this library in favor of space for application code.

Layout of Flash Memory {.western lang="zxx"}
======================

0x0000 – 0x37FF Application code (app area) 14KB=14336B

0x3800 – 0x3801 Length of data in temp area (if value \>14334 means temp area contains invalid data

0x3802 – 0x6FFF Temp area 14334B

0x7000 – 0x7FFF Bootloader area 4096B (bls)

Complete Flow of FOTA Process {.western lang="zxx"}
=============================

1.  2.  3.  4.  5.  6.  7.  8.  9.  10. 

Potential Improvements {.western lang="zxx"}
======================

verification of checksum of firmware prior to update of app area.

more space in the app area, there are several techniques how to get there

-   -   -   

introduce [faster mode](http://lowpowerlab.com/blog/2016/01/21/wireless-programming-just-got-50-faster/) that increases transfer rate

allow Arduino IDE to update firmware over the air
