
#include "deliriumUI.h"

//------------------------------------------------------------------
// Add Widget

int addDeliriumUIWidget(deliriumUI* deliriumUI_window, deliriumUI_WidgetType widgetType, int group, float _x, float _y, float _w, float _h, char* _label, int port_number)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUI_window->deliriumUIWidgets = deliriumUIWidgets;

	deliriumUIWidgets[numberOfUIWidgets-1].type = widgetType;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;
	deliriumUIWidgets[numberOfUIWidgets-1].min = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].max = 1;
	deliriumUIWidgets[numberOfUIWidgets-1].increment = 0.01;
	deliriumUIWidgets[numberOfUIWidgets-1].toggleMode = false;
	deliriumUIWidgets[numberOfUIWidgets-1].clickTop = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].clickBottom = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].group= group;
	deliriumUIWidgets[numberOfUIWidgets-1].port_number = port_number;


	deliriumUIWidgets[numberOfUIWidgets-1].values[0] = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].values[1] = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].values[2] = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].values[3] = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].current_value = 0;


	switch (widgetType)
	{
		case deliriumUI_Fader:
			deliriumUIWidgets[numberOfUIWidgets-1].clickTop = 15;
			deliriumUIWidgets[numberOfUIWidgets-1].clickBottom = 20;
			break;

		case deliriumUI_MicroKnob:
			deliriumUIWidgets[numberOfUIWidgets-1].clickTop = 20;
			deliriumUIWidgets[numberOfUIWidgets-1].clickBottom = 20;
			break;

		case deliriumUI_Switch:
			deliriumUIWidgets[numberOfUIWidgets-1].toggleMode = true;
			break;
	}



	numberOfUIWidgets++;

	deliriumUI_window->numberOfUIWidgets = numberOfUIWidgets;

	return numberOfUIWidgets-1; // return handle number
}



//------------------------------------------------------------------
// set packing grid size

void setDeliriumUIGridSize(deliriumUI* deliriumUI_window, int _w, int _h, int _x, int _y)
{
	deliriumUI_window->originalWidth = _w;
	deliriumUI_window->originalHeight = _h;
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->gridX = _x;
	deliriumUI_window->gridY = _y;
	deliriumUI_window->widgetWidth = _w / _x;
	deliriumUI_window->widgetHeight = _h / _y;
}

//------------------------------------------------------------------
// set current window size

void setDeliriumUICurrentWindowSize(deliriumUI* deliriumUI_window, int _w, int _h)
{
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->widgetWidth = _w / deliriumUI_window->gridX;
	deliriumUI_window->widgetHeight = _h / deliriumUI_window->gridY;
}

