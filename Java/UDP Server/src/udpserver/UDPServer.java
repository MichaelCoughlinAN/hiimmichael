import java.io.*;
import java.net.*;
import java.net.InetAddress;
import java.net.UnknownHostException;

class UDPServer {

    public static void main(String args[]) throws Exception {

        // The current IP address of server
        InetAddress ip = null;
        String hostname = null;

        DatagramSocket serverSocket = new DatagramSocket(9876);
        byte[] receiveData = new byte[1024];
        byte[] sendData = new byte[1024];

        try {
            ip = InetAddress.getLocalHost();
            hostname = ip.getHostName();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }

        while (true) {
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            serverSocket.receive(receivePacket);
            String message = new String(receivePacket.getData());

            System.out.println("Received from client: " + message);
            message = "You found me! Here is my IP address: " + ip.toString();

            InetAddress IPAddress = receivePacket.getAddress();
            int port = receivePacket.getPort();

            sendData = message.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
            serverSocket.send(sendPacket);
        }
    }
}
