Okay, now you know how to XOR ASCII characters.
This is a critical step as we build up to our first cryptosystem, but now, we need to XOR entire ASCII strings!
Let's try this.

Python’s `^` operator lets you XOR integers, but if you want to XOR entire byte strings or ASCII strings, you can use the `strxor` function from the PyCryptodome library.
You can import it in Python using [`from Crypto.Util.strxor import strxor`](https://pycryptodome.readthedocs.io/en/v3.23.0/src/util/util.html#crypto-util-strxor-module).

XORing two strings is done byte by byte, just like XORing two bytes is done bit by bit.
So, to draw on an earlier example:

```console
hacker@dojo:~$ python
>>> from Crypto.Util.strxor import strxor
>>> strxor(b"AAA", b"16/")
b'pwn'
```

You can verify this yourself with the ASCII table: A ^ 1 is p, A ^ 6 is w, and A ^ / is n.
We just decrypted the _ciphertext_ `AAA` with the _key_ `16/` to retrieve the _plaintext_ `pwn`.

In this challenge, you'll do this several times in a row: like the previous challenge, but with strings!
Good luck!

----
**CAVEAT:**
What are these `b`s prepended to the quotes?
Python's default string representation (e.g., "AAA") is [_Unicode_](https://en.wikipedia.org/wiki/Unicode), an international encoding standard designed to represent all characters known to humanity: from the good old ABCs (_see the [Latin alphabet](https://en.wikipedia.org/wiki/Latin_alphabet)_) to the Arabic and Cyrillic scripts (to name a few).
First published in the 1990s, Unicode now supports a massive set of symbols from "A" to "💩"; when this text was written, Unicode encompassed 154,998 characters!

Unfortunately, a single byte of 8 bits can only hold `2**8 == 256` different values, which is enough for ASCII to encode basic English text (a-z, 0-9, punctuation, etc.), but not enough for Unicode.
Unicode is _encoded_ using different encodings, such as the [UTF-8](https://en.wikipedia.org/wiki/UTF-8) we mentioned earlier.
UTF-8 is designed to be backwards-compatible with ASCII: "A" is just 0x41; something like "💩" is _four_ bytes: `f0 9f 92 a9`!

Basically, `ASCII` is a character encoding standard for `The Latin Alphabet` and `UTF-8` is a character encoding standard for `Unicode`. In the same way that the Latin alphabet is a subset of Unicode, ASCII is a subset of UTF-8.
Wild.

Anyway, Python strings (including what you get from `input()`) represent text as Unicode, while some helpful functions, such as `strxor`, expect and return _bytes_.
You can create a bytes object directly as I did above, by prepending your quotes with `b` (for **b**ytes) and using ASCII or hex encoding (e.g., `b"AAA"` and `b"A\x41\x41"` are equivalent). You can also _encode_ a Unicode string into bytes using UTF-8, as in `"AAA".encode() == b"AAA"` or `"💩".encode() == b"\xf0\x9f\x92\xa9"`, and _decode_ the resulting bytes back into Unicode strings: `b"AAA".decode() == "AAA"` or `b"\xf0\x9f\x92\xa9".decode() == "💩"`.

This is _further_ complicated by the fact that UTF-8 can't turn any arbitrary bytes into Unicode.
For example, `b'\xb0'.decode()` raises an exception because by these bytes are not valid UTF-8 (note that .decode() is equivalent to .decode('utf-8')).
You can avoid this by specifying a different encoding, such as [ISO-8859-1](https://en.wikipedia.org/wiki/ISO/IEC_8859-1), also known as Latin-1. In Python, this encoding may be referred to as latin, latin1, or latin-1 -- these all mean the same thing. This older encoding maps _every_ byte to a character, so arbitrary sequences can be decoded without errors: `b'\xb0'.decode('latin')`.

Even though Latin-1 pre-dates Unicode, decoding with it produces a standard Python Unicode string.
However, keep in mind that Latin-1 encoding is _different_ from UTF-8: `b"\xb0".encode("latin").decode() == b'\xc2\xb0'`.
You must, instead, be consistent and decode and encode with the same encoding: `b"\xb0".encode("latin").decode("latin1") == b"\xb0"`.

Anyways, all this sounds terrifying, but it's mostly a warning for the future.
For _this_ level, we VERY carefully chose the characters so that you don't run into these issues.

**CAUTION:**
Python's strings-vs-bytes situation is terrible and _will_ byte (haha!) you eventually.
There's no way to avoid pitfalls --- they still get us after years and years of using Python, so you will just have to learn to pick yourself up, brush yourself off, fix your code, and carry on.
With enough experience under your belt, you will improve from losing _entire freaking days_ to bugs caused by string/bytes mixups to merely _entire freaking hours_.
