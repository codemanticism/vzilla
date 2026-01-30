#!/bin/bash
cd ~/.local/bin
rm vzilla
rm vzilla-c
echo " " > vzillash.sh
wget https://raw.githubusercontent.com/codemanticism/vzilla/refs/heads/master/vzilla
wget https://raw.githubusercontent.com/codemanticism/vzilla/refs/heads/master/vzilla-c
chmod +x vzilla-c
chmod +x vzillash.sh
chmod +x vzilla
echo 'vzilla_func() {
    cd ~/.local/bin
    source vzilla $1 $2
    cd -
}
alias vzilla="vzilla_func"' >> ~/.bashrc
cd -
echo "Exit the session and then re-enter."
