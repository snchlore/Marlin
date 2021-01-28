use 5v probe?
use wider signal on probing?

#define S_CURVE_ACCELERATION
// #define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
#define USE_PROBE_FOR_Z_HOMING
#define BLTOUCH
#define NOZZLE_TO_PROBE_OFFSET { -42, -10, 0 }
#define XY_PROBE_SPEED (166*60)
#define Z_PROBE_SPEED_FAST (8*60)
#define Z_PROBE_SPEED_SLOW (Z_PROBE_SPEED_FAST)
#define Z_MIN_PROBE_REPEATABILITY_TEST
#define AUTO_BED_LEVELING_BILINEAR
#define RESTORE_LEVELING_AFTER_G28
#define G26_MESH_VALIDATION
#define GRID_MAX_POINTS_X 5
#define PREHEAT_1_TEMP_HOTEND 210
#define PREHEAT_1_TEMP_BED     70

/*

Press J to jump to the feed. Press question mark to learn the rest of the keyboard shortcuts
Log In
Sign Up
57
Step-by-Step Guide for Ender 3 v2 Firmware w/ BLTouch and UBL
57
Posted byu/MironV
5 months ago
SilverHugz
Step-by-Step Guide for Ender 3 v2 Firmware w/ BLTouch and UBL

It's hard to find good tutorials online for how to roll your own firmware. It's actually really easy, so I thought I'd write up a quick guide on it for anyone who is interested. Otherwise, I recommend the excellent pre-compiled firmware here: https://marlin.crc.id.au/.

    Get a few important tools:

        Git: You don't need Git, as you can download the source code directly, but it's nice to have because then you can just pull the latest changes every few weeks and recompile.

        VS Code: This is the editor where you'll make your changes. Simply download it here.

        PlatformIO: This is the VS Code extension that compiles the Marlin firmware. You can install it with these simple instructions.

        Auto Build Marlin: This is an optional VS Code extension that makes things even simpler to build. You can install it with these simple instructions.

    Get the source code.

        With Git: Open up a terminal, navigate to the folder you want and type git clone https://github.com/MarlinFirmware/Marlin.git, which will create a new folder called Marlin with all the source code. Navigate to the folder and type in git checkout bugfix-2.0.x to switch to the nightly branch where the Ender 3 v2 is currently supported.

        Without Git: Just download the bugfix-2.0.x branch directly and unzip it somewhere.

    Open the main Marlin folder in VS Code. Simply go to File -> Open and then find the main folder you either cloned or unzipped.

    Configure the platformio.ini file, which is in the main Marlin folder. You just need to change the default_envs (you'll see it near the top) by writing: default_envs = STM32F103RET6_creality.

    You now need to configure the Configuration.h and Configuration_adv.h files for the Ender 3 v2. The examples for the Ender 3 v2 are here. Download them, then navigate to Marlin/Marlin/ (the folder called Marlin inside the main Marlin folder) and completely replace the Configuration.h and Configuration_adv.h that are there.

    Almost done! We now just want to do a couple of tweaks. This is really easy, I promise. If you ever wonder what a certain section does, you can read the documentation for Configuration.h here and Configuration_adv.h here. We won't need to further modify Configuration_adv.h in this tutorial. In VS Code, open up Configuration.h and make the following changes to enable BLTouch (you can just search for the names):

        In #define DEFAULT_AXIS_STEPS_PER_UNIT you can change your e-steps default from 93 (it's the 4th number).

        If you want, enable #define S_CURVE_ACCELERATION by removing the //.

        You should have all 5 wires of the BLTouch connected to the port rather than using the Z-Stop like older Ender 3 versions. You should disable #define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN by adding // in front of it.

        Enable #define USE_PROBE_FOR_Z_HOMING by removing the //.

        Enable #define Z_MIN_PROBE_PIN 32 by removing the // and change the 32 to Z_PROBE_PIN. This step is no longer needed, revert it back to the original.

        Enable #define BLTOUCH by removing the //.

        Change #define NOZZLE_TO_PROBE_OFFSET { 10, 10, 0 } to the settings for the printed mount. If you use this one from Thingiverse, change to #define NOZZLE_TO_PROBE_OFFSET { -42, -10, 0 }.

        You can increase #define XY_PROBE_SPEED 3000 to 10000 to make things a bit faster.

        You can enable M48 if you want: #define Z_MIN_PROBE_REPEATABILITY_TEST by removing the //.

        Enable #define DELAY_BEFORE_PROBING 200 by removing // and change to 100 to keep things snappy.

        I like to change the bed size to #define X_BED_SIZE 230 and #define Y_BED_SIZE 230.

        Enable #define AUTO_BED_LEVELING_BILINEAR by removing //. You could also use #define AUTO_BED_LEVELING_UBL.

        You can enable #define RESTORE_LEVELING_AFTER_G28 so you don't have to re-enable bed leveling after homing.

        You can enable #define G26_MESH_VALIDATION to let you print quick bed leveling test patterns. Set the variables below it to whatever settings you normally use.

        If you're using bilinear, you can change the amount of points to use (e.g., 3x3 or 5x5) by modifying #define GRID_MAX_POINTS_X 3 to 5 or more.

        Enable #define Z_SAFE_HOMING by removing //.

        If you want to change your default temps, you can change the variables under #define PREHEAT_1_LABEL "PLA".

    If you want to mess with the LCD, you can open up dwin.cpp in Marlin/Marlin/src/lcd/dwin/. I modified #define MACHINE_SIZE "220x220x250" to "230x230x250" and you can also mess with some stuff like #define CORP_WEBSITE_E.

    Save all the changes, click on the "M" button on the left-hand side for the Auto Build Marlin extension and then click the little hammer icon to build. Check some stuff:

        Firmware should be "Marlin bugfix-2.0.x".

        Machine Name should be "Ender-3 V2" with "Cartesian 230x230x250mm with Heated Bed (1)".

        Environments should be "STM32F103RET6_creality".

    The firmware file is located in a hidden folder in the main Marlin folder. Enable hidden folders and navigate to Marlin/.pio/build/STM32F103RET6_creality/. You'll see a file called firmware-[date]-[time].bin where [date] and [time] changes depending on when you build it. This is handy because the Ender 3 v2 will ignore firmware if it has the same name.

    Copy the firmware file to an SD Card, put it in the Ender 3 v2, and turn it on. The LCD screen should be black for a bit and then it should boot up with your new firmware!

That should be it. You can configure your BL Touch using this excellent guide from /u/wolftecx. In general, you can use M119 to check the status of the BL Touch and play around with M280 P0 S10 to deploy, M280 P0 S90 to retract, and M280 P0 S60 and M280 P0 S160 to enter/exit test mode.

If you want to use the fancy UBL vs. just bilinear, enable it per the instructions above. You then need to make some changes:

    UBL enables you to do a very detailed leveling and then adjust it quickly with each print. You can also use OctoPrint to set this up, basically the sequence to wire up to a command is:

M140 S60 ; Warm bed to 60C.

M190 S60 ; Wait until bed is warm so we're more accurate.

G28 ; Home XYZ.

G29 P1 ; Do automated probing of the bed.

G29 P3 ; Fill in the rest.

G29 S1 ; Save UBL mesh points to EEPROM in Slot 1.

G29 F 10.0 ; Set Fade Height for correction at 10.0 mm.

G29 A ; Activate the UBL System.

    You should be able to wire up the "Level" button in the LCD to do the same thing. Just open up dwin.cpp, find queue.inject_P(PSTR("G28O\nG29")); and change it to queue.inject_P(PSTR("M140 S60\nM190 S60\nG28\nG29 P1\nG29 P3\nG29 S1\nG29 F10\nG29 A"));.

    Now that you have the main leveling done, you want to do a quick 3-point level before each print in Cura's settings:

; Ender 3 Custom Start G-code

M140 S{material_bed_temperature_layer_0} ; Set Heat Bed temperature

M190 S{material_bed_temperature_layer_0} ; Wait for Heat Bed temperature

M104 S160; start warming extruder to 160

G28 ; Home all axes

G29 A ; Activate the UBL System.

G29 L1 ; Load UBL

G29 J ; Quick 3-point level

G29 F10.0 ; Fade to 10mm

G92 E0 ; Reset Extruder

M104 S{material_print_temperature_layer_0} ; Set Extruder temperature

G1 X0.1 Y20 Z0.3 F5000.0 ; Move to start position

M109 S{material_print_temperature_layer_0} ; Wait for Extruder temperature

; G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed

G1 X0.1 Y200.0 Z0.3 F1500.0 E15 ; Draw the first line

G1 X0.4 Y200.0 Z0.3 F5000.0 ; Move to side a little

G1 X0.4 Y20 Z0.3 F1500.0 E30 ; Draw the second line

G92 E0 ; Reset Extruder

G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed

; End of custom start GCode

Hope this helps!
52 comments
93% Upvoted
Log in or sign up to leave a comment
Log In
Sign Up
Sort by
View discussions in 1 other community
level 1
jShips831
5 months ago
· edited 5 months ago

So this worked great.. however its stuck in Japanese on the lcd panel. In the Configuration.h file the LCD_LANGUAGE is defined as `en`.

Is there some sort of method to get it back to english?

Scratch that, found a solution! https://www.reddit.com/r/ender3/comments/hmlbt6/ender_3_v2_ui_in_chinese/
2
level 1
Fernlander
5 months ago

Incredible write up. While i’m i’m there is like to clean up a few other things. Like add live baby stepping and add linear advance. Also I believe Marlin 2.0.6 release supports Ender 3 V2 or am I wrong?
2
level 2
MironV
5 months ago

It might be supported, I haven't checked yet. Babystepping is easy to enable in the advanced configuration file. Unfortunately, linear advance is not possible with the Ender 3 v2 because the motor drivers are in Legacy mode.
1
Continue this thread 
level 1
ThatPrinterDude
4 months ago

Something has changed, and these instructions now cause the nozzle to crash into the bed during z homing.

Config change e (or #5) is the culprit. You should no longer enable the #define Z_MIN_PROBE_PIN line. The code defining pins for the board now takes care of this by default.
2
level 1
fooxzorz
4 months ago

> Enable #define DELAY_BEFORE_PROBING 200 by removing // and change to 100 to keep things snappy.


If you get probing failed errors in OctoPI, increase it back to 200 or 350 (ms). Mine would work for a few probes doing a G29 P2, but then fail and when it failed it was like the probe just never triggered and the Z would crash into the bed.


I am assuming the probe wasn't ready by the time it was supposed to trigger.
2
level 1
calebjade
4 months ago

Good God I've been seaching every term imaginable to try to find out how to do this. Thank you so much
2
level 1
eudes8
2 months ago

Worked without a hitch for me! Thanks u/MironV
2
level 1
mitjahenner
2 months ago
· edited 2 months ago

Great guide. Everything seems to work fine until I try to save the mesh to EEPROM:

Send: G29 S1

Recv: echo:start

Recv: PowerUp

Recv: Marlin bugfix-2.0.x

Recv:

Recv: echo: Last Updated: 2020-11-13 | Author: (none, default config)

Recv: echo:Compiled: Nov 15 2020

Recv: echo: Free Memory: 49079 PlannerBufferBytes: 1600

Recv:

Recv: DWIN handshake error.

Recv: Unified Bed Leveling System v1.01 inactive

Recv:

Recv: BL24CXX Check succeeded!

Recv: echo:SD card ok

Printer restarts and the mesh is gone.
2
level 2
jpijiu
1 month ago

Same problem. You get it solved?
1
Continue this thread 
level 1
listener4
5 months ago

Nice! Is it the same for the display firmware? It looks like that's in dwin.cpp, but I thought it was a separate binary?
1
level 2
MironV
5 months ago

The display firmware is a separate thing, I'm not sure if there are any updates to that.
2
level 1
byun123
5 months ago

Whenever I flash the firmware with the example configuration.h and configuration_adv.h files, I get an error "TMC connection error". I do not get this when I apply my changes to the default files in the Marlin directory. Any idea why?
1
level 2
MironV
5 months ago

Where is this error displaying?
1
Continue this thread 
level 1
ElMarco19
5 months ago

Can't get it to work on my printer https://www.reddit.com/r/ender3v2/comments/i9xowh/bltouch_31_not_leveling_marlin_206_hero_5_gen_me/
1
level 1
NLclothing
5 months ago

So what are the benefits of UBL vs other leveling methods? Worth the extra trouble?
1
level 2
MironV
5 months ago

The main bed leveling procedure uses a lot more points and you can save different ones if you switch build plates out. This then lets you do a quick 3-point level before each print that adjusts the mesh further. Overall, UBL is faster with more accuracy.
1
level 1
InvalidUserAccount
5 months ago

Quick question. I don't quite understand #1 under the bl touch configuration.h section. What should I be doing exactly there?

    "In #define DEFAULT_AXIS_STEPS_PER_UNIT you can change your e-steps default from 93 (it's the 4th number)."

If I'm changing it from 93 what am I changing it too?

Thanks in advance!
1
level 2
MironV
5 months ago

The esteps calibration ensures that when you ask for 100mm of filament, you get 100mm and not 105mm or 94mm or something.

You can follow this video for instructions on how to set this: https://youtu.be/HVljfDVPp3o
2
Continue this thread 
level 1
Sfelaccio
5 months ago

I'm having a problem with ubl if you can help. I can't get the level menu button to work with ubl. Even when changing queue.inject_P(PSTR("G28O\nG29")); to queue.inject_P(PSTR("M140 S60\nM190 S60\nG28\nG29 P1\nG29 P3\nG29 S1\nG29 F10\nG29 A")); Any advice? It will go through the steps but it won't go back to the main menu after. It just says auto leveling...
1
level 2
MironV
5 months ago

Have you confirmed the steps themselves work fine with something like Pronterface or OctoPrint?
1
Continue this thread 
level 1
Revolutionary_Ad9028
3 months ago

I am getting a compile error that is related to the default_envs. Any suggestions?

Here is my statement in platformio

[platformio]
src_dir      = Marlin
boards_dir   = buildroot/share/PlatformIO/boards
# default_envs = mega2560
default_envs = STM32F103RET6_creality
include_dir  = Marlin

This is the compile error

In file included from c:\users\kassalkane\.platformio\packages\toolchain-gccarmnoneeabi\arm-none-eabi\include\c++\7.2.1\stdlib.h:36:0,

from C:\Users\KassalKane\.platformio\packages\framework-arduinoststm32-maple\STM32F1\cores\maple\wirish.h:41,

from C:\Users\KassalKane\.platformio\packages\framework-arduinoststm32-maple\STM32F1\cores\maple\Arduino.h:30, from C:\Users\KassalKane\.platformio\packages\framework-arduinoststm32-maple\STM32F1\cores\maple\tone.cpp:11:

c:\users\kassalkane\.platformio\packages\toolchain-gccarmnoneeabi\arm-none-eabi\include\c++\7.2.1\cstdlib:41:10: fatal error: bits/c++config.h: No such file or directory

#include <bits/c++config.h>

^~~~~~~~~~~~~~~~~~

compilation terminated.

*** [.pio\build\STM32F103RET6_creality\FrameworkArduino\sdio.cpp.o] Error 1

arm-none-eabi-g++: error: CreateProcess: No such file or directory

arm-none-eabi-g++: error: CreateProcess: No such file or directory

*** [.pio\build\STM32F103RET6_creality\FrameworkArduino\tone.cpp.o] Error 1

*** [.pio\build\STM32F103RET6_creality\FrameworkArduino\stm32f1\wirish_digital_f1.cpp.o] Error 1

*** [.pio\build\STM32F103RET6_creality\FrameworkArduino\stm32f1\wirish_debug.cpp.o] Error 1

================================================= [FAILED] Took 33.86 seconds =================================================

Environment Status Duration

---------------------- -------- ------------

STM32F103RET6_creality FAILED 00:00:33.862

============================================ 1 failed, 0 succeeded in 00:00:33.862 ============================================The terminal process "C:\Users\KassalKane\.platformio\penv\Scripts\platformio.exe 'run'" terminated with exit code: 1.


Terminal will be reused by tasks, press any key to close it.
1
level 2
MironV
3 months ago

It looks like PIO didn't install correctly so files are missing. I would double-check your install.
1
level 1
RoryWQuin
2 months ago

Wow - lots of work from you. Thanks for this!
1
level 1
Waste_Fig_107
2 months ago

Wow, great work with this. I'll give it a try tomorrow! :) Thanks alot
1
level 1
Char_Aznabl3
7 days ago

I'm trying to follow the guide and when I try to build I get an error from " Identifier 'myserial1' is undefined" does anyone know how to fix this?
1
More posts from the ender3 community
1.9k
Posted byu/Just_Dank
4 days ago
SilverHugz3
Help
Wtf are wrong with my walls
Post image
326 comments
1.4k
Posted byu/ThrottleMunky
1 day ago
SilverHugz3
In Case 2021 Starts Acting Up
Post image
see full image
107 comments
Continue browsing in r/ender3
*/