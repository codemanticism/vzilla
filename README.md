A manager specifically for the V language.

<b> This is a work in progress. </b>

Note: this scripts messes with the /usr/bin directory of the system, so you might want to be careful.

I originally wrote this in C. Ideally, this could get converted to the V code. My plan is getting this on package managers of Linux distros. 

Currently supports V release versions until 0.5.

This updates the path environment variable for the session. To use V in a terminal session with this tool, put that into `~/.bashrc` or whatever the equivalent is in the shell used or type `source `, then whatever directory, `run.sh switch ` and then whatever version, but it has to be in whatever directory `run.sh` properly. Don't run it the normal way (`./run.sh and so on and so forth), because then it won't work as intented.

This is how:

`source run.sh install 0.4.10` to install that version of V.

`source run.sh switch 0.5.0` to switch to that version of V.

Note: For versions that can be written with `.0` at the end, that `.0` at the end is optional.
