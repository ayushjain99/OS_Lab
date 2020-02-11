#!/usr/bin/env python
# Ayush Jain - 2017UCP1168
# Implementation of RC4 algorithm

import codecs
MOD = 256

def KSA(key):
    key_length = len(key)
    S = list(range(MOD))
    j = 0
    for i in range(MOD):
        j = (j + S[i] + key[i % key_length]) % MOD
        S[i], S[j] = S[j], S[i]  # swap values
    return S

def PRGA(S):
    # Psudo Random Generation Algorithm
    i = 0 ; j = 0
    while True:
        i = (i + 1) % MOD
        j = (j + S[i]) % MOD

        S[i], S[j] = S[j], S[i]
        K = S[(S[i] + S[j]) % MOD]
        yield K

def get_keystream(key):
    S = KSA(key)
    return PRGA(S)

def encrypt_logic(key, text):
    key = [ord(c) for c in key]
    keystream = get_keystream(key)
    res = []
    for c in text:
        val = ("%02X" % (c ^ next(keystream)))
        res.append(val)
    return ''.join(res)

def encrypt(key, plaintext):
    plaintext = [ord(c) for c in plaintext]
    return encrypt_logic(key, plaintext)

def decrypt(key, ciphertext):
    ciphertext = codecs.decode(ciphertext, 'hex_codec')
    res = encrypt_logic(key, ciphertext)
    return codecs.decode(res, 'hex_codec').decode('utf-8')


def main():
    fhand = open("input.dat","r") ; i=0
    for line in fhand:
        if(i==0):
            plaintext = line.rstrip()
        else:
            key = line.rstrip()
        i=i+1
    fhand.close()
    ciphertext = encrypt(key, plaintext)
    #####################################################
    print('Plaintext:', plaintext)
    print('Ciphertext:', ciphertext)
    #####################################################
    fhand = open("cipher.dat","w")
    fhand.write(ciphertext) ; fhand.close()
    # ciphertext = 'B743F79213B40249903DD29F49C38348535E0D81E335C6DA86A145B8E0C0BF33479CD58D43235C335C'
    # change ciphertext to string again
    decrypted = decrypt(key, ciphertext)
    print('decrypted:', decrypted)

    if plaintext == decrypted:
        print('\nDecryption Completed Successfully')
    else:
        print('Decryption not complete..Try Again')


def test():
    assert(encrypt('Key', 'Plaintext')) == 'BBF316E8D940AF0AD3'
    assert(decrypt('Key', 'BBF316E8D940AF0AD3')) == 'Plaintext'
    assert(encrypt('Wiki', 'pedia')) == '1021BF0420'
    assert(decrypt('Wiki', '1021BF0420')) == 'pedia'
    assert(encrypt('Secret',
                   'Attack at dawn')) == '45A01F645FC35B383552544B9BF5'
    assert(decrypt('Secret',
                   '45A01F645FC35B383552544B9BF5')) == 'Attack at dawn'

if __name__ == '__main__':
    main()
