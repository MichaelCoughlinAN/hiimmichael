/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multicastpublisher;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.simple.JSONObject;
//import org.json.JSONException;
//import jdk.nashorn.internal.parser.JSONParser;
//import org.json.JSONObject;
//import org.json.simple.parser.JSONParser;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class MulticastPublisher {

    private static DatagramSocket socket;
    private InetAddress group;
    private byte[] buf;

    public MulticastPublisher() throws IOException {
        socket = new DatagramSocket();
        group = InetAddress.getByName("230.0.0.0");
        //buf = multicastMessage.getBytes();

    }

    public void send() throws IOException, ParseException {

        JSONParser parser = new JSONParser();
        Reader targetReader = new InputStreamReader(getClass().getResourceAsStream("pulse_receipt_12_13_2017_07_59.json"));
        JSONObject o = (JSONObject) parser.parse(targetReader);

        System.out.println("Per Dispense Report [TEST]");
        System.out.println("Report Date: " + o.get("report"));
        System.out.println("Dispense Date: " + o.get("dispense"));
        System.out.println("Work Order: " + o.get("workorder"));
        System.out.println("Job Code: " + o.get("jobcode"));
        System.out.println("Fluid Oil: " + o.get("fluid"));
        System.out.println("Amount Dispensed: " + o.get("amount"));

        buf = o.toString().getBytes();
        DatagramPacket packet
                = new DatagramPacket(buf, buf.length, group, 4446);
        socket.send(packet);

    }

    public static void main(String... args) throws IOException {
        MulticastPublisher multicastPublisher = new MulticastPublisher();
        try {
            multicastPublisher.send();
        } catch (ParseException ex) {
            Logger.getLogger(MulticastPublisher.class.getName()).log(Level.SEVERE, null, ex);
        }
        socket.close();
    }

}
