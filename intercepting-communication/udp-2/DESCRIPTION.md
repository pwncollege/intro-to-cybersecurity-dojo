Though we didn't explore this for TCP, in addition to selecting the destination port, both TCP and UDP can set their _source_ port.
We'll practice that here --- you can set the source port with `s.bind` on the socket, exactly how a server does it to set their listening port.
