inidb-linux
===========

@inidb Arma 3 extension ported to Linux by LimpinBizkit (http://steamcommunity.com/id/kratosza).

A simple server-side database extension using INI files. A port of the project found here: https://github.com/code34/-inidbi

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
