package com.javaquery.bluetooth;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.bluetooth.*;

public class ServicesSearch {

    /** 
     * UUID used to find specific service supported by bluetooth device
     * https://www.bluetooth.org/en-us/specification/assigned-numbers/service-discovery
     * Find UUIDs for all types of bluetooth services.
     */
    /* To find push object service */
    private UUID OBEX_OBJECT_PUSH_PROFILE = new UUID(0x1105);
    /* To find file transfer service */
    private UUID OBEX_FILE_TRANSFER_PROFILE = new UUID(0x1106);
    /* To find hands free service */
    private UUID HANDS_FREE = new UUID(0x111E);
    /* Get URL attribute from bluetooth service */
    private int URL_ATTRIBUTE = 0X0100;
    
    public Map<String, List<String>> getBluetoothDevices() {        
        /**
         * Find service on bluetooth device 
         * Note: In following line you can use one service at a time. I'm new to bluetooth programming it might me wrong perception.
         * UUID[] searchUuidSet = new UUID[]{OBEX_FILE_TRANSGER_PROFILE};
         * 
         * CORRECT: UUID[] searchUuidSet = new UUID[]{OBEX_FILE_TRANSGER_PROFILE};
         * WRONG: UUID[] searchUuidSet = new UUID[]{OBEX_FILE_TRANSGER_PROFILE, OBEX_OBJECT_PUSH_PROFILE};
         */
        /* Initialize UUID Array */
        UUID[] searchUuidSet = new UUID[]{HANDS_FREE};
        final Object serviceSearchCompletedEvent = new Object();
        int[] attrIDs = new int[]{URL_ATTRIBUTE};
        
        /* Create an object to get list of devices in range or paired */
        RemoteDeviceDiscovery remoteDeviceDiscovery = new RemoteDeviceDiscovery();
        /* Create map to return Bluetooth device address, name and URL */
        final Map<String, List<String>> mapReturnResult = new HashMap<String, List<String>>(); 

        try {
            /* Create an object of DiscoveryListener */
            DiscoveryListener listener = new DiscoveryListener() {

                /* To find bluetooth devices */
                public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                }

                /* To find bluetooth devices */
                public void inquiryCompleted(int discType) {
                }

                /* Find service URL of bluetooth device */
                public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                    for (int i = 0; i < servRecord.length; i++) {
                        /* Find URL of bluetooth device */
                        String url = servRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
                        if (url == null) {
                            continue;
                        }
                        String temporaryString = "";
                        /* Get object of bluetooth device */
                        RemoteDevice rd = servRecord[i].getHostDevice();
                        /* Get attribute from ServiceRecord */
                        DataElement serviceName = servRecord[i].getAttributeValue(URL_ATTRIBUTE);
                        if (serviceName != null) {         
                            temporaryString = serviceName.getValue() + "\n" + url;
                            
                            //System.out.print(serviceName);
                                      
                            /* Put it in map */
                            mapReturnResult.get(rd.getBluetoothAddress()).add(temporaryString);
                        } else {
                            temporaryString = "Uknown service \n" + url;
                            /* Put it in map */
                            mapReturnResult.get(rd.getBluetoothAddress()).add(temporaryString);
                        }
                    }
                }

                public void serviceSearchCompleted(int transID, int respCode) {
                    /* Notify thread when search completed */
                    synchronized (serviceSearchCompletedEvent) {
                        serviceSearchCompletedEvent.notifyAll();
                    }
                }
            };

            /* Get list of bluetooth device from class RemoteDeviceDiscovery */
            for (Enumeration en = remoteDeviceDiscovery.getDevices().elements(); en.hasMoreElements();) {
                /* Get RemoteDevice object */
                RemoteDevice btDevice = (RemoteDevice) en.nextElement();
                /* Create list to return details */
                List<String> listDeviceDetails = new ArrayList<String>();
                
                try {
                    /* Add bluetooth device name and address in list */
                    listDeviceDetails.add(btDevice.getFriendlyName(false));
                    listDeviceDetails.add(btDevice.getBluetoothAddress());
                } catch (Exception e) {
                }
                
                /* Put bluetooth device details in map */
                mapReturnResult.put(btDevice.getBluetoothAddress(), listDeviceDetails);
                synchronized (serviceSearchCompletedEvent) {
                    LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(attrIDs, searchUuidSet, btDevice, listener);
                    serviceSearchCompletedEvent.wait();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        /* Return bluetooth devices detail */
        return mapReturnResult;
    }
}
