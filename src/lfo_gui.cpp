#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "lfo_gui.hpp"
#include "lfo.hpp"
#include "g_dial.hpp"

LfoGUI::LfoGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(true));

	Label *p_labelWaveForm = manage (new Label("Wave Form"));
	p_mainWidget->pack_start(*p_labelWaveForm);

	m_comboWaveForm = manage (new ComboBoxText());
	m_comboWaveForm->append_text("Sine");
	m_comboWaveForm->append_text("Triangle");
	m_comboWaveForm->append_text("Sawtooth Up");
	m_comboWaveForm->append_text("Sawtooth Down");
	m_comboWaveForm->append_text("Rectangle");
	m_comboWaveForm->append_text("S & H");

	color->set_rgb(7710, 8738, 9252);
	m_comboWaveForm->modify_bg(Gtk::STATE_NORMAL, *color);
	m_comboWaveForm->modify_base(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotWaveForm = compose(bind<0> (mem_fun(*this, &LfoGUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number));
	m_comboWaveForm->signal_changed().connect(p_slotWaveForm);

	p_mainWidget->pack_start(*m_comboWaveForm);

	Label *p_labelFrequency = manage (new Label("Frequency"));
	p_mainWidget->pack_start(*p_labelFrequency);

	slot<void> p_slotFrequency = compose(bind<0>(mem_fun(*this, &LfoGUI::write_control), p_frequency), mem_fun(*this,  &LfoGUI::get_freq));
	m_dialFreq = new Dial(p_slotFrequency, p_frequency, 0, 100, true, 1);
	Alignment *p_alignmentFreq = manage (new Alignment(0.5, 0.5, 1, 1));
	p_alignmentFreq->add(*m_dialFreq);
	p_mainWidget->pack_start(*p_alignmentFreq);

	Label *p_labelPhi0 = manage (new Label("Phi0"));
	p_mainWidget->pack_start(*p_labelPhi0);

	slot<void> p_slotPhi0 = compose(bind<0> (mem_fun(*this, &LfoGUI::write_control), p_phi0), mem_fun(*this, &LfoGUI::get_phi0));
	m_dialPhi0 = new Dial(p_slotPhi0, p_phi0, 0, 6.28, false, 0.01);
	Alignment *p_alignmentPhi0 = manage (new Alignment(0.5, 0.5, 1, 1));
	p_alignmentPhi0->add(*m_dialPhi0);
	p_mainWidget->pack_start(*p_alignmentPhi0);

	p_mainWidget->set_size_request(256, 320);

	p_background->add(*p_mainWidget);
	add(*p_background);

	m_dialFreq->Redraw();

	Gtk::manage(p_mainWidget);
}

float LfoGUI::get_freq() { return m_dialFreq->get_value(); }
float LfoGUI::get_phi0() { return m_dialPhi0->get_value(); }

void LfoGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_waveForm)
	{
		int p_waveFormValue = (int) (*static_cast<const float*> (buffer));
		if (p_waveFormValue >= 0 && p_waveFormValue <= 5)
		{
			m_comboWaveForm->set_active((int) p_waveFormValue);
		}
	}
	else if (port == p_frequency)
	{
		m_dialFreq->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_phi0)
	{
		m_dialPhi0->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = LfoGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/lfo/gui");
