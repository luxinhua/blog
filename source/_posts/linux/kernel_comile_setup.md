---
title: kernel debug envirment setup 
date: 2021/12/16
categories: linux
---

---
### install OS: 
---
	Ubuntu 20.04.3 LTS (Focal Fossa)

---
### dependence
---
    sudo  apt-get install build-essential kernel-package libncurses5-dev　flex bison libssl-dev 
   
---
### download source code
---
    xhlu@xhlu-Default-string:~$ uname -a  // check kernel version 
    Linux xhlu-Default-string 5.11.0-27-generic #29~20.04.1-Ubuntu SMP Wed Aug 11 15:58:17 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
   
   download version (5.11.*) your need from https://www.kernel.org/pub/linux/kernel/v5.x
    
    sudo  apt-get install aria2
    aria2c  --max-connection-per-server=4 --min-split-size=1M  https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.11.19.tar.gz
    tar xvf linux-5.11.19.tar.gz
    cd linux-5.11.19

---
### start compile
---
    make menuconfig  // nothing to change , save to .config
    vim .config  // change string to CONFIG_SYSTEM_TRUSTED_KEYS=""
    make-kpkg clean
    export CONCURRENCY_LEVEL=$(noproc)  // compile multi-core support
    time fakeroot make-kpkg --initrd --append-to-version=amd336 kernel-image kernel-headers

---
### install kernel
---
    finish compile ，there will be 2 deb package in path "../"
   	
        linux-headers-5.11.19amd336_5.11.19amd336-10.00.Custom_amd64.deb
        linux-image-5.11.19amd336_5.11.19amd336-10.00.Custom_amd64.deb
   
    sudo dpkg -i linux-*.deb 
    sudo reboot 
    choose your kernel to boot 
    Edit /etc/default/grub ,  
		comment GRUB_TIMEOUT_STYLE=hidden
		change GRUB_TIMEOUT to "GRUB_TIMEOUT=10", 
		update-grub.  
    
    you can find the boot menu when reboot. kernel debug envirment setup: 
