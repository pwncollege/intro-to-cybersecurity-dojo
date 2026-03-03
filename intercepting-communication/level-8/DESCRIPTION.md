Manually send an Ethernet packet.
The packet should have `Ether type=0xFFFF`.
The packet should be sent to the remote host at `10.0.0.2`.

---

From the lectures, you learned how data is structured and encapsulated as it moves through the network stack. Equally important is understanding how data leaves one host and arrives at another: this is called **end-to-end communication**. 

At the Data Link Layer (Layer 2), frames enter and exit a host through a network interface, like eth0. 

At the Transport Layer (Layer 4), TCP and UDP move data between processes using OS-managed *sockets*. A *network socket* is a software abstraction that combines an IP address and a port number to form a unique communication endpoint between hosts. In socket programming, you use *system calls* to create and manage sockets. 

The operating system owns and controls these sockets — maintaining connection state, handling retransmissions (for TCP), and automatically constructing the underlying IP and Ethernet headers on behalf of the host.

You can also create a Layer 2 socket, called a *raw socket*, which allows you to bypass higher-level protocol handling and directly send and receive Ethernet frames.

*Tool Note:* The `socket` module comes standard with Python and supports manual, precise packet building. `Scapy` might be a more convenient solution, however, as it is an external library designed for these packet crafting, sniffing, spoofing, and other security testing tasks. 
