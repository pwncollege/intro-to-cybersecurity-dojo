#!/opt/pwn.college/python

import subprocess
import random
import struct
import os

raw_flag_lines = subprocess.check_output("/usr/bin/figlet < /flag", shell=True).split(b"\n")
max_line_length = max(len(line) for line in raw_flag_lines)
flag_lines = [ line.ljust(max_line_length) for line in raw_flag_lines ]

flag_pixels = [ ]
for y,line in enumerate(flag_lines):
	for x,c in enumerate(line):
		flag_pixels += [ (x, y, c) ]
random.shuffle(flag_pixels)

operations = [ ]
for p in flag_pixels:
	operations += [ struct.pack("<HBBBBBBBB", 2, p[0], p[1], 1, 1, 0x8c, 0x1d, 0x40, p[2]) ]
	operations += [ struct.pack("<HB", 6, 1) ]
	operations += [ struct.pack("<HI", 7, 733_331) ]

img = b"cIMG" + struct.pack("<HBBI", 4, max_line_length, len(flag_lines), len(operations)) + b"".join(operations)
with open("/challenge/the_flag.cimg", "wb") as o:
	o.write(img)
