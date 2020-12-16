#!/bin/sh
# This is a comment!
openssl genrsa -out privkey_alice.pem 2048
openssl rsa -in privkey_alice.pem -outform PEM -pubout -out pubkey_alice.pem
openssl dgst -sha256 -sign privkey_alice.pem -out sign_alice.sha256 /home/data_user/b.txt
openssl enc -base64 -in sign_alice.sha256 -out sign_alice.sha256.base64
openssl req -new -x509 -days 365 -nodes -out certificate.crt -key privkey_alice.pem -subj "/C=IN/ST=KL/L=KL/O=UFF/OU=THD/CN=example.org/emailAddress=alice@alice.com"
