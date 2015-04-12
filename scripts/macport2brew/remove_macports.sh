#!/bin/bash

#http://bitboxer.de/2010/06/03/moving-from-macports-to-homebrew/

sudo port -f uninstall installed

sudo rm -rf /opt/local
sudo rm -rf /Applications/DarwinPorts
sudo rm -rf /Applications/MacPorts
sudo rm -rf /Library/LaunchDaemons/org.macports.*
sudo rm -rf /Library/Receipts/DarwinPorts*.pkg
sudo rm -rf /Library/Receipts/MacPorts*.pkg
sudo rm -rf /Library/StartupItems/DarwinPortsStartup
sudo rm -rf /Library/Tcl/darwinports1.0
sudo rm -rf /Library/Tcl/macports1.0
sudo rm -rf ~/.macports

#After that you should remove the /opt/local/bin from your $PATH.


