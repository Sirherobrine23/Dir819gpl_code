Note: this GPL only support 32 bit Linux System.

Step1: Install Fedora Linux 19 ,and make sure you connect to internet
       1)You must execute the following command :
             i  ) yum install gcc-c++
             ii ) yum install kernel-devel 
             iii) yum install ncurses-devel.i686
             iv ) yum install zlib-devel
             v  ) yum install automake
             vi ) yum install bison flex
Step2:  Setup Build Environment ($means command)
          1 ) Please login with root user such as john, and copy the gpl file to folder,
              such as the folder /home/john
          2 ) #cd /home/john
              # tar -xvzf DIR819A1_v1.00.tar.gz
                 You will get five files :
                 GPL_License_List.pdf 
                 readme.txt
                 DIR819   
                 LICENSE.txt          
                 toolschain
          4 ) #cp -rf toolschain/buildroot-gcc342 /opt/     
          9 ) #cd toolschain/lzma-4.32.7    
          10) #./configure  
          11) #make
          12) #make install (install lzma to /usr/local/bin)
Step 3. Building the image
         1) #cd /home/john/DIR819/                    
         2) #make prepare          
         3) #make tools
         4) #make
         5) After make successfully, you will find the image file DIR-819.bin in ./build/romfs/DIR-819.bin
