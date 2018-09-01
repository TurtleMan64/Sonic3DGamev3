Keyboard Controls:   
WASD to control sonic + menu   
Spacebar to jump + accept on menu  
Ctrl/Shift to spindash  
Ctrl to bounce  
Shift to dropdash
Q to stomp
F to light dash  
Tab to grab/release mouse  
Enter to pause/unpause 
0/9 to change time of day 

You can change the game resolution and fullscreen mode 
in the DisplaySettings.ini located in the Settings folder.

Troubleshooting FAQ:

When I launch the game, it gives me the error "The program 
can't start because MSVCP140.dll is missing from your computer"
You will need to install Microsoft C++ Redistributable, which 
you can find the 32 bit version here: 
https://aka.ms/vs/15/release/vc_redis...

My camera is spinning! Sonic's controls are inverted! What do?
Your controller will need to be configured. Go into the Settings 
folder and edit ControllerConfig.ini - this is the file that the 
game reads to map controller buttons/axis. You will also see some 
other example controller config files for some popular controllers. 
You can copy+paste the contents from whichever file you want 
into ControllerConfig.ini. So for example, if you use a Logitech F310 
controller, copy the contents of ControllerConfigLogitechF310.ini and 
paste that into ControllerConfig.ini.

The game is running way too fast!
This is a common issue for 144 Hz monitors. This game is designed 
to run at 60 Hz, so you will need to put your monitor in 60 Hz mode.

The game is lagging! It's unplayable this slow...
There are a couple of graphics settings you can turn down to really 
improve performance. Open up to Settings/GraphicsSettings.ini, and 
turn down some of the high impact settings. Render_Bloom, HQ_Water, 
and Render_Shadows are all good ones to disable to see if they help 
the game not lag.

If you notice the water is broken (very obvious 
at the start of emerald coast) turn HQ Water off in the 
graphics settings. The broken water has been obversed on an 
AMD RX 480 on driver revisions 18.7.1 and 18.8.1. 
Another solution is downgrading to 18.6.1 or lower.

