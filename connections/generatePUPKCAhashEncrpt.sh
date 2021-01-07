#!/bin/sh
# This is a comment!
echo Hello World         # This is a comment, too!

openssl genrsa -aes256 -out ca.key 2048
openssl req -new -x509 -days 7300 -key ca.key -sha256 -extensions v3_ca -out ca.crt
openssl genrsa -out bob.key 2048
openssl req -sha256 -new -key bob.key -out bob.csr
openssl x509 -sha256 -req -in bob.csr -CA  /home/vipin/rootCA/ca.crt -CAkey  /home/vipin/rootCA/ca.key -CAcreateserial -out bob.crt -days 7300

openssl dgst -sha256 -sign bob.key -out sign.sha256 cAliceBob.txt
openssl enc -base64 -in sign.sha256 -out sign.sha256.base64

# cAliceBob.txt: file contain cAlice,cBob

openssl enc -salt -aes-256-cbc -in sign.sha256.base64 -kfile secret.txt -out signedValue.enc

# send signedValue.enc across the channel and verify it on Alice
