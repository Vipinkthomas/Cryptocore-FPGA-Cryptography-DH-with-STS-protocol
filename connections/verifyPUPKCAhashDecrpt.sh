#!/bin/sh
# This is a comment!
echo Hello World         # This is a comment, too!

openssl enc -d -salt -aes-256-cbc -in signedValueAlice.enc -kfile secret.txt -out sign.sha256.base64
openssl enc -base64 -d -in sign.sha256.base64 -out sign.sha256
openssl dgst -sha256 -verify pubkey.pem -signature sign.sha256 cBobAlice.txt
