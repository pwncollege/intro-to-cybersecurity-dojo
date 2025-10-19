This level closes the loophole that allowed you to steal cookies from JavaScript.
Cookies have an optional attribute called (`HttpOnly`)[(https://developer.mozilla.org/en-US/docs/Web/HTTP/Cookies#security)], and when this is set, the cookie is not able to be accessed by JavaScript (e.g. `document.cookie`)
This is a security measure, aimed to prevent exactly the type of cookie pilfering that you have been doing.
Luckily, Flask's default `session` cookie is set to be `HttpOnly`, so you cannot steal it from JavaScript.

So, now how would you get the flag with your CSRF-to-XSS shenanigans?
Luckily, you don't _need_ the cookie!
Once you have JavaScript execution within the page, you can freely `fetch()` other pages without worrying about the Same Origin Policy, since you now live in the same Origin.
Use this, read the page with the flag, and win!
