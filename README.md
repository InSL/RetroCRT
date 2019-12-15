# Some License Nonsense

RetroCRT :: Utility suite to configure RetroPie for a CRT

Copyright (C) 2019 Duncan Brown (https://github.com/xovox)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

# RetroCRT

RetroCRT is a suite of tools designed to make [RetroPie](https://retropie.org.uk) gaming on CRTs easy and user friendly.

![alt text](https://raw.githubusercontent.com/xovox/RetroCRT-Media/master/RetroCRT-240p/NES_Mockup.jpg)


# Supported Hardware

* [RetroTink Ultimate](http://www.retrotink.com)
  * Component & RGB only, for now
* [pi2jamma](http://arcadeforge.net/Pi2Jamma-Pi2SCART/Pi2Jamma::248.html)
  * JAMMA controls are currently unsupported, but will be
* [pi2scart](http://arcadeforge.net/Pi2Jamma-Pi2SCART/PI2SCART::264.html)
* [GERT VGA 666](https://github.com/PiSupply/Gert-VGA-666)
  * You can buy it on [Amazon](amazon.com/Raspberry-Adapter-Board-Atomic-Market/dp/B075DM4C5V)

See [the bugs list](#bugs) to see what's known to not work, or not fully work.

# Downloads

[The release page](https://github.com/xovox/RetroCRT/releases) has any, and all, pre-built images ready to go.

# What You Get

* My 240p EmulationStation theme, [https://github.com/xovox/es-theme-RetroCRT-240p](RetroCRT 240p)!
* 240p test suite roms for several console platforms!
* Easy installation!
* Pixel-perfect console emulation!
* Pixel-perfect arcade emulation for most games!
  * This is achieved with on-load screen resolution changes!
* Automatic rotation for vertical games!
* Installation of CRT Friendly EmulationStation themes!
* No system messages on boot/shutdown/reboot!
* No annoying EmulationStation yellow text!
* My unbridled enthusiasm about building this project!

## Future Supported Hardware

* Other RetroTink connections
  * S-Video & composite do not work 100%
* Raspberry Pi built-in composite out (untested)

# NTSC vs SECAM & PAL

Sadly, I don't have a SECAM or PAL setup to test everything on, I'll need someone else to do that for me.

# Installation

## Images

[Download the pre-built image](https://github.com/xovox/RetroCRT/releases).

## DIY

I'm assuming you're able to SSH in, or have a monitor & keyboard. I typically connect my Pi via Ethernet when I'm first configuring it for ease.

You can also do the initial configuration with a monitor hooked up to HDMI.

* [Enabling SSH](https://www.raspberrypi.org/documentation/remote-access/ssh/) on the official Raspbian docs.
  * This is best solved by putting your SD card in another machine and creating an empty file called 'ssh' in the boot partition.
* [Wireless Connectivity](https://www.raspberrypi.org/documentation/configuration/wireless/README.md) is an option, but I prefer wired for simplicity.
* SSH Clients
  * [Windows](https://www.raspberrypi.org/documentation/remote-access/ssh/windows.md)
  * [Linux & macOS](https://www.raspberrypi.org/documentation/remote-access/ssh/unix.md)

You can cut & paste this into your terminal.

```
cd &&
git clone https://github.com/xovox/RetroCRT &&
cd RetroCRT &&
/bin/bash ./retrocrt_setup.sh
```

# TV Compatibility

This should work for all NTSC TVs, but these are ones that have been tested.

## CRTs Behaving Badly

Flat Trinitrons and many other more modern CRTs perform processing on 240p signals.  This may mean you'll see text "jumping" or weird ghosting effects happening on screen. This cannot be disabled on the TV.

## NTSC

| Make 		| Model 	| Tested 	| Issues
|------		|-------	|--------	|--------
| Panasonic	| CT-27D10	| Component	| None
| Magnavox      | 20MS3442/17   | Component     | None

# Troubleshooting

Before doing anything else, update RetroCRT!  You can do this 
See the [troubleshooting doc](TROUBLESHOOTING.md).

# Bugs

- runcommand doesn't work, joy2key or something else isn't working.

# TODO

* Outputs
  * RetroTink S-Video Output
  * RetroTink Component Output
  * 3.5mm Composite Output

* Video
  * Collect PAL timings
  * Collect SECAM timings

# Copying to NTFS

```
sudo rsync -rt  --progress ./ /tmp/a/retropie-mount/
```
# Footnotes

I am not affiliated with Mike Chi, RetroTink, pi2jamma, or anyone else.  I'm doing this as a personal project.

Shout out to [Vykran](https://github.com/Vykyan/retroTINK-setup) for the initial groundwork, though he seems to be PAL & I'm NTSC... which brought us to where we are now.

# theme

* https://retropie.org.uk/forum/topic/24277/my-clean-simple-240p-es-theme-retrocrt/2

```
                                                       .
                                                       ;\
                                                      /  \
                                                      `.  i          ,^^--.
                                                   ___  i  \        /      \              ,',^-_
                                                  /   \ !   \       |       |            / /   /
                                                  \   /  \   \      |       ;      ,__. |    ,'
                                                   4 |    \   `.    |      /      (    `   __>
                                                 ,_| |_.   \    `-__>      >.      `---'\ /
                                                /,.   ..\   `.               `.         | |
                                                U |   | U     `.               \    ,--~   ~--.
--~~~~--_       _--~~~~--_       _--~~~~--_       _--~~~~--_    \  _--~~~~--_   \  /_--~~~~--_ \
         `.   ,'          `.   ,'          `.   ,'          `.  |,'          `.  \,'          `.
           \ /              \ /              \ /              \ /              \ /              \
```

|  |
