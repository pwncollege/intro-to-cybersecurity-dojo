Of course, these sorts of security gaps abound!
For example, in this level, the specification of the logged in user is actually secure.
Instead of get parameters or raw cookies, this level uses an encrypted session cookie that you will not be able to mess with.
Thus, your task is to get the application to actually authenticate you as admin!

Luckily, as the name of the level suggests, this application is vulnerable to a _SQL injection_.
A SQL injection, conceptually, is to SQL what a Command Injection is to the shell.
In Command Injections, the application assembled a command string, and a gap between the developer's intent and the command shell's actual functionality enabled attackers to carry out actions unintended by the attacker.
A SQL injection is the same: the developer built the application to make SQL queries for certain goals, but because of the way these queries are assembled by the application logic, the resulting actions of the SQL query, when executed by the database, can be disastrous from a security perspective.

When you find the SQL query into which you can inject your input (hint: it is the only SQL query to substantially differ between this level and the previous level), look at what the query looks like right now, and what unintended conditions you might inject.
The quintessential SQL injection adds a condition so that an application can succeed without knowing the password.
How can you accomplish this?
