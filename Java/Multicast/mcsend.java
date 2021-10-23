import java.net.*;  /* import networking package */
import java.io.*;   /* import input/output package */

public class mcsend {

  public static final int MIN_PORT = 1024;  /* min network port */
  public static final int MAX_PORT = 65535; /* max network port */

  public static void main(String argv[]) {
 
    InetAddress mcAddress=null;  /* multicast address */
    int mcPort=0;                /* multicast port */
    int ttl=1;                   /* time to live */
    BufferedReader stdin;        /* input from keyboard */
    String sendString;           /* string to be sent */
    byte[] sendBytes;            /* bytes to be sent */

    /* validate number of arguments */
    if (argv.length != 2) {
      System.out.println("Usage: mcsend " +
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
      System.err.println("Invalid port number (" + argv[1] + ")");
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
      MulticastSocket sock = new MulticastSocket();

      /* set the time to live */
      sock.setTimeToLive(ttl); // Java 1.0/1.1 use setTTL()

      /* prepare to read from the keyboard input */
      stdin=new BufferedReader(new InputStreamReader(System.in));

      System.out.println("Begin typing (return to send," + 
                         " ctrl-C to quit):");

      while ((sendString=stdin.readLine()) != null) {

        /* convert keyboard input to bytes */
        sendBytes=sendString.getBytes();

        /* populate the DatagramPacket */
        DatagramPacket packet = new DatagramPacket(sendBytes,                                 sendBytes.length, mcAddress, mcPort);

        /* send the packet */
        sock.send(packet);
      }
      sock.close();

    } catch (IOException e) {
      System.err.println(e.toString());
      System.exit(1);
    }
  }
}
