Your host at 10.0.0.1 is receiving traffic on port `31337`; block that traffic.

___

In this challenge, you'll control the flow of data on a port. The title gives you a hint as to how — use a firewall!

A firewall secures a host by inspecting network traffic and enforcing rules to control it. A common tool for configuring these rules is [iptables](https://linux.die.net/man/8/iptables).

Note: Rule order and priority matter. You can list the current configuration to understand how packets are processed and debug your setup.
