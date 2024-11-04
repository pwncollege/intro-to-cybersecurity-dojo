The first few challenges in this dojo will walk you through the creation of your first basic cIMG image.
Of course, the point of this is not to create images, but rather to experience the process of understanding a program, and by extension understanding logic and data formats used by the program, just from reversing its binary.

The `/challenge/cimg` binary in this level is (the start of) an image rendering program, specifically focusing on the cIMG format.
Software identifies the formats of files (e.g., whether the file is a GIF, a JPEG, an MP3, or so on) in a few ways:

1. The file extension.
   This is the part of the file after the `.`: a `ZardusSmiling.jpg` is probably a JPEG of Zardus smiling, whereas `KanakLaughing.mp3` is probably an MP3 of Kanak laughing.
2. The _magic number_.
   Files can get renamed, or the filenames associated with files can be lost (e.g., in a partial filesystem failure) or simply missing (e.g., in a data stream).
   Thus, most file formats include a _magic number_ in the format that a parser can check to identify it.

You've already interacted with plenty of files containing magic numbers.
For example, the ELF binary files you've worked with all start with the bytes `\x7fELF`.
Of course, to you, this looks like a semantic-bearing string of characters, but a computer reads it as a number, hence the term.

In this challenge, you must craft a file with a `cimg` extension that contains the correct magic number.
You can learn this magic number by reversing the `/challenge/cimg` binary.
If you properly get past the magic number check, the challenge will give you the flag!
