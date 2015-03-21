# Introduction #

This is a _very simple_ game, just move around and avoid collisions.

# Requirements #
  * CPU: 1GHz.
  * RAM: 256MiB.
  * GPU&VRAM: With DirectX 9+/OpenGL 1.2+ support.
  * OS: Windows XP+ & DirectX 9 / Linux kernel 2.6+ & OpenGL 1.2+
  * Recommended environment:
  * CPU: Lots of cores.
  * GPU&VRAM: Very fast graphic rendering.
  * Sound: Ability to run OpenAL software version.

## More Recommends... ##
  * SERIOUSLY, NO Trypophobia!
  * Cheat Engine(skip levels, obtain more Clear Range's, and more...)
  * Some editors or compilers(If you find this impossible and want to make it easier)
  * (Additionally for the last one)Ability to read non human-readable code.
  * ~~Achromatopsia~~

# Build and Run #

**If you're using Windows, it's recommended to download the pre-compiled**
**binary(which is built with mingw-w64) shown at the project home.**

However, that build might not be the latest revision. So some part of this text may be unavailable in the version above.

Additionally, all optimizations have been disabled for the mingw-w64 build due to bugs in mingw-w64 (or BLR).

## If you want to build from source ##
  1. checkout from svn.
  1. Get required sdks.
  1. Use Visual Studio(Windows) or Code::Blocks(Linux), create a project, or write a Makefile yourself. This project doesn't come with a Makefile yet.
  1. Hit build!
  1. If it failed, check step 2, then repeat step 4...

**Important!!:** If you managed to build a Windows version, you still have to use
the two `*`.dtp files in the official released version. They are too big to be uploaded
to this repo.

## Running BLR ##

Minimum required directory struct:
  * The executable
  * BLRData.dtp & BLRMusic.dtp(Windows)...
  * ...or the whole "Resource" folder from the source distribution(Linux).

If everything is okay, just run the executable to start BLR.

For command line options, see [IntroductionToBLR#Command\_Line\_Options](IntroductionToBLR#Command_Line_Options.md).

# Controls #

Use arrow keys to navigate in the menus. Z for selecting/changing values.

In the options menu and the player preference menu, you can also use left key and right key for changing values.

However the square can only be controlled with keyboard,
joystick and mouse are not supported yet. (And may not be supported in the future)

Arrow keys: Move.

Shift: Slow the square down.

Z or X (Modify it in Options): Hit to call Clear Range directly, hold
to charge for CLR.

Changing other key bindings is not supported yet.

# Menus #
## Main Menu ##
|Start                 | Select a mode and start the game.            |
|:---------------------|:---------------------------------------------|
|Highscores            | View highscores(Currently out of maintenance)|
|Options               | Settings and Options                         |
|About                 | A dull credits list.                         |
|Exit                  | Parents are coming!!                         |

## Game Modes ##
  * Classic
> Classic Mode. The game ends instantly if you get a collision.

> However you can choose to continue...

  * Assessment Mode
> You are the frog being boiled (instead of being frozen).

> Every levels get harder as time goes.

> You'll be brought to the next part if you had a collision.

  * Free Play Mode
> Free play. You'll never die!

> Believe it or not, this mode will waste less time...
## Options ##
  * Fullscreen
> Change if the game should be run in fullscreen mode.
> The change will take effect after restarting the game.

> P.S.: You can modify this without restarting the game by pressing
> alt+enter. However this won't be written to config.

  * VSync
> Use VSync or not.

> This game should run at ~60FPS. If your screen refresh rate is not 60,
> set this to off.

  * Clear Range Key
> Change the key for Clear Range.

  * Resolution
> Choose a resolution that BLR uses.

> The changes will take effect after restarting BLR.

> The game was designed to run under 800x600, which is its native resolution,
> however it also look well under other provided resolutions.

> If fullscreen is on, this option should use with causion. Some graphic cards/monitors
> don't support 960x720 in fullscreen mode...

  * Player Profile
> Modify the player's attribute. Available options are:
    * Moving Speed: player's moving speed
    * Precise Moving Speed: player's moving speed while shift is pressed
    * Clear Range Bonus: Get more Clear Range's.
    * Clear Range Mode: Change Clear Range's mode.
> Use left/right arrow keys to edit the value.

> Your settings will be limited by something called "Ability Point", which
> is shown below. Changing Clear Range Mode doesn't affect Ability Point.

# Gameplay #
> As mentioned above, you just move around and avoid collisions.

> However it might be harder than it looks...

> If you've never played BLR, go through the built-in help first(assessible
> in the main menu).

> If you're not sure, try the Free Play Mode first.

# Score System #
> The score system is also very "simple".
  * You'll get a few points if you survived a frame.
  * When a new bullet is generated, you'll get some points.
  * If you get a collision, you'll lose _lots of_ points. In contrast, if you get a semi-collision, you'll get a few points.
  * The "score bullets" give you extra points. They are usually generated when a Clear Range is used or a bullet is removed.
  * There's a multiplier system in this game. All your newly-gained score will be multiplied by the multiplier before adding into the score.
  * The multiplier may increase itself if there are no collisions in 30 seconds. The increment will also increase if there are combos.
  * The multiplier will be divided by 2 if there's a collision.
  * A semi-collision or a green score bullet will increase the multiplier.
  * If there're no semi-collisions in a second and the multiplier is greater than 1, the multiplier will start decreasing.
  * The minimum multiplier is 0.1.
# Command Line Options #
You can get the full help text by running BLR with "--help".

Here is a list of available command line options.

|--help           |Print command line usage and exit.                                         |
|:----------------|:--------------------------------------------------------------------------|
|--version        |Print version and exit.                                                    |
|--start=x,y      |Start free play mode directly from level x part y. The part must be valid. |
|--nosound        |Forcibly use no sound.                                                     |
|--fullscreen=1/0 |Forcibly use fullscreen/windowed. This will override your configuration.   |
|--vidmode=0~4    |Forcibly use specific video mode instead the one in the configuration.     |
|--firststartup   |Forcibly run first start up. The score file will be preserved if exist.    |
|--fast           |Fast mode. All levels are two times shorter.                               |
|--logfile=...    |Use an alternate log file name instead of the default "BLRLOG.txt".        |
|--nohideconsole  |Do not hide console (Windows version only).                                |