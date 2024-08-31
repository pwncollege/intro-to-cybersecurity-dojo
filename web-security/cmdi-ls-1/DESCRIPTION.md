The previous levels' path traversals happened because of a disconnect between at least two of the following:

1. A lack of developer awareness of the true range of potential input that an attacker might send to their application (e.g., the concept of an attacker sending characters that have special meaning in paths).
2. The developer's understanding of how paths work in Linux (e.g., that `..` can occur anywhere, not just in the beginning).
3. A gap in the flow of a semantic understanding of developer intent between the server (where the implementation makes it clear that we only expect files under the `/challenge/files` directory to be served) and the filesystem (where `..` wreaks havok).

Now, all this happened just with paths in the mix.
Imagine getting more crazy: interactions between the web server and the whole Linux shell!

Depressingly often, developers rely on the command line shell to help with complex operations.
In these cases, a web server will execute a Linux command and use the command's results in its operation (a frequent usecase of this, for example, is the `Imagemagick` suite of commands that facilitate image processing).
Different languages have different ways to do this (the simplest way in Python is `os.system`, but we will mostly be interacting with the more advanced `subprocess.check_output`), but almost all suffer from the risk of _command injection_.

In path traversal, the attacker sent an unexpected character (`.`) that caused the filesystem to do something unexpected to the developer (look in the parent directory).
The shell, similarly, is chock full of special characters that cause effects unintended by the developer, and the gap between what the developer intended and the reality of what the shell (or, in previous challenges, the file system) does holds all sorts of security issues.

For example, consider the following Python snippet that runs a shell command:

```console
os.system(f"echo Hello {word}")
```

The developer clearly intends the user to send something like `Hackers`, and the result to be something like the command `echo Hello Hackers`.
But the hacker might send _anything_ the code doesn't explicitly block.
Recall what you learned in the [Chaining](/linux-luminarium/chaining) module of the [Linux Luminarium](/linux-luminarium): what if the hacker sends something containing a `;`?

In this level, we will explore this exact concept.
See if you can trick the level and leak the flag!
