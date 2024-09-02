Actual XSS exploits try to achieve something more than `alert("PWNED")`.
A very common goal is to use the ability to execute JavaScript inside a victim's browser to initiate new HTTP requests masquerading as the victim.
This can be done in a number of ways, including using JavaScript's `fetch()` function.

This challenge implements a more complex application, and you will need to retrieve the flag out of the `admin` user's unpublished draft post.
After XSS-injecting the `admin`, you must use the injection to make an HTTP request (as the `admin` user) to enable you to read the flag.
Good luck!
