From your host at 10.0.0.1, connect to the remote host at 10.0.0.2 on port 31337, and then shut down the connection.

As before, you'll want to use the `nc` command.

Sometimes the other side of a connection wants to wait for you to finish sending all of your data before it finishes sending data back to you.
Imagine a protocol where the client might need to send lots of data, over a long duration, before the server can respond with some final result.
In this case, it might not make sense to preestablish how much data will be sent in total as part of the protocol, because the client might not know at the beginning how much data it will need to send.
How can we handle this situation?

One option would be to have the client send a single packet at the end that just says "END".
But network packets can be complicated, with no guarantees from the network that they won't be split apart or merged together.
Or what if you want to be able to send "END" as part of the data?

Fortunately, TCP provides a solution to this problem, with the TCP "FIN" flag.
When a client sends a packet with the FIN flag set, it is saying "I'm done sending data, but I'm still listening for data from you."

Netcat is ultimately a simple tool, that translates data from standard input to network packets and vice versa to standard output.
So how do you send a packet with the FIN flag set?
You do the equivalent file operation: you close standard input!
In an interactive terminal session, you can do this by pressing `Ctrl-D`.
