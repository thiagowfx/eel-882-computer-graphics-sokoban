#include "soko_object.h"
namespace Sokoban {
  /**
  This class represents an object that is a light box on a sokoban board
  */
  class SokoLightBox : SokoObject {
    public:

      /**
      This method returns the type of this SokoObject
      */
      virtual Type getType() {
        return LIGHT_BOX;
      }
  };
}