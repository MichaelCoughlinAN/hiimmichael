#include "XMLSceneParser.h"

using namespace sivelab;

XMLSceneParser::XMLSceneParser()
{
}

XMLSceneParser::XMLSceneParser(const std::string &filename)
  : m_currFileName(filename)
{
  f_parse();
}

XMLSceneParser::~XMLSceneParser()
{
  f_cleanup();
}

void XMLSceneParser::parseFile(const std::string &filename)
{
  f_cleanup();
  m_currFileName = filename;
  f_parse();
}

void XMLSceneParser::f_parse()
{
  SceneElementCreator *creator = 0;

  read_xml(m_currFileName, m_ptree);

  //  if (m_doc == NULL) {
  //    std::cerr << "Error: could not parse file " << m_currFileName << std::endl;
  //  }

  // call the call back for the scene, which could potentially over-ride all that is here. However, it would 

  using boost::property_tree::ptree;
  BOOST_FOREACH( ptree::value_type const &v, m_ptree.get_child("scene") ) {

    if (v.first == "sceneParameters") {
      creator = m_elemCallbackMap["sceneParameters"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::SCENEPROPS;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No \"sceneParameters\" creator callback provided!" << std::endl;
    }

    if (v.first == "camera") {
      creator = m_elemCallbackMap["camera"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::CAMERA;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No camera creator callback provided!" << std::endl;
    }

    if (v.first == "transform") {
      creator = m_elemCallbackMap["transform"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::TRANSFORM;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No transform creator callback provided!" << std::endl;
    }

    if (v.first == "light") {
      creator = m_elemCallbackMap["light"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::LIGHT;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No light creator callback provided!" << std::endl;
    }

    if (v.first == "shader") {
      creator = m_elemCallbackMap["shader"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::SHADER;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No shader creator callback provided!" << std::endl;
    }
	
    if (v.first == "texture") {
      creator = m_elemCallbackMap["texture"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::TEXTURE;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No texture creator callback provided!" << std::endl;
    }

    if (v.first == "shape") {
      creator = m_elemCallbackMap["shape"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::SHAPE;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No shape creator callback provided!" << std::endl;
    }

    if (v.first == "instance") {
      creator = m_elemCallbackMap["instance"];
      if (creator)
	{
	  creator->m_otype = SceneElementCreator::INSTANCE;
	  creator->instance( v );
	}
      else 
	std::cerr << "Warning!!!! No instance creator callback provided!" << std::endl;
    }
  }
}

void XMLSceneParser::f_cleanup()
{
}

#if 0

void XMLSceneParser::parseScene(xmlNode *nPtr)
{
}


void XMLSceneParser::parseCamera(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["camera_name"] = SceneDataContainer::emptyProp("name");
  nodeData["camera_type"] = SceneDataContainer::emptyProp("type");

  nodeData["camera_position"] = SceneDataContainer::emptyElem("position");
  nodeData["camera_viewDir"] = SceneDataContainer::emptyElem("viewDir");
  nodeData["camera_lookatPoint"] = SceneDataContainer::emptyElem("lookatPoint");
  nodeData["camera_focalLength"] = SceneDataContainer::emptyElem("focalLength");
  nodeData["camera_imagePlaneWidth"] = SceneDataContainer::emptyElem("imagePlaneWidth");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("name", nPtr, nodeData["camera_name"]);
  retrieveProperty("type", nPtr, nodeData["camera_type"]);

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  while (currNodePtr != NULL) 
    {
      // Camera position
      retrieveElementData("position", currNodePtr, nodeData["camera_position"]);
      
      // Camera view direction
      retrieveElementData("viewDir", currNodePtr, nodeData["camera_viewDir"]);
      
      // Camera lookat point
      retrieveElementData("lookatPoint", currNodePtr, nodeData["camera_lookatPoint"]);

      // Camera focal length
      retrieveElementData("focalLength", currNodePtr, nodeData["camera_focalLength"]);

      // Camera image plane width
      retrieveElementData("imagePlaneWidth", currNodePtr, nodeData["camera_imagePlaneWidth"]);

      currNodePtr = currNodePtr->next;
    }

  return;
}



void XMLSceneParser::parseLight(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["light_type"] = SceneDataContainer::emptyProp("type");

  nodeData["light_position"] = SceneDataContainer::emptyElem("position");
  nodeData["light_intensity"] = SceneDataContainer::emptyElem("intensity");

  nodeData["light_normal"] = SceneDataContainer::emptyElem("normal");
  nodeData["light_width"] = SceneDataContainer::emptyElem("width");
  nodeData["light_length"] = SceneDataContainer::emptyElem("length");

  // add spherical light properties
  nodeData["light_radius"] = SceneDataContainer::emptyElem("radius");

  // mesh lights
  nodeData["light_file"] = SceneDataContainer::emptyElem("file");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("type", nPtr, nodeData["light_type"]);

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  while (currNodePtr != NULL) 
    {
      // Light position
      retrieveElementData("position", currNodePtr, nodeData["light_position"]);

      // Light Intensity
      retrieveElementData("intensity", currNodePtr, nodeData["light_intensity"]);

      // Light Normal
      retrieveElementData("normal", currNodePtr, nodeData["light_normal"]);

      // Light length
      retrieveElementData("length", currNodePtr, nodeData["light_length"]);

      // Light width
      retrieveElementData("width", currNodePtr, nodeData["light_width"]);

      retrieveElementData("radius", currNodePtr, nodeData["light_radius"]);

      retrieveElementData("file", currNodePtr, nodeData["light_file"]);
      
      currNodePtr = currNodePtr->next;
    }

  return;
}

void XMLSceneParser::parseTransform(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["transform_name"] = SceneDataContainer::emptyProp("name");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("name", nPtr, nodeData["transform_name"]);

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  int xformCount = 0;
  while (currNodePtr != NULL) 
    {
      std::ostringstream ndataName;

      ndataName << "transform_" << std::setfill('0') << std::setw(3) << xformCount << '_';

      // If the element tag matches and it wasn't previously set, so
      // replace the contents appropriately in the SceneDataContainer, d
      if (matchesNodeName(currNodePtr->name, "translate"))
	{
	  xmlChar *key = xmlNodeListGetString(m_doc, currNodePtr->xmlChildrenNode, 1);

	  ndataName << "translate";
	  nodeData[ndataName.str()] = SceneDataContainer::emptyElem("translate");
	      
	  SceneDataContainer &d = nodeData[ndataName.str()];
	  d.val = (const char *)key;
	  d.isSet = true;

	  xformCount++;

	  xmlFree(key);
	}

      else if (matchesNodeName(currNodePtr->name, "rotate"))
	{
	  xmlChar *key = xmlNodeListGetString(m_doc, currNodePtr->xmlChildrenNode, 1);

	  xmlChar *propName = xmlGetProp(currNodePtr, (const xmlChar*)"axis");

	  if ((char)*propName == 'X')
	    {
	      ndataName << "rotateX";
	      nodeData[ndataName.str()] = SceneDataContainer::emptyElem("rotateX");
	      
	      SceneDataContainer &d = nodeData[ndataName.str()];
	      d.val = (const char *)key;
	      d.isSet = true;

	      xformCount++;
	    }
	  else if ((char)*propName == 'Y')
	    {
	      ndataName << "rotateY";
	      nodeData[ndataName.str()] = SceneDataContainer::emptyElem("rotateY");
	      
	      SceneDataContainer &d = nodeData[ndataName.str()];
	      d.val = (const char *)key;
	      d.isSet = true;

	      xformCount++;
	    }
	  else if ((char)*propName == 'Z')
	    {
	      ndataName << "rotateZ";
	      nodeData[ndataName.str()] = SceneDataContainer::emptyElem("rotateZ");
	      
	      SceneDataContainer &d = nodeData[ndataName.str()];
	      d.val = (const char *)key;
	      d.isSet = true;

	      xformCount++;
	    }

	  xmlFree(propName);
	  xmlFree(key);
	}

      else if (matchesNodeName(currNodePtr->name, "scale"))
	{
	  xmlChar *key = xmlNodeListGetString(m_doc, currNodePtr->xmlChildrenNode, 1);

	  ndataName << "scale";
	  nodeData[ndataName.str()] = SceneDataContainer::emptyElem("scale");
	      
	  SceneDataContainer &d = nodeData[ndataName.str()];
	  d.val = (const char *)key;
	  d.isSet = true;

	  xformCount++;

	  xmlFree(key);
	}

      currNodePtr = currNodePtr->next;
    }

  return;
}


void XMLSceneParser::parseTexture(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["texture_type"] = SceneDataContainer::emptyProp("type");
  nodeData["texture_name"] = SceneDataContainer::emptyProp("name");
  nodeData["texture_sourcefile"] = SceneDataContainer::emptyElem("sourcefile");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("type", nPtr, nodeData["texture_type"]);
  retrieveProperty("name", nPtr, nodeData["texture_name"]);

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  while (currNodePtr != NULL) 
    {
      // Texture source file
      retrieveElementData("sourcefile", currNodePtr, nodeData["texture_sourcefile"]);
      currNodePtr = currNodePtr->next;
    }

  return;
}

void XMLSceneParser::parseShader(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["shader_ref"] = SceneDataContainer::emptyProp("ref");
  nodeData["shader_name"] = SceneDataContainer::emptyProp("name");
  nodeData["shader_type"] = SceneDataContainer::emptyProp("type");

  nodeData["shader_diffuse"] = SceneDataContainer::emptyElem("diffuse");
  nodeData["shader_diffusetex"] = SceneDataContainer::emptyElem("diffusetex");
  nodeData["shader_specular"] = SceneDataContainer::emptyElem("specular");
  nodeData["shader_emissive"] = SceneDataContainer::emptyElem("emissive");
  nodeData["shader_phongExp"] = SceneDataContainer::emptyElem("phongExp");
  nodeData["shader_mirrorCoef"] = SceneDataContainer::emptyElem("mirrorCoef");
  nodeData["shader_roughness"] = SceneDataContainer::emptyElem("roughness");

  nodeData["shader_refractiveIndex"] = SceneDataContainer::emptyElem("refractiveIndex");
  nodeData["shader_attenuationCoef"] = SceneDataContainer::emptyElem("attenuationCoef");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("ref", nPtr, nodeData["shader_ref"]);
  retrieveProperty("name", nPtr, nodeData["shader_name"]);
  retrieveProperty("type", nPtr, nodeData["shader_type"]);

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  while (currNodePtr != NULL) 
    {
      retrieveElementData("diffuse", currNodePtr, nodeData["shader_diffuse"]);
      retrieveElementData("diffusetex", currNodePtr, nodeData["shader_diffusetex"]);
      retrieveElementData("specular", currNodePtr, nodeData["shader_specular"]);
      retrieveElementData("emissive", currNodePtr, nodeData["shader_emissive"]);
      retrieveElementData("phongExp", currNodePtr, nodeData["shader_phongExp"]);
      retrieveElementData("mirrorCoef", currNodePtr, nodeData["shader_mirrorCoef"]);
      retrieveElementData("roughness", currNodePtr, nodeData["shader_roughness"]);

      retrieveElementData("refractiveIndex", currNodePtr, nodeData["shader_refractiveIndex"]);
      retrieveElementData("attenuationCoef", currNodePtr, nodeData["shader_attenuationCoef"]);
      
      currNodePtr = currNodePtr->next;
    }

  return;
}

void XMLSceneParser::parseShape(xmlNode *nPtr, std::map<std::string, SceneDataContainer>& nodeData)
{
  //
  // register scene data components for camera
  //
  nodeData["shape_name"] = SceneDataContainer::emptyProp("name");
  nodeData["shape_type"] = SceneDataContainer::emptyProp("type");
  nodeData["shape_id"] = SceneDataContainer::emptyProp("id");
  nodeData["shape_subdivision"] = SceneDataContainer::emptyProp("subdivision");
  nodeData["shape_slices"] = SceneDataContainer::emptyProp("slices");
  nodeData["shape_topo"] = SceneDataContainer::emptyProp("topo");
  
  nodeData["shape_center"] = SceneDataContainer::emptyElem("center");
  nodeData["shape_radius"] = SceneDataContainer::emptyElem("radius");
  nodeData["shape_minPt"] = SceneDataContainer::emptyElem("minPt");
  nodeData["shape_maxPt"] = SceneDataContainer::emptyElem("maxPt");
  nodeData["shape_height"] = SceneDataContainer::emptyElem("height");
  nodeData["shape_v0"] = SceneDataContainer::emptyElem("v0");
  nodeData["shape_v1"] = SceneDataContainer::emptyElem("v1");
  nodeData["shape_v2"] = SceneDataContainer::emptyElem("v2");

  //
  // Attempt to set the correct values in the properties and elements
  //
  retrieveProperty("name", nPtr, nodeData["shape_name"]);
  retrieveProperty("type", nPtr, nodeData["shape_type"]);
  retrieveProperty("id", nPtr, nodeData["shape_id"]);
  
  // property that might exist for subdivision level
  retrieveProperty("subdivision", nPtr, nodeData["shape_subdivision"]);  

  // property that might exist for slices
  retrieveProperty("slices", nPtr, nodeData["shape_slices"]);  

  // property that might exist for topo - open or closed... open is default for shapes that this applies to
  retrieveProperty("topo", nPtr, nodeData["shape_topo"]);  

  xmlNode *currNodePtr = nPtr->xmlChildrenNode;
  while (currNodePtr != NULL) 
    {
      // shader information
      if (matchesNodeName(currNodePtr->name, "shader"))
	{
	  parseShader(currNodePtr, nodeData);
	}

      // transform information
      if (matchesNodeName(currNodePtr->name, "transform"))
	{
	  parseTransform(currNodePtr, nodeData);
	}

      // sphere values
      retrieveElementData("center", currNodePtr, nodeData["shape_center"]);
      retrieveElementData("radius", currNodePtr, nodeData["shape_radius"]);

      // box values
      retrieveElementData("minPt", currNodePtr, nodeData["shape_minPt"]);
      retrieveElementData("maxPt", currNodePtr, nodeData["shape_maxPt"]);

      // cylinder values
      // Center and radius have already been picked up by the sphere requirements... need height
      retrieveElementData("height", currNodePtr, nodeData["shape_height"]);      

      // triangle values
      retrieveElementData("v0", currNodePtr, nodeData["shape_v0"]);      
      retrieveElementData("v1", currNodePtr, nodeData["shape_v1"]);      
      retrieveElementData("v2", currNodePtr, nodeData["shape_v2"]);

      // mesh values
      retrieveElementData("file", currNodePtr, nodeData["shape_file"]);

      // add in support to parse the texture elements

      currNodePtr = currNodePtr->next;
    }

  return;
}

bool XMLSceneParser::retrieveProperty(const std::string &name, xmlNodePtr ptr, SceneDataContainer &d)
{
  xmlChar *propName = xmlGetProp(ptr, (const xmlChar*)name.c_str());
  if (propName && d.isSet == false)
    {
      // we found it and it wasn't previously set, so replace the
      // contents appropriately in the SceneDataContainer, d
      d.val = (char *)propName;
      d.isSet = true;

      xmlFree(propName);
      return true;
    }

  xmlFree(propName);
  return false;
}


void XMLSceneParser::f_printNodeMapData(const std::map<std::string, SceneDataContainer>& nodeMap, const std::string &name) const
{
  std::map<std::string, SceneDataContainer>::const_iterator sdIter;
  for (sdIter=nodeMap.begin(); sdIter != nodeMap.end(); sdIter++)
    {
      SceneDataContainer sd = sdIter->second;
      std::cout << name << "[" << sdIter->first << "]: " 
		<< sd.dtype << ", " << sd.name << ", " 
		<< sd.val << ", " << sd.isSet << std::endl;
    }
}
#endif

void XMLSceneParser::registerCallback(const std::string &elementName, SceneElementCreator *secPtr)
{
  m_elemCallbackMap[elementName] = secPtr;
}
