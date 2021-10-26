#/bin/bash


_passman(){
 local cur prev opts

    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    prev_prev="${COMP_WORDS[COMP_CWORD-2]}"
    opts="--help --no-config --lenght= --quiet -q -h -l "
    commands="gen add status purge get rm "


    if [[ ${cur} == -* ]] ; then
        COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
        return 0
elif [[ ${prev} == gen ]] ; then
    COMPREPLY=()
	return 0 
elif [[ ${prev} == get ]] ; then
	COMPREPLY=() #TODO completion list from ids file
	return 0 
elif [[ ${prev} == rm ]] ; then
    COMPREPLY=()
	return 0 
elif [[ ${prev} == add ]] || [[ ${prev_prev} == add ]] ; then
    COMPREPLY=()
	return 0 
else
        COMPREPLY=( $(compgen -W "${commands}" -- ${cur}) )
        return 0
    fi
}

complete -F _passman passman
