from Crypto.Cipher import AES
import random
import string

plaintext = b'[REDACTED(ha ha!)]'

key_string = ''.join(random.choices(string.ascii_uppercase, k=6))
key_string = key_string + key_string + key_string + key_string
key_bytes = bytes(key_string, 'utf-8')
key = key_bytes

cipher_enc = AES.new(key, AES.MODE_EAX)
nonce = cipher_enc.nonce
ciphertext, tag = cipher_enc.encrypt_and_digest(plaintext)

f=open("ciphertext","wb")
f.write(ciphertext)
f=open("nonce","wb")
f.write(nonce)
f=open("key","wb")
f.write(key)