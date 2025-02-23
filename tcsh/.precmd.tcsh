set __prompt_key_color="${__host_color}"
if (! $__last_code == 0) set __prompt_key_color="%{\033[38;2;231;130;132m%}"
set prompt="${__host_color}%n@%m ${__git_color}`__git_current_branch`${__path_color}%C ${__prompt_key_color}${__prompt_key}${__reset_color}${__reset_cursor} "
