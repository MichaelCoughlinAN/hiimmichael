#ifndef __SCENE_DATA_CONTAINER_H__
#define __SCENE_DATA_CONTAINER_H__ 1

#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>

namespace sivelab 
{

  using boost::property_tree::ptree;

#if 0
  // Forward reference.
  class SceneDataContainer
  {
  public:
    enum SceneDataType
      {
	PROPERTY,
	ELEMENT,
	UNKNOWN
      };

    SceneDataContainer() : dtype(UNKNOWN), name(""), val(""), isSet(false) {}
    SceneDataContainer(const SceneDataType dt, const std::string &n, const std::string& v, bool setState=true) 
      : dtype(dt), name(n), val(v), isSet(setState) {}

    static SceneDataContainer emptyProp(const std::string &s) 
    { 
      return SceneDataContainer(SceneDataContainer::PROPERTY, s, "", false); 
    }

    static SceneDataContainer emptyElem(const std::string &s) 
    { 
      return SceneDataContainer(SceneDataContainer::ELEMENT, s, "", false); 
    }

    SceneDataType dtype;
    std::string name;
    std::string val;
    bool isSet;
  };
#endif

  class SceneElementCreator
  {
  public:
    enum SceneObjectType
      {
	SCENEPROPS,
	CAMERA,
	LIGHT,
	SHADER,
	SHAPE,
	TEXTURE,
	TRANSFORM,
	INSTANCE,
	UNKNOWN_TYPE
      };

    SceneElementCreator() 
      : m_otype(SceneElementCreator::UNKNOWN_TYPE) {}
    virtual ~SceneElementCreator() {}
    
    virtual void instance( ptree::value_type const &v ) = 0;

    SceneObjectType m_otype;

  private:
  };
}

#endif //  __SCENE_DATA_CONTAINER_H__ 1
