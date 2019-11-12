package com.javaquery.swing;

import com.javaquery.bluetooth.ServicesSearch;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.UIManager;

public class BluetoothDevices extends javax.swing.JFrame {

    /* DefaultListModel to attach it with JList */
    private DefaultListModel defaultModel;
    /* Map to get device details list */
    private Map<String, List<String>> mapReturnResult = new HashMap<String, List<String>>();
    /* Map to identify device on user click of JList */
    private Map<Integer, List<String>> mapDevicePosition = new HashMap<Integer, List<String>> ();

    public BluetoothDevices() {
        initComponents();
        defaultModel = new DefaultListModel();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        JListBluetoothDevices = new javax.swing.JList();
        lblDeviceName = new javax.swing.JLabel();
        lblRuntimeDeviceName = new javax.swing.JLabel();
        lblDeviceAddress = new javax.swing.JLabel();
        lblRuntimeDeviceAddress = new javax.swing.JLabel();
        lblServiceDetails = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        JTextAreaServiceDetails = new javax.swing.JTextArea();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Bluecove Bluetooth Discovery");
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowOpened(java.awt.event.WindowEvent evt) {
                formWindowOpened(evt);
            }
        });

        JListBluetoothDevices.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                JListBluetoothDevicesMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(JListBluetoothDevices);

        lblDeviceName.setText("Bluetooth Device Name");

        lblDeviceAddress.setText("Bluetooth Device Address");

        lblServiceDetails.setText("Service Details");

        JTextAreaServiceDetails.setColumns(20);
        JTextAreaServiceDetails.setRows(5);
        jScrollPane2.setViewportView(JTextAreaServiceDetails);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(lblDeviceName)
                            .addComponent(lblDeviceAddress))
                        .addGap(73, 73, 73)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(lblRuntimeDeviceAddress)
                            .addComponent(lblRuntimeDeviceName, javax.swing.GroupLayout.PREFERRED_SIZE, 144, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(lblServiceDetails)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 475, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 185, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lblDeviceName)
                            .addComponent(lblRuntimeDeviceName))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lblDeviceAddress)
                            .addComponent(lblRuntimeDeviceAddress))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(lblServiceDetails)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jScrollPane2, 0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

	/* Search for bluetooth device when window opened */
    private void formWindowOpened(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowOpened
        int intDevicePosition = 0;
        JListBluetoothDevices.setModel(defaultModel);        

        /* Create an object of ServicesSearch */
        ServicesSearch ss = new ServicesSearch();
        /* Get bluetooth device details */
        mapReturnResult = ss.getBluetoothDevices();

        /* Add devices in JList */
        for (Map.Entry<String, List<String>> entry : mapReturnResult.entrySet()) {            
            defaultModel.addElement(entry.getValue().get(0));
            mapDevicePosition.put(intDevicePosition, entry.getValue());
            intDevicePosition++;
        }
    }//GEN-LAST:event_formWindowOpened

	/* On click of any item in List Box */
    private void JListBluetoothDevicesMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_JListBluetoothDevicesMouseClicked
		/* Get bluetooth device details from temporary list */
        List<String> tmpDeviceDetails = mapDevicePosition.get(JListBluetoothDevices.getSelectedIndex());
		/* Set bluetooth device name */
        lblRuntimeDeviceName.setText(tmpDeviceDetails.get(0));
		/* Set bluetooth device Address */
        lblRuntimeDeviceAddress.setText(tmpDeviceDetails.get(1));       
        
        if(tmpDeviceDetails.size() > 2 && tmpDeviceDetails.get(2) != null){
			/* Set bluetooth device service name and URL */
            JTextAreaServiceDetails.setText(tmpDeviceDetails.get(2));
        }else{
            JTextAreaServiceDetails.setText("Service not found");
        }
    }//GEN-LAST:event_JListBluetoothDevicesMouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                 /* To set new look and feel */
                JFrame.setDefaultLookAndFeelDecorated(true);
                try {
                    /**
                     * Change look and feel of JFrame to Nimbus 
                     * For other look and feel check
					 * http://www.javaquery.com/2013/06/how-to-applyset-up-swing-look-and-feel.html
                     */
                    UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
                } catch (Exception ex) {
                   ex.printStackTrace();
                }
                /* Create an object of BluetoothDevices */
                BluetoothDevices bluetoothDevicesFrame = new BluetoothDevices();
                /* make BluetoothDevices visible */
                bluetoothDevicesFrame.setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JList JListBluetoothDevices;
    private javax.swing.JTextArea JTextAreaServiceDetails;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JLabel lblDeviceAddress;
    private javax.swing.JLabel lblDeviceName;
    private javax.swing.JLabel lblRuntimeDeviceAddress;
    private javax.swing.JLabel lblRuntimeDeviceName;
    private javax.swing.JLabel lblServiceDetails;
    // End of variables declaration//GEN-END:variables
}
