import java.net.*;  /* import networking package */
import java.io.*;   /* import input/output package */

public class mcreceive {

  public static final int MAX_LEN  = 1024;  /* max receive buffer */
  public static final int MIN_PORT = 1024;  /* min network port */
  public static final int MAX_PORT = 65535; /* max network port */

  public static void main(String argv[]) {

    InetAddress mcAddress=null; /* multicast address */
    int mcPort=0;               /* multicast port */
    int ttl=1;                  /* time to live */
    boolean done=false;         /* variable for send loop */

     /* validate number of arguments */
    if (argv.length != 2) {
      System.out.println("Usage: mcreceive " + 
                         "<Multicast IP> <Multicast Port>");
      System.exit(1);
    }

    /* validate the multicast address argument */
    try {
      mcAddress = InetAddress.getByName(argv[0]);
    } catch (UnknownHostException e) {
      System.err.println(argv[0] + " is not a valid IP address");
      System.exit(1);
    }

    /* validate address argument is a multicast IP */
    if (! mcAddress.isMulticastAddress()) {
      System.err.println(mcAddress.getHostAddress() +
                         " is not a multicast IP address.");
      System.exit(1);
    }

    /* parse and validate port argument */
    try {
      mcPort = Integer.parseInt(argv[1]);
    } catch (NumberFormatException nfe) {
      System.out.println("Invalid port number " + argv[1]);
      System.exit(1);
    }

    if ((mcPort < MIN_PORT) || (mcPort > MAX_PORT)) {
      System.out.println("Invalid port number " + mcPort);
      System.out.println("Port should be in range " + MIN_PORT
                         + " to " + MAX_PORT);
      System.exit(1);
    }

    try {

      /* instantiate a MulticastSocket */
      MulticastSocket sock = new MulticastSocket(mcPort);

      /* set the address reuse option */
      sock.setReuseAddress(true); // Java 1.4 and higher
  Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
    while (interfaces.hasMoreElements()) {
        NetworkInterface iface = interfaces.nextElement();
        if (iface.isLoopback() || !iface.isUp())
            continue;

        Enumeration<InetAddress> addresses = iface.getInetAddresses();
        while(addresses.hasMoreElements()) {
            InetAddress addr = addresses.nextElement();
            multicastSocket.setInterface(addr);
            multicastSocket.joinGroup(InetAddress.getByName(groupName));
        }
    }
      /* join the multicast group */
      sock.joinGroup(mcAddress);

      while (!done) {  /* loop forever */
         
        /* create a new DatagramPacket with an empty buffer */
        byte[] buf = new byte[MAX_LEN];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);

        /* wait to receive packet into the DatagramPacket instance */
        sock.receive(packet);

        /* output the data from the packet received */
        System.out.println("Received " + packet.getLength() +
            " bytes from " + packet.getAddress() + ": " 
            + new String(packet.getData(),0,packet.getLength()));
      }

      sock.leaveGroup(mcAddress);
      sock.close();

    } catch (IOException e) {
      System.err.println(e.toString());
      System.exit(1);
    }
  }
}
