#!/bin/bash
echo "Enter source file path:"
read src_path
if [ ! -f "$src_path" ]; 
then
    echo "Error: File does not exist at path $src_path"
    exit 1
fi
echo "Enter destination path:"
read dst_path
cp "$src_path" "$dst_path"
echo "File copied successfully"
echo "Press any key to terminate..."
read -n1 char
