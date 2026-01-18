#!/bin/bash
echo "Enter the path of the file you want to move: "
read file_path
if [ ! -f "$file_path" ]; then
  echo "Error: File not found."
  exit 1
fi
echo "Enter the destination path for the file: "
read dest_path
if [ ! -d "$dest_path" ]; then
  echo "Error: Destination directory not found."
  exit 1
fi
mv "$file_path" "$dest_path/"
echo "File moved successfully."
echo "Press any key to terminate..."
read -n1 char
