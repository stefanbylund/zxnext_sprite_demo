# Demonstration of zxnext_sprite

The **zxnext_sprite_demo** project contains a simple example program demonstrating
how to use the [zxnext_sprite](https://github.com/stefanbylund/zxnext_sprite) C
hardware sprite API for the Sinclair ZX Spectrum Next.

**Note:** This demo still works but is a bit out-of-date. It will be updated
someday when I have the time ;)

## Download

The latest version of this program can be downloaded **[here](build/zxnext_sprite_demo.zip)**.
This download contains the following binaries and resources:

* zxnext_sprite_demo/zxnext_sprite_demo.nex
* zxnext_sprite_demo/zxnext_sprite_demo.c
* zxnext_sprite_demo/readme.txt

The included readme.txt file explains how to start the program.

If you want to build the zxnext_sprite_demo program yourself, see the "How to Build"
section below.

## How to Build

If you want to build the zxnext_sprite_demo program yourself, follow the steps
below:

1. On Windows, you need [MinGW](http://www.mingw.org/),
[UnxUtils](https://sourceforge.net/projects/unxutils/) or
[Cygwin](https://www.cygwin.com/) for the basic Unix commands. Add the chosen
set of Unix commands to your path.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and the
[ZEsarUX](https://github.com/chernandezba/zesarux) or
[CSpect](https://dailly.blogspot.se/) emulator.

3. Download [zxnext_sprite](https://github.com/stefanbylund/zxnext_sprite/blob/master/build/zxnext_sprite.zip)
and unpack it in a suitable place.

4. Download the zxnext_sprite_demo repository either as a ZIP archive using the
"Clone or download" button at the top of this page or with Git using the
following command:

> git clone https://github.com/stefanbylund/zxnext_sprite_demo.git

5. Make sure the zxnext_sprite and zxnext_sprite_demo directories are located in
a common parent directory.

6. Go to the zxnext_sprite_demo directory and enter the following command to
build a NEX file:

> make all

7. Run the zxnext_sprite_demo/bin/\<compiler-flavour\>/zxnext_sprite_demo.nex
file in the ZEsarUX or CSpect emulator.

**Tip:** If you don't care for makefiles or don't want to install
MinGW/UnxUtils/Cygwin on Windows, you can build zxnext_sprite_demo manually
by using the z88dk command-line invocation located in the header of the
zxnext_sprite_demo.c source file.

**Tip:** To start the ZEsarUX emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> zesarux --noconfigfile --machine tbblue --enabletimexvideo --tbblue-fast-boot-mode
  --quickexit --enable-esxdos-handler --esxdos-root-dir <zxnext_sprite_demo_folder>
  zxnext_sprite_demo.nex

**Tip:** To start the CSpect emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> CSpect -w2 -tv -zxnext -mmc=<zxnext_sprite_demo_folder>/ zxnext_sprite_demo.nex

## License

This software is licensed under the terms of the MIT license.
