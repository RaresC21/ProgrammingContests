#!/bin/bash

read_file() {
    read -r header < "$1"
    if [[ "$header" == "#include <bits/stdc++.h>" ]]
    then
        while IFS='' read -r line || [[ -n "$line" ]]; do
            printf '%s\n' "$line" >> sol.cpp
        done < "$1"
    else
        new_file_name=$(echo "$header" | cut -d'<' -f2 | cut -d'>' -f1)
        read_file $new_file_name

        while IFS='' read -r line || [[ -n "$line" ]]; do
            if ! [[ "$line" =~ "#include" ]]
            then
                printf '%s\n' "$line" >> sol.cpp
            fi
        done < "$1"
    fi
}

read_file "$1"