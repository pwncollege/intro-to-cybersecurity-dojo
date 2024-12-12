Of course, web applications can have security vulnerabilities that have nothing to do with the shell.
A common type of vulnerability is an _Authentication Bypass_, where an attacker can bypass the typical authentication logic of an application and log in without knowing the necessary user credentials.

This level challenges you to explore one such scenario.
This specific scenario arises because, again, of a gap between what the developer expects (that the URL parameters set by the application will only be set by the application itself) and the reality (that attackers can craft HTTP requests to their hearts content).

The goal here is not only to let you experience how such vulnerabilites might arise, but to familiarize you with _databases_: places where web applications stored structured data.
As you'll see in this level, data is stored into and read from these databases using a language called the _Structured Query Language_, or SQL (often pronounced like "sequel") for short.
SQL will become incredibly relevant later, but for now, it is an incidental part of the challenge.

Anyways, go and bypass this authentication to log in as the `admin` user and get the flag!
