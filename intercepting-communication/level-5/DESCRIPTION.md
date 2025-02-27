Monitor traffic from a remote host.
Your host is already receiving traffic on port `31337`.

----
**HINT:**
You will likely want to use the Wireshark (`tshark` if you connected through `ssh` or prefer using CUI instead of GUI) tool for this.
This is installed on the dojo, and you can launch it from the terminal of the `10.0.0.1` client (after your `/challenge/run`)!
Make sure to launch it from there: launched from elsewhere (such as a different terminal on the workspace), Wireshark (`tshark`) will not be running on the correct host!
Wireshark might take a long time to start up.
If you're waiting for over a minute, something is wrong...
`tshark` starts immediately, `tshark -h` to see how to use it.
