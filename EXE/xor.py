import os
import sys
import string
import random




def gen_key(num_chars=32):
  charset = string.ascii_letters
  return "".join(random.choice(charset) for _ in range(num_chars))

def xor_enc(_str, key):
  return ''.join(chr(ord(c) ^ ord(key[i % len(key)])) for i, c in enumerate(_str))

def s2h(_str):
  return ''.join('%02X' % ord(c) for c in _str)




def grabtext( inside, first, second ):
    try:
        begin = inside.index( first ) + len( first )
        ending = inside.index( second, begin )
        return inside[begin:ending]
    except ValueError:
        return ""

key = 'TmFrUOCSDzrNBEJhRjklFSDfnuzlxnnr'
print key
with open('test.txt', 'r') as infile, open('encryptedtest.txt', 'w') as outfile:
    for line in infile:
	lmfao = grabtext(line, "START", "END")
	print lmfao
	if lmfao:
	    hexed = s2h(xor_enc(lmfao, key))
	    print hexed
	    outfile.write(line.replace("START"+lmfao+"END", hexed))
            
print key
