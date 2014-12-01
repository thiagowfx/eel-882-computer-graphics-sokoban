#ifndef _SOKO_BOARD_H_
#define _SOKO_BOARD_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "soko_position.hpp"
#include "soko_object.hpp"
using namespace std;

namespace Sokoban {
  /** 
  This class represents a Sokoban board.  
  */
  class SokoBoard {
    private:
      /// This nested class represents a movement from the character
      class Movement {
        public:
          Movement(Direction direction, bool boxMoved) : direction(direction), 
                                                           boxMoved(boxMoved) {};
          /// The direction of the movement
          Direction direction;

          /// True if a box was moved with this movement
          bool boxMoved;
      };

      /// This nested class represents an animated object
      class Animated {
        friend SokoBoard;
        public:
          Animated(SokoObject obj_, 
                  SokoPosition start_, 
                  Direction direction_,
                  int totalSteps_) : 
                  obj(obj_),
                  startPosition(start_),
                  direction(direction_),
                  stepCounter(0)
                  { };
          
          SokoPosition getEndPosition() { return startPosition + direction; };
          SokoPosition getStartPosition() { return startPosition; };
          Direction getDirection() { return direction; };
          int getTotalSteps() { return totalSteps; };
          int getStepCounter() { return stepCounter; };
          SokoObject getObject() { return obj; };

        private:
          SokoObject obj;
          SokoPosition startPosition;
          Direction direction;
          int totalSteps, stepCounter;          
      };
    public:

      /// Constructs a new SokoBoard from @filename.
      SokoBoard(std::string filename);

      /// Move the character to direction indicated by @direction.      
      bool move(Direction direction);

      /// Prints a representation of this class to a ostream.
      friend ostream& operator<<(ostream&, const SokoBoard&);

      /// Return the string representation of this object.
      std::string toString() const;

      /// Get the number of moves of the character so far.
      unsigned getNumberOfMoves() const;

      /// Get the number of boxes of this board.
      unsigned getNumberOfBoxes() const;

      /// Get the number of light boxes of this board.
      unsigned getNumberOfLightBoxes() const;

      /// Get the number of heavy boxes of this board.
      unsigned getNumberOfHeavyBoxes() const;

      /// Get the number of targets of this board.
      unsigned getNumberofTargets() const;

      /// Get the number of boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedBoxes() const;

      /// Get the number of light boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedLightBoxes() const;

      /// Get the number of heavy boxes not yet moved to a target in this board.
      unsigned getNumberOfUnresolvedHeavyBoxes() const;

      /// Return the number of rows of the static board.
      unsigned getNumberOfRows() const;

      /// Return the number of columns of the static board.
      unsigned getNumberOfColumns() const;

      /// Returns true if this board is finished, with all boxes moved to targets.
      bool isFinished() const;

      /// Returns the element in position x, y of the dynamic board.
      SokoObject getDynamic(int x, int y);

      /// Returns the element in position x, y of the static board.
      SokoObject getStatic(int x, int y);

      /// Undo the last character movement.
      bool undo();

      /// Returns the animated objects list
      std::vector< Animated > getAnimated();

    private:
      unsigned unresolvedLightBoxes, unresolvedHeavyBoxes, 
        lightBoxes, heavyBoxes, targets;

      

      /// A vector with all the objects that are currently being animated
      std::vector< Animated > animated;

      /// The stack with all the movements that happened.
      std::stack< Movement > undoTree;

      /// The character position.
      SokoPosition characterPosition;

      /// The direction the character is facing.
      Direction characterDirection;
      
      /// Stores dynamic SokoObjects of a board, such as boxes and the character.
      std::vector< std::vector< SokoObject > > dynamicBoard;
      
      /// Stores static SokoObjects of a board, such as walls and targets.
      std::vector< std::vector< SokoObject > > staticBoard;

      /// Update how many boxes are (un)resolved.
      void updateUnresolvedBoxes();
  };
}

#endif // _SOKO_BOARD_H_
