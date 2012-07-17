KioskMode
=========

A useful (but dangerous!) app for putting a Mac into a locked-down "kiosk" mode. 
A minimal amount of key commands are supported (see below), but more can be added
easily in main.c.

About
=========

We run this app in installations on things like touchscreens that are user-facing. 
It is espcially handy when keyboards come into play.

Right now, it prevents the following key commands:
* changing spaces (control + arrow key)
* enter/exit chrome in fullscreen (command + shift + F, control + command + f )
* tab switch to application (command + tab)
* quit application (command + q)
* open spotlight (command + space)
* new tab (browser) (command + t)
* close window (command + w)

Running
=========

KioskMode is a headless app that is best run via the command line. Again, be careful!
You can get stuck locked into an app pretty easily if you don't know what you're up to.

The app needs to be run as root. This means it must either be run from the command line
as sudo, OR you can set-uid root. We do the latter like so:

1. Copy KioskMode/Release/KioskMode to /Applications
2. open Terminal
3. type: "sudo chmod 4755 /Applications/KioskMode" and hit enter

Now you can run the app just by double clicking (it will open Terminal to run) or via a script.
The app must be killed via a script, for example:

1. open Terminal
2. type "ps -A | grep KioskMode" and hit enter
   you should see a list like this:
   27219 ttys000    0:00.03 /Applications/KioskMode
   27288 ttys001    0:00.00 grep KioskMode
3. copy the first number on the /Applications/KioskMode line (in this case 27219)
4. type "kill NUMBER_YOU_COPIED" and hit enter