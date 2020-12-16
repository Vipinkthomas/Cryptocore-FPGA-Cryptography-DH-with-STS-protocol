#!/bin/sh
# This is a comment!
echo Hello World         # This is a comment, too!
openssl genrsa -out privkey.pem 2048
openssl rsa -in privkey.pem -outform PEM -pubout -out pubkey.pem
openssl dgst -sha256 -sign privkey.pem -out sign.sha256 test.txt
openssl enc -base64 -in sign.sha256 -out sign.sha256.base64
openssl req -new -x509 -days 365 -nodes -out Certificate.crt -key privkey.pem -subj "/C=IN/ST=KL/L=KL/O=UFF/OU=THD/CN=example.org/emailAddress=a@a.com"
