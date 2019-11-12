package com.javaquery.bluetooth;

import java.util.Enumeration;
import java.util.Vector;
import javax.bluetooth.DeviceClass;
import javax.bluetooth.DiscoveryAgent;
import javax.bluetooth.DiscoveryListener;
import javax.bluetooth.LocalDevice;
import javax.bluetooth.RemoteDevice;
import javax.bluetooth.ServiceRecord;

public class RemoteDeviceDiscovery {

    public Vector getDevices() {
        /* Create Vector variable */
        final Vector devicesDiscovered = new Vector();
        try {
            final Object inquiryCompletedEvent = new Object();
            /* Clear Vector variable */
            devicesDiscovered.clear();

            /* Create an object of DiscoveryListener */
            DiscoveryListener listener = new DiscoveryListener() {

                public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                    /* Get devices paired with system or in range(Without Pair) */
                    devicesDiscovered.addElement(btDevice);
                }

                public void inquiryCompleted(int discType) {
                    /* Notify thread when inquiry completed */
                    synchronized (inquiryCompletedEvent) {
                        inquiryCompletedEvent.notifyAll();
                    }
                }

                /* To find service on bluetooth */
                public void serviceSearchCompleted(int transID, int respCode) {
                }

                /* To find service on bluetooth */
                public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                }
            };

            synchronized (inquiryCompletedEvent) {
                /* Start device discovery */
                boolean started = LocalDevice.getLocalDevice().getDiscoveryAgent().startInquiry(DiscoveryAgent.GIAC, listener);
                
                if (started) {
                    System.out.println("wait for device inquiry to complete...");
                    inquiryCompletedEvent.wait();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        /* Return list of devices */
        return devicesDiscovered;
    }
}
