#!/bin/bash

reset="\033[0m"
red="\033[1;31m"
green="\033[32m"
yellow="\033[1;33m"
blue="\033[34m"
purple="\033[35m"

# A function to handle the 'mkdir' command
handle_mkdir() {
    # Check if file_name is provided
    if [ -z "$2" ]; then
        echo "Please provide a directory name"
        return 1
    fi
    # Create directory
    mkdir "$2"
    echo "Directory '$2' created."
}

command()
{
    local cmd=$@
    echo -e "${yellow} $cmd"
    "$@"
}

# Handle different commands
csim()
{
    case "$1" in
        mkdir)
            handle_mkdir "$@";;
        remove)
            local num_of_arg=$# 
            if [[ $num_of_arg -lt 3 ]]; then
                echo -e "${red} you are passing $# argument, please add file_name or folder_name"
                echo -e "${green} Usage: csim remove {file|folder} <file_name|folder_name>"
            else
                case "$2" in
                    file)
                        local file_name=$3
                        if [[ -e $file_name ]]; then
                            command rm -f $file_name
                        else
                            echo -e "${red} $file_name does not exist"
                        fi
                        ;;
                    folder)
                        local folder=$3 
                        rm -rf $folder;;
                esac
            fi;;
        find)
            local file_name=$2  
            find -iname $file_name
            if [[ ! -e $file_name ]]; then
                echo -e "${red} $file_name does not exist"
            fi
            ;;
        *)
            echo "Unknown command: $1"
            return 1
            ;;
    esac
}

# Enable Tab Completion for csim command
_complete_csim() {
    local cur prev opts
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="mkdir remove find"

    if [[ ${COMP_CWORD} -eq 1 ]]; then
        # After 'csim', complete the command options (e.g., 'remove')
        COMPREPLY=( $(compgen -W "$opts" -- $cur) )
        return 0
    fi

    if [[ ${COMP_WORDS[1]} == "remove" ]]; then
        # After 'csim remove', complete the sub-options ('file' or 'folder')
        if [[ ${COMP_CWORD} -eq 2 ]]; then
            opts="file folder"
            COMPREPLY=( $(compgen -W "$opts" -- $cur) )
            return 0
        fi

        # # After 'csim remove file' or 'csim remove folder', complete file/folder names
        # if [[ ${COMP_WORDS[2]} == "file" || ${COMP_WORDS[2]} == "folder" ]]; then
        #     # Suggest file/folder names based on whether the user is typing file or folder
        #     local path=""
        #     if [[ ${COMP_WORDS[2]} == "file" ]]; then
        #         path="*"
        #     elif [[ ${COMP_WORDS[2]} == "folder" ]]; then
        #         path="*/"
        #     fi
        #     COMPREPLY=( $(compgen -f -- "$path$cur") )
        #     return 0
        # fi
    fi

    return 0
}

# Tell Bash to use _complete_csim for tab completion of 'csim'
complete -F _complete_csim csim

