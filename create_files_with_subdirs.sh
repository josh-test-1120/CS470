# Author: Joshua Summers
# Lab1 Assignment
# This script will create a directory based on the string
# format for the current date and time (concatenated together)
# This folder will contain 10 subfolders and in each subfolder
# it will create a file that has a unique programming language
# listed as a string

# Output the string to the stdout using the 'echo' command
echo "Lab1 Program Start"

# Languages array syntax that will hold the languages known
# Array is created with () symbols and space separated
languages=("Java" "C#" "JavaScript" "C++" "Python" "Ruby" \
 "Perl" "PHP" "Assembly" "Swift")

# Get the current date and time in string format
# Use the date command, but output the string based on the formatter
# Assign to the current_date variable
current_date=$(date +"%Y-%m-%d-%H-%M-%S")
# Create the main directory
# Make Directory is called with 'mkdir' referencing current_date variable
mkdir $current_date
# Change Directory is called with 'cd' referencing current_date variable
cd $current_date

# Iterate through the numbers 1 and 10 for subfolders
for i in {1..10}; do
    # Capture index string in variable that references the current i integer
    index=$((i))
    # Format the sub folder names
    # If else loop is called with if;then...else...fi
    # String and variable concatenation is stored in subname variable
    if [ $i -lt 10 ]; then subname="file10"$index
    else subname="file1"$index
    fi
    # Create the sub folder
    # Make Directory is called with 'mkdir' referencing subname variable
    mkdir $subname
    # Change Directory is called with 'cd' referencing subname variable
    cd $subname
    # Create the text file
    # String and variable concatenation is stored in filename variable
    filename="tuser5"$index".txt"
    # Put the language string into the filename based on index - 1
    # The 'echo' command sends a string and the '>' redirects the output
    # to the filename variable (a file is created or overwritten)
    # Languages array is accessed as a variable with the '{}' sybmols
    # and '[]' symbols for the index of the element
    echo ${languages[$i-1]} > $filename
    # Go back a directory
    # Change Directory is called with 'cd' referencing the parent directory
    # symbol '..'
    cd ".."
done
# Output the string to the stdout using the 'echo' command
echo "Program Complete"
