#!/bin/bash

email=$(git config --global user.email)

current_year=$(date +"%Y")
current_month=$(date +"%m")
current_day=$(date +"%d")

latest_year=$current_year
latest_day=25

if [ $current_month -lt 12 ]
then
    latest_year=$((current_year-1))
else
    latest_day=$current_day
fi

for year in $(eval echo "{2015..${latest_year}}")
do
    echo "Downloading ${year}'s input..."
    day_range=$(eval echo {1..25})

    if [ $year -eq $latest_year ] && [ $latest_day -lt 25 ]
    then
        day_range=$(eval echo "1..${latest_day}")
    fi

    for day in $day_range
    do
        url="https://adventofcode.com/${year}/day/${day}/input"
        input_file="input/${year}/day$(printf '%02d' $day).in"

        if [ ! -f $input_file ]
        then
            curl -s -A "${email}" --cookie cookies.txt "${url}" -o "${input_file}" --create-dirs > /dev/null
        fi
    done
    echo "Completed!"
done
