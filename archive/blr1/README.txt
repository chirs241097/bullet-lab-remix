/*************************************\
 *    Bullet Lab Remix HGE 1.0.3     * 
 *      The Creature of Colour       * 
 *       CopyLeft Chris Xiong        * 
 *   Readme File for binary release  * 
\*************************************/
*************************************************************
First, I'm glad to annonce the first stable release of BLR.
After three and a half of lazy work, BLR1 Stable came out at last.
Well, this is just the start. Let's expect BLR2!
*************************************************************
WARNING: Everything works correctly on my computer, but I can't guarantee the same 
thing will happen on your computer!
----------------------------------------------------------------------------------
Why I am writting this "Game":

-Do not care details...
----------------------------------------------------------------------------------
Attention: If you are using Linux, just ignore this and read Compiling.txt
Basic requirements of this game:

Hardware requirements:
CPU: Better than none.
RAM: If you are using Windows XP+, you can ignore this.
GPU: Any GPU supporting DirectX 9 is okay.
A keyboard is necessary. Although this game doesn't use a mouse to control, you'd 
better have one to use your operating system...

Software requirements:
If your computer is not from the last century and the game wouldn't start, check...
If DirectX 9 Runtime is installed.
If you are using Windows XP or later version.

Something else...:
CheatEngine (Optional, recommended for people who are urgent to highscores.)
No Trypophobia! (Important!!)

Additional:
To run it in High FPS mode (much better experience than Low FPS mode)
-Turn on "Lock FPS to the highest level" in BLR config
-Configure your GPU correctly. A mis-configured GPU can cause many problems...
-Have a stronger CPU. Quad core is recommended.

If FPS is only around 500... Just give it up... Turn on Low FPS mode in BLR config.

Another small tip:
I found that Intel HD Graphics always get the highest FPS easily...
----------------------------------------------------------------------------------
[Attention!]: The topic below is for those who have tried to play but failed.

Operating with keyboard:
Arrow keys: Move
Shift+Arrow keys: Precise move (If you ignore this you will probably NEVER pass easy)
(Well, I was joking. You can "Continue" anyway.)
Z (or X, determined in your configuration): Call Clear Range
Z/Enter(In menus): Confirm
Esc(In game): Pause

Collision & "Semi-collision":
Only a VERY close distance will be treat as a collision (about 2 pixels, imagine that.)
Other bullets passed by you(in 4 pixels) will be treat as a semi-collision, which would
plus your score by 2000.

Configuring the player:
You can customize the player in the Player Profile menu.
You can determine the player's moving speed(both in normal mode or precise mode).
And a clear range bonus.
You should know that you are customizing yourself in the limit of "Ability Points".
----------------------------------------------------------------------------------
Softwared used to develop Bullet Lab Remix:
Visual Studio 2012 (Compiler)
DirectX SDK (Aug. 2009)
HGE (Packed DirectX APIs)
Photosohop CS6 for graphic resources
Inkscape for vector graphics
Porting to Linux is also done by Chris Xiong, using Kwrite and Geany.
----------------------------------------------------------------------------------
Frequently Asked Questions and my own problems

Q: ...The game crashes and quit automatically?
A: I didn't have that problem... This may be caused by a wrong RAM access.
   Make sure you have enough RAM to run this game.

Q: It stopped working just before the menu appears...
A: Well, I use "freopen" for file operations. M$ said that's not safe but I insisted..
   Just be patient and restart the game.

Q: Huge RAM usage?
A: The main code uses less than 5 MB RAM. However, levels with too much bullets may 
   use a huge amount of RAM.

Q: "Cannot decompress resources!"
A: Resources used in this game have been compressed with Microsoft LZ compresss program.
   If you meet this fault, check if there's already a folder called "Decompressed" in 
   the Resources folder. If so, delete it. (Now the program could delete it automatically
   even the error has already been reported. So you may not find this folder. Just restart
   the game)
   If that doesn't work, check if "expand.exe" is included in your system.

