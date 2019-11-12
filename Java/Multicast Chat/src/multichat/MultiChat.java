/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multichat;

import java.net.*; 
import java.io.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 
import java.util.Calendar; 
/* 
 * Multicast based chat system with a very simple GUI using SWING 
 * The main thread does the sending, while a secondary thread (the reader) 
 * does the receiving of messages 
 */

public class MultiChat extends JPanel implements ActionListener
 {

    JTextArea textarea = null; 
    JTextField textfield = null; 
    JScrollPane scrollpane = null; 
    private String id; 
    private MulticastSocket socket = null; 
    private SocketAddress dest = null;

    /** 
     * Send the text to the multicast group. 
     * Add the name of the user in front of the message. 
     */ 
    private void send(String msg) throws IOException
   { 
        String buf = id + ">> " + msg; 
        byte[] b = buf.getBytes(); 
        DatagramPacket packet = new DatagramPacket(b, 0, b.length, dest); 
        socket.send(packet); 
    }

    /** 
     * Reader thread. 
     */ 
    class Reader extends Thread { 
        public void run() { 
            byte[] buf = new byte[512]; 
            DatagramPacket p = null; 
            // Just loop forever, as the main thread will take care of the 
            // exit conditions 
            while (true) { 
                try { 
                    p = new DatagramPacket(buf, buf.length); 
                    socket.receive(p); 
                } catch (IOException e) { 
                    e.printStackTrace(); 
                } 
                // We got a packet, let's extract the message and display it 
                String line = new String(p.getData(), 0, p.getLength()); 
                textarea.append(line); 
                textarea.append("\n"); 
            } 
        } 
    }

    /** 
     * Main constructor. 
     * Takes a String containing the name (or id) of the user. 
     */ 
    MultiChat(String name) {

        super(true); 
        id = name;

        // This is the multicast group we'll be using. 
        dest = new InetSocketAddress("228.5.6.7", 4321);

        try { 
            // The socket is created and bound to the proper port. 
            socket = new MulticastSocket(4321); 
            // Set the loopback mode to false if you don't want to see your 
            // own messages 
            //socket.setLoopbackMode(false);

            // get the default Network Interface 
            NetworkInterface netif = NetworkInterface.getByInetAddress(InetAddress.getLocalHost()); 
            // Join the multicast group 
            socket.joinGroup(dest, netif); 
        } catch (Exception e) { 
            e.printStackTrace(); 
            System.exit(1); 
        }

        // From here onwards, the GUI is created

        // Force SwingSet to come up in the Cross Platform L&F 
        try
         { 
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName()); 
            // If you want the System L&F instead, comment out the above line and 
            // uncomment the following: 
            // UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName()); 
        } catch (Exception exc) { 
            System.err.println("Error loading L&F: " + exc); 
        }

        setBorder(BorderFactory.createEtchedBorder()); 
        setLayout(new BorderLayout()); 
        setFocusCycleRoot(true); 
        setRequestFocusEnabled(true);

        // Create the area in which the messages will be seen after a RETURN is hit. 
        // Using the JTextArea class to construct the GUI for this purpose. 
        textarea = new JTextArea(); 
        //textarea.setBackground(Color.cyan); 
        textarea.setLineWrap(true); 
        textarea.setWrapStyleWord(true); 
        textarea.setEditable(false); 
        scrollpane = new JScrollPane(textarea); 
        scrollpane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);

        // Create the area in which the user can key in the text message to be displayed. 
        // Using the JTextField class to construct the GUI for this purpose. 
        textfield = new JTextField(); 
        //textfield.setBackground(Color.yellow); 
        textfield.setDragEnabled(true); 
        textfield.requestFocus(true);

        add("Center", scrollpane); 
        add("South", textfield);

        textfield.addActionListener(this); 
        Reader r = new Reader(); 
        r.start(); 
    }

    // When the user hits <RETURN> this method is called 
    public void actionPerformed(ActionEvent evt) { 
        String text = textfield.getText(); 
        try {

            // So you want to quit? 
            if ("quit".equalsIgnoreCase(text)) { 
                // Let's be nice 
                send("Goodbye!"); 
                System.exit(1); 
            }

            // OK, let's just send the message then 
            send(text);

            // And clear the TextField 
            textfield.setText("");

        } catch (IOException e) {

            e.printStackTrace();

        }

    }

    /** 
     * To shutdown when run as an application.  This is a 
     * fairly lame implementation.   A more self-respecting 
     * implementation would at least check to see if a save 
     * was needed. 
     */

    protected static final class AppCloser extends WindowAdapter {

        public void windowClosing(WindowEvent e) { 
            System.exit(0); 
        }

    }

    /** 
     * main() method of this program. The method creates a frame with Border Layout 
     * and adds the MultiChat GUI onto the center of the frame with text string as 
     * a label on the bottom of the frame to inform the user how to quit the application. 
     */

    public static void main(String[] args)  throws IOException
{

        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String name;
        System.out.println("Enter your name :"); 
        name=br.readLine();
         if (args.length > 0) 
            name = args[0]; 
        JFrame frame = new JFrame(); 
        frame.setTitle(name + "@ChatRoom");

        // Add the comps... 
        frame.getContentPane().setLayout(new BorderLayout()); 
        frame.getContentPane().add("Center", new MultiChat(name)); 
        frame.getContentPane().add("South", new JLabel("Type \'quit\' to exit or just close the window")); 
        frame.addWindowListener(new AppCloser()); 
        frame.pack(); 
        frame.setSize(400, 200); 
        frame.show();

    }

}