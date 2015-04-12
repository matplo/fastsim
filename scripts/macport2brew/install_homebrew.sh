#!/bin/bash
#https://github.com/Homebrew/homebrew/blob/master/share/doc/homebrew/Installation.md#installation

ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

brew update
brew upgrade
brew doctor
