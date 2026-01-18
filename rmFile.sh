#!/bin/bash
echo "Enter the file path:"
read file_path
if [ -f "$file_path" ]; 
then
  rm "$file_path"
  echo "File $file_path deleted successfully."
else
  echo "File $file_path not found."
fi
echo "Press any key to terminate..."
read -n1 char
