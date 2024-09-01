Okay, so injecting some HTML was pretty cool!
You can imagine how this can be used to confuse victims, but it gets worse...

In the 1990s, the wise designers of the web invented JavaScript to make websites more interactive.
JavaScript lives alongside your HTML, and makes things interesting.
For example, this turns your browser into a clock:

```html
<html>
  <body>
    <script>
      document.body.innerHTML = Date();
    </script>
  </body>
</html>
```

Basically, the HTML `<script>` tag tells the browser that what is inside that tag is JavaScript, and the browser executes it.
I'm sure you can see where this is going...

In the previous level, you injected HTML.
In this one, you must use the exact same Stored XSS vulnerability to execute some JavaScript in the victim's browser.
Specifically, we want you to execute the JavaScript `alert("PWNED")` to pop up an alert that informs the victim that they've been pwned.
The _how_ of this level is the exact same as the previous one; only the _what_ changes, and suddenly, you're cooking with gas!
