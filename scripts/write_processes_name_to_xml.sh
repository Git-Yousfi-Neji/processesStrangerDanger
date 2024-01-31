#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file path>"
    exit 1
fi
xml_file="$1"

username_exists() {
    local username="$1"
    local xml_file="$2"

    grep -q "<systemUsernames>$username</systemUsernames>" "$xml_file" && return 0

    return 1
}

add_username_to_xml() {
    local username="$1"
    local xml_file="$2"

    if grep -q "</root>" "$xml_file"; then
        sed -i "/<\/root>/i \<systemUsernames>$username</systemUsernames>" "$xml_file"
    else
        echo "<systemUsernames>$username</systemUsernames>" >> "$xml_file"
    fi
}

for proc_dir in /proc/*/; do
    proc_id=$(basename "$proc_dir")
    
    if [[ -d "$proc_dir" && "$proc_id" =~ ^[0-9]+$ ]]; then
        process_name=$(ps -o comm= -p $proc_id)
        if ! username_exists "$process_name" "$xml_file"; then
            echo "Found process Id = $proc_dir process Name=$process_name"
            add_username_to_xml "$process_name" "$xml_file"
        fi
    fi
done

echo "Process names successfully added to the XML file."
