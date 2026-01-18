#!/bin/bash
read -p "Enter the path of the directory to delete: " dir_path
if [ -d "$dir_path" ]; 
then
    rm -rf "$dir_path"
    echo "Directory deleted successfully!"
else
    echo "Directory does not exist!"
fi
echo "Press any key to terminate..."
read -n1 char
