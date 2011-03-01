#ifndef __compose_header_view_impl_hpp
#define __compose_header_view_impl_hpp

#include <glibmm/refptr.h>

namespace Gtk {
  class TreeView;
  class CellRendererText;
}

namespace Compose {

  class Message;

  class HeaderViewImpl {
  public:
    HeaderViewImpl(Gtk::TreeView *);

    void set_message(Glib::RefPtr<Message> message);

  private:
    Gtk::CellRendererText *m_ref_value_cell;
    Glib::RefPtr<Message> m_ref_message;
    Gtk::TreeView *m_parent;
  };

}

#endif
