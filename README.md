Currently supports versions until 0.5.

This updates the path for the session. To use V in a terminal session with this tool, put that into ~/.bashrc or whatever the equivalent is in the shell used or type `source run.sh switch ` and then whatever version, but it has to be in whatever directory run.sh. Don't run it like `./run.sh switch ` and so on, because then it won't work as intented.

This is how:

`source run.sh install 0.4.10` to install that version of V.

`source run.sh switch 0.5.0` to switch to that version of V.

Note: For versions that can be written with `.0` at the end, that `.0` at the end is ooptional.
