In this challenge you will decode base64-encoded data.
Despite base64 data appearing "mangled", it is not an encryption scheme.
It is an encoding, much like ASCII.
It is simply a popular way of encoding raw bytes.

The name "base64" comes from the fact that there are 64 characters used in the output.
These can actually vary, but the standard base64 encoding uses an "alphabet" of the uppercase letters `A` through `Z`, the lowercase letters `a` through `z`, the digits `0` through `9`, and the `+` and `/` symbols.
This results in 64 total output symbols, and each symbol can encode `2**6` (2 to the power of 6) possible input symbols, or 6 bits of data.
That means that two encode a single byte (8 bits) of input, you need more than one base64 output character.
In fact, you need _two_: one that encodes the first 6 bytes and one that encodes the remaining 2 (with 4 bytes of that second output character being unused).
To mark these unused bytes, base64 encoded data appends an `=` for every two unused bytes.
For example:

```console
hacker@dojo:~$ echo -n A | base64
QQ==
hacker@dojo:~$ echo -n AA | base64
QUE=
hacker@dojo:~$ echo -n AAA | base64
QUFB
hacker@dojo:~$ echo -n AAAA | base64
QUFBQQ==
hacker@dojo:~$
```

As you can see, 3 bytes (`3*8 == 24` bits) encode precisely into 4 base64 characters (`4*6 == 24` bits).

base64 is a popular encoding because it can represent any data without using "tricky" characters such as newlines, spaces, quotes, semicolons, unprintable special characters, and so on.
You might recall that such characters can cause trouble in certain scenarios, and base64-encoding the data avoids this nicely.
For the purposes of this module, base64 will be used to give you random and encrypted data, all of which is terribly unprintable and much easier to input and output as base64.

Other popular encodings are base2 (typically just `0` and `1`), base10 (typically `0` through `9`), base16 (`0` through `9` and `A` through `F`).
This last one is especially interesting: a single character in base16 encodes 4 bits, making a single byte of binary data representable using two base16 characters.
This is used all over computing: for example, the `%20` that you've seen in URL encoding is base16 for the ASCII space character.
In binary, ASCII's space is `0010 0000`, which translates to `20` in base16.

Anyways, that was a long tangent.
Go run `/challenge/run` and decode the flag!

----
**HINT:**
You can use Python's `base64` module (note: the base64 decoding functions in this module consume and return Python bytes) or the `base64` command line utility to do this!

**FUN FACT:**
The flag data in `pwn.college{FLAG}` is actually base64-encoded ciphertext.
You're well on the way to being able to build something like the dojo!
