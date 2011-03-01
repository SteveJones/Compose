#ifndef __compose_compose_hpp
#define __compose_compose_hpp

#include <gtkmm/window.h>
#include <memory>

namespace Compose {

  class ComposeImpl;
  class Message;
  
  class Compose : public Gtk::Window {
  public:
    Compose();
    ~Compose();

    void set_message(Glib::RefPtr<Message>);

  private:
    std::auto_ptr<ComposeImpl> pimpl;
  };

}

#endif
