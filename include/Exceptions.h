/**
* @author Dr. Anvik <john.anvik@uleth.ca>, LN Wilson <n.wilson@uleth.ca>
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>

/**
* @class pointer_cannot_be_null Exceptions.h "Exceptions.h"
* @details Exception for when trying to use a null pointer
*/
class pointer_cannot_be_null : public std::runtime_error {
 public:
  /**
  * Exception for trying to use a null pointer
  * @param errMessage An error message.
  */
  explicit pointer_cannot_be_null(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif
