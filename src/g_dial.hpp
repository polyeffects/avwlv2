#ifndef DIAL_H
#define DIAL_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/adjustment.h>

#include <iostream>

using namespace Gtk;

class Dial: public Gtk::DrawingArea
{
	public:
		Dial(const sigc::slot<void> toggle_slot, double Value, double Min, double Max, bool Log, double Step, int NbDigit);
		virtual ~Dial();
		bool Redraw();

		void value_changed();
		float get_value();
		void set_value(float value);

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
		virtual bool onMouseMove(GdkEventMotion* event);
		virtual bool on_button_press_event(GdkEventButton* event);
		virtual bool on_button_release_event(GdkEventButton* event);

	private:
		Gtk::Adjustment *m_adj;

		float m_mouseDelta;
		bool m_mouseDown;

		bool m_log;
		int m_rounder;

		double CalculateLogStep();
		double RoundValue(double Value);
};

#endif