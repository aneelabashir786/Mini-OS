#!/bin/bash
read -p "Enter file name: " filename
if [ -f "$filename" ]; then
    xdg-open "$filename"
else
    echo "File not found."
fi
echo "Press any key to terminate..."
read -n1 char
