#ifndef AMP_GUI_H
#define AMP_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class AmpGUI: public UI<AmpGUI, GtkUI<true>>
{
	public:
		AmpGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialGain;

		float get_gain();
};

#endif
