inidb-linux
===========

@inidb Arma 3 extension for Linux by LimpinBizkit (http://steamcommunity.com/id/kratosza). A simple server-side database extension using INI files on Linux.

A port to Linux C++ of the project (Windows VC) found here https://github.com/code34/-inidbi by:
* nicolas_boiteux@yahoo.fr
* SicSemperTyrannis

This is the first reasonably stable release. Please let me know if there are any issues.

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
To use "iniDB" in your mission, install the extension in your ARMA2 or ARMA3 directory by making an @inidb folder in the root of your ArmA3 installation and copying over the files required.
Don't forget to create a /db/ folder where your db files will be stored per player.
It should look like: /Arma 3/@inidbi/iniDB.so
It should look like: /Arma 3/@inidbi/db/
It should look like: /Arma 3/@inidbi/Addons/inidbi.pbo

Please feel free to get in contact with me on steam if you require my assistance. My details are mentioned above.

Thanks