//------------------------------------------------------------------
// Display widget
void displayDeliriumUIWidget(deliriumUI* deliriumUI_window, cairo_t* cr, int widgetNumber)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	deliriumUI_WidgetType type = deliriumUIWidgets[widgetNumber].type;

	switch (type)
	{
		case deliriumUI_Button:
			displayDiliriumUIButton(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Knob:
			displayDiliriumUIKnob(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_MicroKnob:
			displayDiliriumUIMicroKnob(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Fader:
			displayDiliriumUIFader(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Switch:
			displayDiliriumUISwitch(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_ADSR:
			displayDiliriumUIADSR(deliriumUI_window, cr, widgetNumber);
			break;
	}
}

//------------------------------------------------------------------
// Display all widgets

void displayAllDeliriumUIWidgets(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	cairo_pattern_t *linpat;

	linpat = cairo_pattern_create_linear (0,0,0,500);
	cairo_pattern_add_color_stop_rgb(linpat, 0, 0.1, 0, 0);
	cairo_pattern_add_color_stop_rgb(linpat, 0.5, 0.3, 0, 0);
	cairo_pattern_add_color_stop_rgb(linpat, 1, 0.2, 0, 0);

	/* Set surface to opaque color (r, g, b) */
	// cairo_set_source_rgb (cr, 0.2, 0.0, 0.0);
	  cairo_rectangle(cr, 0, 0, 800, 500);
	  cairo_set_source(cr, linpat);
	  cairo_fill(cr);

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		bool show_it = deliriumUI_window->group_visible[ deliriumUI_window->deliriumUIWidgets[widgetNumber].group ];
		if (show_it) displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
	}
}

//--------------------------------------------------------------------------

void setControllerDiliriumUI(LV2UI_Controller _controller, LV2UI_Write_Function _write_function)
{
	controller = _controller;
	write_function = _write_function;
}

//--------------------------------------------------------------------------

void setMinMax(deliriumUI* deliriumUI_window, int port_number, float min, float max)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;
	int widgetNumber=-1;

	for (int x=0; x<numberOfUIWidgets; x++)
	{
		if ( deliriumUIWidgets[x].port_number == port_number) widgetNumber = x;
	}

	if (widgetNumber==-1) return;

	deliriumUIWidgets[widgetNumber].min = min;
	deliriumUIWidgets[widgetNumber].max = max;
}


//--------------------------------------------------------------------------

void setValue(deliriumUI* deliriumUI_window, cairo_t* cr, int port_number, float value)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;
	int widgetNumber=-1;

	for (int x=0; x<numberOfUIWidgets; x++)
	{
		if (  deliriumUIWidgets[x].type != deliriumUI_ADSR)
		{
			if ( deliriumUIWidgets[x].port_number == port_number) widgetNumber = x;
		}

		if (  deliriumUIWidgets[x].type == deliriumUI_ADSR)
		{
			if (deliriumUIWidgets[x].port_number == port_number ||
				deliriumUIWidgets[x].port_number+1 == port_number ||
				deliriumUIWidgets[x].port_number+2 == port_number ||
				deliriumUIWidgets[x].port_number+3 == port_number)
				{
					widgetNumber = x;
				}
		}
	}

	if (widgetNumber==-1) return;

	int current_value =  port_number - deliriumUIWidgets[widgetNumber].port_number;


	float unscaled_value = value / ((deliriumUIWidgets[widgetNumber].max - deliriumUIWidgets[widgetNumber].min));

	if ( deliriumUIWidgets[widgetNumber].min < 0) unscaled_value += 0.5;

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		if (current_value == 0) unscaled_value = value;
		if (current_value == 1) unscaled_value = 1 - value;
		if (current_value == 2) unscaled_value = 1 - value;
		if (current_value == 3) unscaled_value = 1 - value;

	}

	deliriumUIWidgets[widgetNumber].values[current_value] = unscaled_value;

	deliriumUIWidgets[widgetNumber].scaled_value = value;


	displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
	write_function( controller,port_number, sizeof(float), 0, (const void*)&value);
}

//--------------------------------------------------------------------------

void decValue(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;
	int widgetNumber=deliriumUI_window->currentWidgetNumber;
	int port_number = -1;
	float value = -1;
	int current_value = 0;

	if (widgetNumber==-1) return;

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch) return;

	port_number = deliriumUIWidgets[widgetNumber].port_number;
	current_value = deliriumUIWidgets[widgetNumber].current_value;
	value = deliriumUIWidgets[widgetNumber].values[current_value] - deliriumUIWidgets[widgetNumber].increment;

	if (value < 0) value = 0;
	if (value > 1) value = 1;

	deliriumUIWidgets[widgetNumber].values[current_value] = value;
	deliriumUIWidgets[widgetNumber].scaled_value = deliriumUIWidgets[widgetNumber].min + ( deliriumUIWidgets[widgetNumber].values[current_value]
			* (deliriumUIWidgets[widgetNumber].max-deliriumUIWidgets[widgetNumber].min));

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Fader)
	{
		value = deliriumUIWidgets[widgetNumber].scaled_value;
	}

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		value = deliriumUIWidgets[widgetNumber].values[current_value];
		if (current_value > 0) port_number = deliriumUIWidgets[widgetNumber].port_number + current_value;
		if (current_value > 0) value = 1 - value;
	}

	// printf("%d - %d - %f\n", widgetNumber, port_number, value);

	write_function( controller,port_number, sizeof(float), 0, (const void*)&value);
	displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
}

//--------------------------------------------------------------------------

