#!/opt/pwn.college/python

import struct
import os

FONT_DIR = f"{os.path.dirname(__file__)}/.fonts"

sprite_nums = { }
operations = [ ]
for c in open("/flag").read().strip():
	if c not in sprite_nums:
		sprite_nums[c] = len(operations)
		sprite = [ line for line in open(f"{FONT_DIR}/figlet-{c}", "rb").read().split(b"\n") if line ]
		operations += [ struct.pack("<HBBB", 3, sprite_nums[c], len(sprite[0]), len(sprite)) + b"".join(sprite) ]
	operations += [ struct.pack("<HBBBBBB", 4, sprite_nums[c], 0xff, 0xff, 0xff, 0, 0) ]

img = b"cIMG" + struct.pack("<HBBI", 3, 16, 16, len(operations)) + b"".join(operations)
with open("/challenge/the_flag.cimg", "wb") as o:
	o.write(img)
