package findprinters;

import java.io.OutputStream;
import java.util.ArrayList;

import javax.xml.stream.XMLEventFactory;
import javax.xml.stream.XMLEventWriter;
import javax.xml.stream.XMLOutputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartDocument;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class XMLGenerator {

    // Variable Declaration
    private OutputStream configFile;
    private final String notifications;
    private final String pdf;
    private final String pageSize;
    private final String sbc;
    private final ArrayList locations;

    XMLGenerator(String notifications, String pdf, String pageSize, String sbc, ArrayList locations) {
        this.notifications = notifications;
        this.pdf = pdf;
        this.pageSize = pageSize;
        this.sbc = sbc;
        this.locations = locations;
    }

    public void setFile(OutputStream in) {
        this.configFile = in;
    }

    public void saveConfig() throws Exception {
        // create an XMLOutputFactory
        XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
        // create XMLEventWriter
        XMLEventWriter eventWriter = outputFactory
                .createXMLEventWriter(configFile);

        // create an EventFactory
        XMLEventFactory eventFactory = XMLEventFactory.newInstance();
        XMLEvent end = eventFactory.createDTD("\n");
        // create and write Start TagcreateStartDocument(String encoding, String version)
        StartDocument startDocument = eventFactory.createStartDocument("UTF-8", "1.0");
        eventWriter.add(startDocument);

        // create config open tag
        StartElement configStartElement = eventFactory.createStartElement("",
                "", "config");
        eventWriter.add(configStartElement);
        eventWriter.add(end);

        eventWriter.add(eventFactory.createStartElement("",
                "", "data"));
        eventWriter.add(end);

        // Write the different nodes
        createNode(eventWriter, "notifications", notifications);
        createNode(eventWriter, "pdf", pdf);
        createNode(eventWriter, "pagesize", pageSize);
        createNode(eventWriter, "sbc", sbc);

        for (Object location : locations) {
            createNode(eventWriter, "location", location.toString());
        }

        eventWriter.add(eventFactory.createEndElement("", "", "data"));
        eventWriter.add(end);
        eventWriter.add(eventFactory.createEndElement("", "", "config"));
        eventWriter.add(end);
        eventWriter.add(eventFactory.createEndDocument());
        eventWriter.close();
    }

    private void createNode(XMLEventWriter eventWriter, String name,
            String value) throws XMLStreamException {

        XMLEventFactory eventFactory = XMLEventFactory.newInstance();
        XMLEvent end = eventFactory.createDTD("\n");
        XMLEvent tab = eventFactory.createDTD("\t");
        // create Start node
        StartElement sElement = eventFactory.createStartElement("", "", name);
        eventWriter.add(tab);
        eventWriter.add(sElement);
        // create Content
        Characters characters = eventFactory.createCharacters(value);
        eventWriter.add(characters);
        // create End node
        EndElement eElement = eventFactory.createEndElement("", "", name);
        eventWriter.add(eElement);
        eventWriter.add(end);

    }

}
