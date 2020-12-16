#!/bin/sh
# This is a comment!
echo Hello World         # This is a comment, too!
openssl genrsa -out privkey.pem 2048
openssl rsa -in privkey.pem -outform PEM -pubout -out pubkey.pem