void incValue(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;
	int widgetNumber=deliriumUI_window->currentWidgetNumber;
	int port_number = -1;
	float value = -1;
	int current_value = 0;

	if (widgetNumber==-1) return;

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch) return;

	port_number = deliriumUIWidgets[widgetNumber].port_number;
	current_value = deliriumUIWidgets[widgetNumber].current_value;
	value = deliriumUIWidgets[widgetNumber].values[current_value] + deliriumUIWidgets[widgetNumber].increment;

	if (value < 0) value = 0;
	if (value > 1) value = 1;

	deliriumUIWidgets[widgetNumber].values[current_value] = value;
	deliriumUIWidgets[widgetNumber].scaled_value = deliriumUIWidgets[widgetNumber].min + ( deliriumUIWidgets[widgetNumber].values[current_value]
			* (deliriumUIWidgets[widgetNumber].max-deliriumUIWidgets[widgetNumber].min));

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Fader)
	{
		value = deliriumUIWidgets[widgetNumber].scaled_value;
	}

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		value = deliriumUIWidgets[widgetNumber].values[current_value];
		if (current_value > 0) port_number = deliriumUIWidgets[widgetNumber].port_number + current_value;
		if (current_value > 0) value = 1 - value;
	}

	// printf("%d - %d - %f\n", widgetNumber, port_number, value);

	write_function( controller,port_number, sizeof(float), 0, (const void*)&value);
	displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
}

//--------------------------------------------------------------------------

void zeroValue(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;
	int widgetNumber=deliriumUI_window->currentWidgetNumber;
	int port_number = -1;
	float value = -1;
	int current_value = 0;

	if (widgetNumber==-1) return;

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch) return;

	port_number = deliriumUIWidgets[widgetNumber].port_number;
	current_value = deliriumUIWidgets[widgetNumber].current_value;
	value = (0 - deliriumUIWidgets[widgetNumber].min) / ((deliriumUIWidgets[widgetNumber].max - deliriumUIWidgets[widgetNumber].min));

	if (value < 0) value = 0;
	if (value > 1) value = 1;

	deliriumUIWidgets[widgetNumber].values[current_value] = value;
	deliriumUIWidgets[widgetNumber].scaled_value = deliriumUIWidgets[widgetNumber].min + ( deliriumUIWidgets[widgetNumber].values[current_value]
			* (deliriumUIWidgets[widgetNumber].max-deliriumUIWidgets[widgetNumber].min));

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Fader)
	{
		value = deliriumUIWidgets[widgetNumber].scaled_value;
	}

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		value = deliriumUIWidgets[widgetNumber].values[current_value];
		if (current_value > 0) port_number = deliriumUIWidgets[widgetNumber].port_number + current_value;
		if (current_value > 0) value = 1 - value;
	}

	displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
	write_function( controller,port_number, sizeof(float), 0, (const void*)&value);
}
//--------------------------------------------------------------------------

void setValueFromMousePosition(deliriumUI* deliriumUI_window, int widgetNumber, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
	float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
	float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
	float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

	float clickTop = h * (deliriumUIWidgets[widgetNumber].clickTop/100);
	float clickBottom = h * (deliriumUIWidgets[widgetNumber].clickBottom/100);

	y += clickTop;
	h -= (clickTop+clickBottom);

	float value = (_y - y) / h;


	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		value = (_y - y) / ((h/2) + (h/6));
	}


	 value = 1-value;

	if (value < 0) value = 0;
	if (value > 1) value = 1;

	int port_number = deliriumUIWidgets[widgetNumber].port_number;
	setValueDiliriumUIADSR(deliriumUI_window, widgetNumber, value );

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Fader)
	{
		deliriumUIWidgets[widgetNumber].scaled_value = deliriumUIWidgets[widgetNumber].min + ( deliriumUIWidgets[widgetNumber].values[0]
				* (deliriumUIWidgets[widgetNumber].max-deliriumUIWidgets[widgetNumber].min));
		value = deliriumUIWidgets[widgetNumber].scaled_value;
	}

	if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
	{
		port_number += deliriumUIWidgets[widgetNumber].current_value;
	}

	deliriumUIWidgets[widgetNumber].hover = true;
	if (controller,port_number > -1)
		write_function( controller,port_number, sizeof(float), 0, (const void*)&value);
}

