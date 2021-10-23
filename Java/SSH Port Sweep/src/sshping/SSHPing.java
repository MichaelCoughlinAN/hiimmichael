package sshping;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.ArrayList;

/**
 *
 * @author Michael Coughlin
 */
public class SSHPing {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        // IPv4 addresses to check on network 
        ArrayList<String> addresses = new ArrayList<String>() {
            {
                add("192.168.1.2");
                add("192.168.1.3");
                add("192.168.1.4");             
            }          
        };

        boolean result = false;
        String address = "";
        int connectionTimeOut = 5;
        
        for (int i = 0; i < addresses.size(); ++i) {
            address = addresses.get(i);
            
            try {
                Socket client = new Socket(); 
                client.connect(new InetSocketAddress(address, 22), connectionTimeOut); 
                // new Socket(address, 22).close();
                result = true;
            } catch (IOException ex) {
                result = false;
            }

            if (result) {
                System.out.println("SSH client is enabled on machine: " + address);
            } else {
                System.out.println("SSH client is disabled on machine: " + address);
            }

        }
        
       
    }
}
