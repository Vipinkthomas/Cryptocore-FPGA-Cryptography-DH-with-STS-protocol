# SToESD_II_2020-21 - Team 11

Ausgewählte Themen der Embedded Software Entwicklung II
Selected Topics of Embedded Software Development II



## Project Description
In this project, a Linux device driver is extended by a function which interfaces the CryptoCore in order to perform a sub-step of the Diffie-Hellman protocol in terms
of a modular exponentiation. By calling this function two times with suitable parameters a
common secret can be agreed over a public channel.
By using a User Space Application the rudimental Diffie-Hellman protocoll is extended
into an authenticated protocol by utilizing a cryptographic library (OpenSSL).

For the validation of the calculation inside of the CryptoCore the open-source mathematics
software SageMath is used.


# Prerequisites:

- Connected to THD vpn server
- Linux terminal or Putty already installed

# How To Run the Full Station-To-Station

1. Open SSH terminal and connect to 192.168.101.215 (user: alice , password: alice )
2. Open another SSH terminal and connect to 192.168.101.215 (user: bob , password: bob )
3. Delete all files created from a previous run (For alice: in `/home/alice`, For bob: in `/home/bob`)
4. Terminal ( bob ): change working directory to `/home/bob/stoesd_ii_2020-21/Main` and run the command `sudo python3 main.py`
5. Terminal ( alice ) : change working directory to `/home/alice/stoesd_ii_2020-21/Main` and run the command `sudo python3 main.py`

## How To Verify with sageMath 

To verify the results computed by the cryptocore
- For Alice, Navigate to `/home/alice/stoesd_ii_2020-21/Main`,
- For Bob,  Navigate to `/home/bob/stoesd_ii_2020-21/Main`
- run `/home/root/Downloads/sage-6.9-armv7l-Linux/sage`
- after sage starts, attach the sage file in the working directory by typing `attach("Mod_Exp_Verification.sage")`

## How To use the chat system ( Encryption / Decryption )
1. Terminal ( bob ): change working directory to `/home/bob/stoesd_ii_2020-21/Main` and run the command `sudo python3 chat.py`
2. Terminal ( alice ) : change working directory to `/home/alice/stoesd_ii_2020-21/Main` and run the command `sudo python3 chat.py`

## Further Information
- Precision used for numbers = 4096 bit
- the generator and the modulus are stored in text files in `/home/data_user` as well as rootCA ( password for this user: data_user )
- OpenSSL commands can be found in `.sh` files in `Main` directory for each alice and bob
- application files can be found in `stoesd_ii_2020-21/applications` for each alice and bob
