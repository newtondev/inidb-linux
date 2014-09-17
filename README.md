inidb-linux
===========

<<<<<<< HEAD
@inidb Arma 3 extension for Linux by LimpinBizkit (http://steamcommunity.com/id/kratosza). A simple server-side database extension using INI files on Linux.

A port to Linux C++ of the project (Windows VC) found here https://github.com/code34/-inidbi by:
* nicolas_boiteux@yahoo.fr
* SicSemperTyrannis

This is still under development with no release at this time. Will keep you posted.

## How to Install
~~~
sudo -i 
cd /etc/apt/sources.list.d
echo "deb http://old-releases.ubuntu.com/ubuntu/ raring main restricted universe multiverse" >ia32-libs-raring.list
apt-get update
apt-get install build-essential g++ gcc-4.8 gcc-4.8-dev libc6-dev-i386 ia32-libs g++-4.8-multilib
exit

git clone <reponame>
cd <reponame>
./build.sh
~~~

How to use:
To use "iniDB" in your mission, install the extension in your ARMA2 or ARMA3 directory by copying the entire "@inidb" folder included in the download to your root directory.
Don't forget to copy over over or create the /db/ folder.
It should look like: /Arma 3/@inidbi/iniDB.so
It should look like: /Arma 3/@inidbi/db/
It should look like: /Arma 3/@inidbi/Addons/inidbi.pbo
=======
@inidb Arma 3 extension ported to Linux by LimpinBizkit (http://steamcommunity.com/id/kratosza).

A simple server-side database extension using INI files. A port of the project found here: https://github.com/code34/-inidbi

This is still under development with no release at this time. Will keep you posted.
>>>>>>> 7bc00638d2d6f5a76aca843c7b88c30db52f79dc
