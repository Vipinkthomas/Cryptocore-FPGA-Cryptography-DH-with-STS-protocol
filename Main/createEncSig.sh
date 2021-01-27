openssl dgst -sha256 -sign /home/bob/bob.key -out /home/alice/signatureAlice.sha256 /home/alice/cALiceBob.txt
openssl enc -base64 -in /home/alice/signatureAlice.sha256 -out /home/alice/signatureAlice.base64
openssl enc -salt -aes-256-cbc -in /home/alice/signatureAlice.base64 -kfile secret.txt -out signatureAlice.enc
