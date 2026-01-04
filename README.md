# Password Vault - Encrypted password manager

With Password Vault you can store your passwords encrypted and locally on your machine.
The password records are seperate from the application and can be copied to multiple machines.

Building the application
This application required Qt installed on your machine. I have built and tested the application with Qt5.

Build steps:
1. Clone the repo
2. Create makefile
``
qmake -o Makefile password_vault.pro
``

3. Run make

The binary is created in the 'bin' folder.

The location of the password records can be set in the conf file. Copy the cloned conf file from conf folder to 
~/.config/ARanade/
on Linux and edit the db_path.
 
 Note: For libgcrypt is used for encryption.
 