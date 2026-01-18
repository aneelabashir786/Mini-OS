#!/bin/bash
echo "Enter directory name: "
read dir_name
mkdir "$dir_name"
echo "Directory created: $dir_name"
echo "Press any key to terminate..."
read -n1 char
