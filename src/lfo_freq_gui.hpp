#ifndef LFO_FREQ_GUI_H
#define LFO_FREQ_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class LfoFreqGUI: public UI<LfoFreqGUI, GtkUI<true>>
{
	public:
		LfoFreqGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		Gtk::ComboBoxText* m_comboWaveForm;
		LabeledDial* m_dialTempo;
		LabeledDial* m_dialPhi0;

		float get_tempo();
		float get_tempoMultiplier();
		float get_phi0();
};

#endif
