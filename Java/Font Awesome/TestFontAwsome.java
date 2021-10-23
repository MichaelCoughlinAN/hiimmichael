/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package findprinters;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;
import java.awt.GridBagLayout;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class TestFontAwsome {

    public static void main(String[] args) {
        new TestFontAwsome();
    }

    public TestFontAwsome() {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
                } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
                }
                Path currentRelativePath = Paths.get("");
                String s = currentRelativePath.toAbsolutePath().toString();

                try {
                    GraphicsEnvironment ge
                            = GraphicsEnvironment.getLocalGraphicsEnvironment();
                    Font createFont = Font.createFont(Font.TRUETYPE_FONT, new File(s + "\\src\\findprinters\\fontawesome-webfont.ttf"));
                    ge.registerFont(createFont);

                    // try (InputStream is = TestFontAwsome.class.getResourceAsStream(s+"\\fontawesome-webfont.ttf")) {
                    // Font font = Font.createFont(Font.TRUETYPE_FONT, is);
                    createFont = createFont.deriveFont(Font.PLAIN, 24f);

                    JLabel label = new JLabel("\uf0c0");
                    label.setFont(createFont);

                    JFrame frame = new JFrame("Testing");
                    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    frame.setLayout(new GridBagLayout());
                    frame.add(label);
                    frame.pack();
                    frame.setLocationRelativeTo(null);
                    frame.setVisible(true);
                    //    } catch (IOException | FontFormatException exp) {
                    //        System.out.print(exp);
                    //     }} catch (IOException|FontFormatException e) {
                    //Handle exception
                } catch (FontFormatException ex) {
                    Logger.getLogger(TestFontAwsome.class.getName()).log(Level.SEVERE, null, ex);
                } catch (IOException ex) {
                    Logger.getLogger(TestFontAwsome.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }

}
