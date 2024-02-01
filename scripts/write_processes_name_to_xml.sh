#!/bin/bash

RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
RESET='\e[0m'

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file path>"
    exit 1
fi

xml_file="$1"
counter=0

username_exists() {
    local username="$1"
    local xml_file="$2"

    if grep -q "<systemUsernames>$username</systemUsernames>" "$xml_file"; then
        echo -e "${YELLOW}Skip${RESET} ${RED}[$username]${RESET} ${GREEN}found in db${RESET}" && return 0
    fi

    return 1
}

add_username_to_xml() {
    local username="$1"
    local xml_file="$2"

    if grep -q "</root>" "$xml_file"; then
        sed -i "/<\/root>/i \\t<systemUsernames>$username</systemUsernames>" "$xml_file"
    else
        echo -e "\t<systemUsernames>$username</systemUsernames>" >> "$xml_file"
    fi

    ((counter++))
}

for proc_dir in /proc/*/; do
    proc_id=$(basename "$proc_dir")
    
    if [[ -d "$proc_dir" && "$proc_id" =~ ^[0-9]+$ ]]; then
        process_name=$(ps -o comm= -p "$proc_id")
        if ! username_exists "$process_name" "$xml_file"; then
            echo -e "${GREEN}Adding${RESET}[$process_name] ${GREEN}to db${RESET}"
            add_username_to_xml "$process_name" "$xml_file"
        fi
    fi
done

echo "Added $counter process names to the XML file."
