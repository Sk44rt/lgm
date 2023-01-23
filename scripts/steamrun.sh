#!/bin/bash
# steamlaunch

flatpak run com.valvesoftware.Steam -applaunch $1 2>&1 | tee >(
  while read line; do
    if [[ $line == *"Game process removed: AppID $1"* ]]; then
      flatpak run com.valvesoftware.Steam -shutdown; break
    fi
  done
)
