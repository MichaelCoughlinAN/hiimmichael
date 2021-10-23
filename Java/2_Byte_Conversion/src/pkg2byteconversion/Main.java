package pkg2byteconversion;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.Math;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 *
 * @author qumjc2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        

//            String input = inFromUser.readLine();

//            int temp = encode(Double.parseDouble(input));
//            System.out.println("Encoded value: " + temp);
//            System.out.println("Decoded value: " + decode((short) temp));

        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        
        while (true) {
            // 2 byte Unisgned Integer = 0 to 65,535
            String input = inFromUser.readLine();
            double temp = Double.parseDouble(input);
            int temp2 = to4DigitInt(temp);
            
            System.out.println("Encoded " + temp2);
            System.out.println("Decoded " + decodeInt(temp2));           
            System.out.println(temp + " Pints");
            System.out.println(temp / 8 + " Gallons");
            System.out.println(temp / 2 + " Quarts");
            System.out.println(temp / 2.11338 + " Liters");          
        }
    }

    public static int to4DigitInt(double val) {
        return (int) (val * 10);
    }

    public static float decodeInt(int val) {
        return (float) (val * .10);
    }

//    public static short encode(double value) {
//        int cnt = 0;
//        while (0 != Double.compare(value, Math.floor(value))) {
//            // System.out.println(Math.floor(value));
//            value *= 10.0;
//            cnt++;
//        }
//        return (short) ((cnt << 12) + (int) value);
//    }
//
//    public static double decode(short value) {
//        int cnt = value >> 12;
//        double result = value & 0xfff;
//        while (cnt > 0) {
//            result /= 10.0;
//            cnt--;
//        }
//        return result;
//    }

}
