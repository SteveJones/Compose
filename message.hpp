#ifndef __compose_message_hpp
#define __compose_message_hpp

#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelfilter.h>
#include <gtkmm/textbuffer.h>

namespace Compose {

  class HeaderModelColumns : public Gtk::TreeModelColumnRecord {
  public:
    HeaderModelColumns();

    Gtk::TreeModelColumn<Glib::ustring> m_name;
    Gtk::TreeModelColumn<Glib::ustring> m_value;
    Gtk::TreeModelColumn<bool> m_shown;
  };

  const HeaderModelColumns &header_model();
  
  // Represents an email message
  struct Message : public Glib::Object {
    Message();

    Glib::RefPtr<Gtk::TextBuffer> m_ref_body_buffer;
    Glib::RefPtr<Gtk::ListStore> m_ref_headers;
    Glib::RefPtr<Gtk::TreeModelFilter> m_ref_visible_headers;

    void connect_header_edited(Glib::SignalProxy2<void,
			       const Glib::ustring &,
			       const Glib::ustring &>);
    void set_header_visible(const Glib::ustring &, bool);
    void set_headers_visible(bool);

  private:
    class visible_header_setter {
      Glib::ustring m_name;
      bool m_value;
      
    public:
      visible_header_setter(const Glib::ustring &name, bool value);
      void operator ()(Gtk::TreeIter) const;
    };

    void on_header_edited(const Glib::ustring &, const Glib::ustring &);
  };
}

#endif
