#!/bin/lua

function Print_finished()
print("\n!!! UNINSTALL SCRIPT FINISHED !!!")
end

os.execute("sudo rm -r /usr/share/bash-completion/completions/passman ~/.local/share/passman ~/.config/passman /usr/share/fish/completions/passman.fish  /bin/passman")
Print_finished()
