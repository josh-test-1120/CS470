# Author: Joshua Summers
# Lab1 Assignment
echo "Lab1 Program Start"

# Languages array
languages=("Java" "C#" "JavaScript" "C++" "Python" "Ruby" \
 "Perl" "PHP" "Assembly" "Swift")

# Get the current date and time in string format
current_date=$(date +"%Y-%m-%d-%H-%M-%S")
# Create the main directory
mkdir $current_date
cd $current_date

# Iterate through the numbers 1 and 10 for subfolders
for i in {1..10}; do
    # Capture index string in variable
    index=$((i))
    # Format the sub folder names
    if [ $i -lt 10 ]; then subname="file10"$index
    else subname="file1"$index
    fi
    # Create the sub folder
    mkdir $subname
    cd $subname
    # Create the text file
    filename="tuser5"$index".txt"
    # Put the language string into the filename based on index - 1
    echo ${languages[$i-1]} > $filename
    # Go back a directory
    cd ".."
done

echo "Program Complete"
