Like with SQL injection and command injection, sometimes your XSS occurs in the middle of some non-optimal context.
In SQL, you have dealt with injecting into the middle of quotes.
In XSS, you often inject into, for example, a textarea, as in this challenge.
Normally, text in a textarea is just, well, text that'll show up in a textbox on the page.
Can you bust of this context and `alert("PWNED")`?
