Configure your network interface.
The remote host at `10.0.0.2` is trying to communicate with the remote host at `10.0.0.3` on port `31337`.

---
Recall the routing setup from *Intercepting Communication: Ethernet* which allowed Host A and Host B to communicate using their interfaces at the **Data Link Layer (Layer 2)**. In this challenge, communication uses IP addresses, so you will also need to consider the **Internet Protocol (Layer 3)**.  

Network interfaces come in many types (loopback, ethernet, wireless, virtual, etc.) and are are essential for connecting systems and delivering data. At Layer 2, the interface receives frames from the network, while at Layer 3, IP addresses assigned to the interface ensure it only accepts packets intended for that address. Ensure the interface is set up correctly and active so the hosts can communicate as described.

