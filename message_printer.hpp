#ifndef __compose_message_printer_hpp
#define __compose_message_printer_hpp

#include "message.hpp"
#include <iosfwd>

namespace Compose {

  std::ostream &operator <<(std::ostream &, Glib::RefPtr<Message>);

}

#endif
