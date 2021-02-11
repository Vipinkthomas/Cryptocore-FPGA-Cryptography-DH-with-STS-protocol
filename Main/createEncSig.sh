openssl dgst -sha256 -sign /home/alice/alice.key -out /home/alice/signatureAlice.sha256 /home/alice/cAliceBob.txt
openssl enc -base64 -in /home/alice/signatureAlice.sha256 -out /home/alice/signatureAlice.base64
openssl enc -salt -aes-256-cbc -in /home/alice/signatureAlice.base64 -kfile /home/alice/secret.txt -out /home/alice/signatureAlice.enc
