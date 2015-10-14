#!/bin/bash

find . -name "*.log" -exec tail -v -n 1 {} \;

