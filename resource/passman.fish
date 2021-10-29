#!/bin/fish

set -l long --help --no-config --lenght= --quiet
set -l short -q -h -l
set -l commands gen add status purge get rm

complete -c passman -f -a "$long $short $commands"