Q: Everything runs slowly!
A: Check FPS which is displayed at the right bottom corner of the game. The game
   should run at at least 850 FPS (In HighFPS mode).
   If it is below 700 (at the menu scene), turn on Low FPS mode using the
   configure application.
   If it is fixed at 60 and it is running EXTREMELY slowly, try turn off vertical
   sync first (in your graphics driver settings). If it doesn't work, turn on Low
   FPS mode.
   Please note that Low FPS mode may provide a horrible experience...

Q: What is "Average FPS"?
A: Average FPS is the average of FPS during the game(WTF!). It showed how your computer felt during
   the game...

Q: Tell me something about the UI.
A: The main menu:
           Start---------------Enter the difficulty selecting menu.
   Highscore && Records--------Enter highscore view selecting menu.
          Options--------------Enter options menu.
          Credits--------------Show a long, dull credits list.
            Exit---------------Parents are coming!!!
   The difficulty selecting menu:
            Easy---------------Difficulty without difficulty.
           Normal--------------For most human-beings.
          Extreme--------------Who would like to try?
       Free Play Mode----------No deaths, go for highest score.
            Back---------------Giving up?
   The Options menu:
      Fullscreen: ...----------Toggle fullscreen, the settings will be applied after restarting the game.
    FPS Level: ...-------------Toggle FPS level mode. Possible modes are: Low FPS, Highest and Natural.
Use Key . for Clear Range------Change the key to call Clear Range.
    Player Profile-------------Customize the player.
         Back------------------Done setting, I'm ready!
Tips:
   If supported, you can toggle fullscreen in game by pressing Alt+Enter. However this won't affect your settings.
   Use key Left/Right to adjust values in Player Profile page.

Q: How to load default configuration?
A: To load default configuration, just delete blr.cfg. Then start BLR, you can do your initial settings again.
   Attention: YOUR SCORE FILE WILL BE CLEARED AS WELL!!

Q: When I use a Clear Range, FPS falls terriblely.
A: This is normal... Because the code of Clear Range is terribly inefficient...

Q: Some levels are impossible to pass!
A: That may be true... (I got the same result from some of the testers)
   However this is an excuse, I think.

Q: Ain't there any background?
A: It is painful to think about a background...
   So think about your own background... everyone will have his own version...(Chemistry Laboratory etc.)

Q: Where to get the source code?
A: The source code is terribly ugly...
   However, when I release the binary version, I will also release a tarball of
   the source code.
   To be more creative, WRITE YOUR OWN CODE.
----------------------------------------------------------------------------------
Version History && Planning Versions
For detailed information, view CHANGELOG.txt.

1.0.3sr: Hope this fix for hidden bullets could work!
1.0.2pr: Some input event fixes. Fixed a problem in the render engine. Get rid of the config program.
1.0.1pr: Get rid of hge.dll. Merging hge into project.
1.0.0pr: Fixing small bugs and cheats. Upgrading DirectX to DX9. Trying porting to Linux.
0.8.9α : Adding a lot of lacking functions in earlier versions.
0.8.8α : Small fixes for adding functions.
0.8.7α : Preparation for 1.0.0, categorizing code, bug fixes, resoureces compression andadding some effects etc.
0.8.6α : Second released version, small bugs fixed, a better icon for configure program.
0.8.4α : First released version, most cheats are removed, level frozen version(No new levels will be added).
0.7.4  : A developer only version, the game system is almost completed.
0.7.0  : A developer only version, 7 levels available now.
0.5.3  : A developer only version, 5 levels available now, added collision and semi-collision detection.
0.2.1  : First tower, first bullet. 2 basic levels completed. Basic effects added.
0.0.1  : Only a main menu!

2013-5-11: Project Started
Let's remember the great day!
Thank everyone that waste time to test my poor project!