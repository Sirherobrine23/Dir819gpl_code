Note: this GPL only support 32 bit Linux System.

Step1: Install Fedora Linux 19 ,and make sure you connect to internet
       1)You must execute the following command :
             i  ) yum install gcc-c++
             ii ) yum install kernel-devel 
             iii) yum install ncurses-devel.i686
             iv ) yum install zlib-devel
             v  ) yum install automake
             vi ) yum install bison flex
             vii) yum install openssl-devel
Step2:  Setup Build Environment ($means command)
          1 ) Please login with root user such as john, and copy the gpl file to folder,
              such as the folder /home/john
          2 ) # cd /home/john
              # tar -zxvf DIR819_V1.06B02_GPLCode_20190801.tar.gz
                You will get seven files :
				 DIR819_v1.06  
                 GPL_License_List.pdf 
                 readme.txt 
                 LICENSE.txt          
                 toolschain
                 DIR-819_middle1.bin
                 DIR-819_middle2.bin
          3 ) # cp -rf toolschain/buildroot-gcc342 /opt/     
          4 ) # cd toolschain/lzma-4.32.7    
          5 ) # ./configure  
          6 ) # make
          7 ) # make install (install lzma to /usr/local/bin)
Step 3. Building the image
         1 ) # cd /home/john/
         2 ) # cd DIR819_v1.06/                    
         3 ) # make prepare          
         4 ) # make tools
         5 ) # make
         6 ) After make successfully, you will find the image file DIR-819_A1_v1.06.bin in ./build/romfs/DIR-819_A1_v1.06.bin
How to install?
        a) First of all, the software compiled by the GPL does not support encryption, but the software inside your device (Office Shipping Firmware) supports. So you need to update the middle version1 firstly. And then upgrade the gpl-compiled software. If you want to upgrade back to Office Shipping Firmware, upgrade the middle version2 firstly. And then upgrade Office Shipping Firmware (Please refer your user manual)

           *NOTE*, I have to say, if you modified something and cause some errors, the device may not be able to restart again.

           So, PLEASE MAKE SURE YOU REALLY KNOW WHAT YOU ARE DOING BEFORE YOU UPGRADE ANY UNOFFICIAL FIRMWARE.
Note
		A compressed document called var.tar is generated under /home/john/DIR819_v1.06/build.DIR-819/romfs/rootfs/etc when you've compiled it. You can unzip this compressed document to view its contents by following instructions:
		# cd /home/john/DIR819_v1.06/build.DIR-819/romfs/rootfs/etc
		# tar -xf var.tar
