
Debian
====================
This directory contains files used to package playtd/playt-qt
for Debian-based Linux systems. If you compile playtd/playt-qt yourself, there are some useful files here.

## playt: URI support ##


playt-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install playt-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your playt-qt binary to `/usr/bin`
and the `../../share/pixmaps/playt128.png` to `/usr/share/pixmaps`

playt-qt.protocol (KDE)

