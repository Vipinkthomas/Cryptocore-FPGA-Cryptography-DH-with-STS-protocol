# SToESD_II_2020-21

Ausgewählte Themen der Embedded Software Entwicklung II
Selected Topics of Embedded Software Development II

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

