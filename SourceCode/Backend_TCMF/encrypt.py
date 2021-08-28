from hashlib import sha256

def encrypt(password):
    h = sha256()
    password_binary = f'{password}'.encode('utf-8')
    h.update(password_binary)
    hash = h.hexdigest()
    return hash

print(encrypt("12345678"))
