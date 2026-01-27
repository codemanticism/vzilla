A manager specifically for the V language that is a work in progress. **Note: this scripts messes with the /usr/bin directory of the system, so you might want to be careful.** Fortunately, I use an immutable Linux distribution because of the increased safety.

This updates the $PATH environment variable for the session. To use V in a terminal session with this tool, put that into `~/.bashrc` or whatever the equivalent is in the shell used or type `source `, then whatever directory, ` switch ` and then whatever version, but it has to be in whatever directory `vzilla.sh` properly. Don't run it the normal way (`./vzilla.sh` and so on and so forth), because then it won't work as intented.

This is how:

`source vzilla.sh install 0.4.10` to install that version of V.

`source vzilla.sh switch 0.5.0` to switch to that version of V.

I originally wrote this in C. Ideally, this could get converted to the V code for improved safety and also it would make more intuitive sense. My plan is getting this on package managers of Linux distros. 

Currently supports V release versions until 0.5.

Note: For versions that can be written with `.0` at the end, that `.0` at the end is optional.
