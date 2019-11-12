/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multicasttest;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class MulticastReceiver extends Thread {

    protected static MulticastSocket socket = null;
    protected static byte[] buf = new byte[256];

    public static void main(String... args) throws IOException, ParseException {
        try {

            socket = new MulticastSocket(4446);

            InetAddress group;

            group = InetAddress.getByName("230.0.0.0");

            socket.joinGroup(group);
            while (true) {
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);
                String received = new String(
                        packet.getData(), 0, packet.getLength());
                JSONParser parser = new JSONParser();
                JSONObject o = (JSONObject) parser.parse(received);
                System.out.println("Report Date: " + o.get("report"));
                System.out.println("Dispense Date: " + o.get("dispense"));
                System.out.println("Work Order: " + o.get("workorder"));
                System.out.println("Job Code: " + o.get("jobcode"));
                System.out.println("Fluid Oil: " + o.get("fluid"));
                System.out.println("Amount Dispensed: " + o.get("amount"));

                if ("end".equals(received)) {
                    break;
                }
            }
            socket.leaveGroup(group);
            socket.close();
        } catch (IOException ex) {
            Logger.getLogger(MulticastReceiver.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
