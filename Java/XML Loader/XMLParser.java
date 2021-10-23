package findprinters;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class XMLParser {

    // Variable Declarations
    static final String DATE = "date";
    static final String DATA = "data";
    static final String NOTIFICATIONS = "notifications";
    static final String PDF = "pdf";
    static final String PAGESIZE = "pagesize";
    static final String SBC = "sbc";
    static final String DEVICES = "devices";
    static final String LOCATION = "location";
    private Item item = null;

    public Item getItem() {
        return item;
    }

    @SuppressWarnings({"unchecked", "null"})
    public List<Item> readConfig(InputStream in) {
        List<Item> items = new ArrayList<Item>();
        try {
            // First, create a new XMLInputFactory
            XMLInputFactory inputFactory = XMLInputFactory.newInstance();
            // Setup a new eventReader

            XMLEventReader eventReader = inputFactory.createXMLEventReader(in);
            // read the XML document

            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();

                if (event.isStartElement()) {
                    StartElement startElement = event.asStartElement();
                    // If we have an item element, we create a new item
                    if (startElement.getName().getLocalPart().equals(DATA)) {
                        item = new Item();
                    }

                    if (event.isStartElement()) {
                        if (event.asStartElement().getName().getLocalPart()
                                .equals(NOTIFICATIONS)) {
                            event = eventReader.nextEvent();
                            item.setNotifications(event.asCharacters().getData());
                            continue;
                        }
                    }
                    if (event.asStartElement().getName().getLocalPart()
                            .equals(PDF)) {
                        event = eventReader.nextEvent();
                        item.setPdf(event.asCharacters().getData());
                        continue;
                    }

                    if (event.asStartElement().getName().getLocalPart()
                            .equals(PAGESIZE)) {
                        event = eventReader.nextEvent();
                        item.setPageSize(event.asCharacters().getData());
                        continue;
                    }

                    if (event.asStartElement().getName().getLocalPart()
                            .equals(SBC)) {
                        event = eventReader.nextEvent();
                        item.setSbc(event.asCharacters().getData());
                        continue;
                    }

                    if (event.asStartElement().getName().getLocalPart()
                            .equals(LOCATION)) {
                        event = eventReader.nextEvent();
                        item.setLocation(event.asCharacters().getData());
                        continue;
                    }
                }

                // If we reach the end of an item element, we add it to the list
                if (event.isEndElement()) {
                    EndElement endElement = event.asEndElement();
                    if (endElement.getName().getLocalPart().equals(DATA)) {
                        items.add(item);
                    }
                }
            }
        } catch (XMLStreamException e) {
        }
        return items;
    }
}
