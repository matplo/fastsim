#!/bin/bash

if [ "$1" == "download" ]; then
	echo "[i] downloading..."
	./enoter.py --filter "snips" --no-cache --prod
fi

./enoter.py --make-pages --filter "snips" --force --single
