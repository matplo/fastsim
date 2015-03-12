#!/bin/bash

. $(brew --prefix root)/libexec/thisroot.sh

rver=$(root-config --version)

export PS1="(R$rver):$PS1"

export ROOTSYS=$(root-config --prefix)
