Computers might think in binary, but on your terminal, you see letters!
How does this happen?
Through _encodings_.

An encoding is a mapping from some sequence of binary digits (bits) to a letter.
The mapping itself is just something made up by some people somewhere, and there have been many such mappings throughout history.
For example, the mapping that powers the modern internet, including the all-important emojis that you send to your friends and earn by completing pwn.college dojos, is [UTF-8](https://en.wikipedia.org/wiki/UTF-8).
UTF-8 describes how one or more bytes (each byte is 8 bits) corresponds to a character.
Luckily for our purposes as an English-language educational resource, the encoding of the Latin alphabet in UTF-8 is quite simple, and harkens back to another encoding standard called [_ASCII_](https://en.wikipedia.org/wiki/ASCII).

ASCII is, by computing standards, an ancient encoding, dating back to 1963.
Modern ASCII is pretty simple: every character is one byte (8 bits), uppercase letters are `0x40+letter_index` (e.g., A is `0x41`, F is `0x46`, and Z is `0x5a`), lowercase letters are `0x60+letter_index` (a is `0x61`, f is `0x66`, and z is `0x7a`), and numbers (yes, the numeric characters you're seeing are _not_ bytes of those values, they are ASCII-encoded number characters) are `0x30+number`, so 0 is `0x30` and 7 is `0x37`.
Special characters are sprinkled around the mapping as well: forward slash (`/` is `0x2f`), space is 0x20, and newline is 0x0a.
You can see the whole ASCII table with `man ascii`!

One cool thing is that, since ASCII puts byte values to characters, we can do operations like XOR!
This has obvious implications for cryptography.

In this level, we'll explore these implications byte by byte.
The challenge will give you one letter a time, along with a key to "decrypt" (XOR) the letter with.
You give us the result of the XOR.
For example:

```console
hacker@dojo:~$ /challenge/run
Challenge number 0...
- Encrypted Character: A
- XOR Key: 0x01
- Decrypted Character?
```

How would you approach this?
You can `man ascii` and find the entry for A:

```none
Oct   Dec   Hex   Char
──────────────────────
101   65    41    A
```

So A is `0x41` in hex.
You would XOR that with `0x01`
The result here would be: `0x41 ^ 0x01 == 0x40`, and, according to `man ascii`:

```none
Oct   Dec   Hex   Char
──────────────────────
100   64    40    @
```

It's the @ character!

```console
hacker@dojo:~$ /challenge/run
Challenge number 0...
- Encrypted Character: A
- XOR Key: 0x01
- Decrypted Character? @
Correct! Moving on.
```

Now it's your turn!
Can you XOR things up and get the flag?
