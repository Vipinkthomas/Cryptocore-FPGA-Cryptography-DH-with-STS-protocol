openssl dgst -sha256 -sign /home/bob/bob.key -out /home/bob/signatureBob.sha256 /home/bob/cAliceBob.txt
openssl enc -base64 -in /home/bob/signatureBob.sha256 -out /home/bob/signatureBob.base64
openssl enc -salt -aes-256-cbc -in /home/bob/signatureBob.base64 -kfile secret.txt -out signatureBob.enc
