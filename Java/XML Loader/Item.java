package findprinters;

import java.util.ArrayList;

public class Item {
    // Variable Declarations
    private String notifications;
    private String pdf;
    private String pageSize;
    private String sbc;
    private ArrayList locations;

    public ArrayList getLocations() {
        return locations;
    }

    public void setLocations(ArrayList locations) {
        this.locations = locations;
    }

    public Item() {
        this.locations = new ArrayList();
    }

    public String getNotifications() {
        return notifications;
    }

    public void setNotifications(String notifications) {
        this.notifications = notifications;
    }

    public String getPdf() {
        return pdf;
    }

    public void setPdf(String pdf) {
        this.pdf = pdf;
    }

    public String getPageSize() {
        return pageSize;
    }

    public void setPageSize(String pageSize) {
        this.pageSize = pageSize;
    }

    public String getSbc() {
        return sbc;
    }

    public void setSbc(String sbc) {
        this.sbc = sbc;
    }

    public void setLocation(String location) {
        locations.add(location);
    }

    @Override
    public String toString() {
        String locationStr = "";
        String result = "";
        int count = 1;

        for (Object location : locations) {
            locationStr += "\n\tLocation(" + count + "): " + location;
            ++count;
        }

        result = "XML Data\n"
                + "Page Size: " + pageSize
                + "\nSBC: " + sbc
                + "\nDesktop Notifications Enabled: " + notifications
                + "\nPDF Reports Enabled: " + pdf
                + "\nDevice Locations:" + locationStr;

        return result;
    }
}