//------------------------------------------------------------------
// check if mouse is hovering over widget
void isMouseOverDeliriumUIWidget(deliriumUI* deliriumUI_window, cairo_t* cr, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUI_window->currentWidgetNumber = -1;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int group = deliriumUIWidgets[widgetNumber].group;

		if (deliriumUI_window->group_visible[group])
		{

			float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
			float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
			float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
			float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

			if (deliriumUIWidgets[widgetNumber].pressed && deliriumUIWidgets[widgetNumber].type!=deliriumUI_Switch)
			{

				setValueFromMousePosition(deliriumUI_window, widgetNumber, _x, _y);
				displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
			}

			if (!deliriumUI_window->mouseButton[1])
			{
				if (_x>=x && _y>=y && _x<=x+w && _y<=y+h)
				{
					deliriumUIWidgets[widgetNumber].hover = true;
					deliriumUI_window->currentWidgetNumber = widgetNumber;


					if (deliriumUIWidgets[widgetNumber].type == deliriumUI_ADSR)
					{

						int current_value = ((_x-(int)x) / (w/4));
						deliriumUIWidgets[widgetNumber].current_value = current_value;
					}
				}
				else
				{
					deliriumUIWidgets[widgetNumber].hover = false;
				}
			}
		}
	}
}


//------------------------------------------------------------------
// check if widget has been clicked by mouse button

void hasMouseClickedDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;



	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		bool show_it = deliriumUI_window->group_visible[ deliriumUI_window->deliriumUIWidgets[widgetNumber].group ];

		if (show_it)
		{

			float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
			float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
			float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
			float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

			w -= 2;
			h -= 2;

			if (!deliriumUIWidgets[widgetNumber].toggleMode)
			{
				if (_x>=x && _y>=y && _x<=x+w && _y<=y+h)
				{
					deliriumUIWidgets[widgetNumber].pressed = true;

					if ( deliriumUIWidgets[widgetNumber]. port_number < 0)
					{

						for (int x=1; x<5; x++)
						{
							if ( x!= -deliriumUIWidgets[widgetNumber]. port_number)
								deliriumUI_window->group_visible[x] = false;
							else
								deliriumUI_window->group_visible[x] = true;
						}
						return;
					}

					if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch)
					{
						deliriumUIWidgets[widgetNumber].values[0] = deliriumUIWidgets[widgetNumber].pressed;

						write_function( controller,deliriumUIWidgets[widgetNumber]. port_number, sizeof(float), 0, (const void*)&deliriumUIWidgets[widgetNumber].values[0]);

					}
					setValueFromMousePosition(deliriumUI_window, widgetNumber, _x, _y);

				}
				else
				{
					deliriumUIWidgets[widgetNumber].pressed = false;
					if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch)
					{
						deliriumUIWidgets[widgetNumber].values[0] = deliriumUIWidgets[widgetNumber].pressed;

						write_function( controller,deliriumUIWidgets[widgetNumber]. port_number, sizeof(float), 0, (const void*)&deliriumUIWidgets[widgetNumber].values[0]);

					}
				}
			}
			else
			{
				if (_x>=x && _y>=y && _x<=x+w && _y<=y+h)
				{
					deliriumUIWidgets[widgetNumber].pressed = 1-deliriumUIWidgets[widgetNumber].pressed;
					if ( deliriumUIWidgets[widgetNumber].type == deliriumUI_Switch)
					{
						deliriumUIWidgets[widgetNumber].values[0] = deliriumUIWidgets[widgetNumber].pressed;

						write_function( controller,deliriumUIWidgets[widgetNumber]. port_number, sizeof(float), 0, (const void*)&deliriumUIWidgets[widgetNumber].values[0]);

					}

				}
			}
		}
	}
}

//------------------------------------------------------------------
// Return number of widgets

int getNumberOfWidgets(deliriumUI* deliriumUI_window)
{
	return deliriumUI_window->numberOfUIWidgets;
}

//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI(deliriumUI* deliriumUI_window)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	free(deliriumUIWidgets);
}





