Demonstration of zxnext_sprite
==============================

The zxnext_sprite_demo is a simple example program demonstrating how to use the
zxnext_sprite (https://github.com/stefanbylund/zxnext_sprite) C hardware sprite
API for the Sinclair ZX Spectrum Next.

The zxnext_sprite_demo project is available on GitHub at:
https://github.com/stefanbylund/zxnext_sprite_demo

Run in CSpect emulator
----------------------

1. The absolute path to the zxnext_sprite_demo folder (i.e. this folder) is
   denoted as <zxnext_sprite_demo>.

2. Install the latest version of the CSpect emulator from https://dailly.blogspot.se/.

3. Run the zxnext_sprite_demo.sna file in the CSpect emulator:

> CSpect.exe -zxnext -mmc=<zxnext_sprite_demo>/ <zxnext_sprite_demo>/zxnext_sprite_demo.sna

Note that the -mmc path must end with a / or \ character!

Run in ZEsarUX emulator
-----------------------

1. The absolute path to the zxnext_sprite_demo folder (i.e. this folder) is
   denoted as <zxnext_sprite_demo>.

2. Install the latest version of the ZEsarUX emulator from https://sourceforge.net/projects/zesarux/.

3. Run the zxnext_sprite_demo.tap file in the ZEsarUX emulator:

> zesarux.exe --machine tbblue --enable-mmc --enable-divmmc-ports --mmc-file tbblue.mmc
  --quickexit --tape <zxnext_sprite_demo>/zxnext_sprite_demo.tap
