Authors:
    Arian Safari
    Aishan Irfan

Retro platformer game influenced by the Donkey Kong games. This game has been created for the Raspberry Pi 4 and was written for the course CPSC359.

Game instructions:

The character must collect all coins and get to the door in the given time to pass each level.
Blue hearts grant half a heart.
Enemies (Skelettons, sharks, wolves, DK) reduce half a heart and reset character position when the character is hit
Some objects (rocks, trees, barrels) block the characters path and others (cactus, seaweed, thorns, explosive barrels) reduce half a heart and reset character position when the character hits them.

How to run:
You must be using a device with a Fedora Linux OS that is able to run the openocd command.
Connect the Raspberry Pi 4 to your computer and the SNES controller to the Raaspberry Pi. The Raspberry Pi must also be connected
to an external monitor via HDMI.

1. Open a terminal and run the command "openocd -f rpi4.cfg"
2. Open another terminal and run gdb
3. In gdb run the following commands:
    1. set architechture aarch64
    2. target extended-remote :3333
    3. make
    4. load kernel8.elf
    5. continue (or c)