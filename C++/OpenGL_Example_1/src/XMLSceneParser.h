#ifndef __SIVELAB_XML_SCENE_PARSER_H__
#define __SIVELAB_XML_SCENE_PARSER_H__ 1

#include <cassert>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "SceneDataContainer.h"

namespace sivelab
{

  class XMLSceneParser 
  {
  public:
    XMLSceneParser();
    XMLSceneParser(const std::string &filename);
    ~XMLSceneParser();

    void parseFile(const std::string &filename);

    // registration functors
    void registerCallback(const std::string &elementName, SceneElementCreator *secPtr);

  private:
    void f_parse();
    void f_cleanup();

#if 0
    void f_printNodeMapData(const std::map<std::string, SceneDataContainer>& nodeMap, const std::string &name) const;

    bool matchesNodeName(const xmlChar* str, const std::string &tag)
    {
      if ((!xmlStrcmp(str, (const xmlChar *)tag.c_str()))) 
	return true;
      else
	return false;
    }

    bool retrieveElementData(const std::string &name, xmlNodePtr ptr, SceneDataContainer &d);
    bool retrieveProperty(const std::string &name, xmlNodePtr ptr, SceneDataContainer &d);

    // Scene Related parsing elements
    void parseScene(xmlNode *nPtr);
    void parseCamera(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
    void parseLight(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
    void parseTexture(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
    void parseTransform(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
    void parseShader(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
    void parseShape(xmlNode *nPtr, std::map<std::string, SceneDataContainer> &nodeData);
#endif

    ptree m_ptree;
    std::string m_currFileName;

    std::map<std::string, SceneElementCreator *> m_elemCallbackMap;
  };

}

#endif //  __SIVELAB_XML_SCENE_PARSER_H__ 1
