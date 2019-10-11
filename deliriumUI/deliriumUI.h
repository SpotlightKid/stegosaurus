#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cairo/cairo.h>
#include "pugl/pugl.h"

// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"


// public Lv2 communication stuff
LV2UI_Controller controller;
LV2UI_Write_Function write_function;

typedef enum {
    deliriumUI_Button=1,
    deliriumUI_Knob=2,
    deliriumUI_MicroKnob=3,
    deliriumUI_Fader=4,
    deliriumUI_Switch=5,
    deliriumUI_ADSR=6
} deliriumUI_WidgetType;

typedef struct {
    deliriumUI_WidgetType	type;
    float	x;
    float	y;
    float	w;
    float	h;
    bool	pressed;
    bool	hover;
    bool	toggleMode;
    const char* label;
    float values[4];
    int current_value;
    float scaled_value;
    float increment;
    float	min;
    float	max;
    float clickTop;
    float clickBottom;
    int group;
    int port_number;
} deliriumUIWidget;

typedef struct {
    int originalWidth;
    int originalHeight;
    int currentWidth;
    int currentHeight;
    int gridX;
    int gridY;
    int widgetWidth;
    int widgetHeight;
    deliriumUIWidget* deliriumUIWidgets;
    int numberOfUIWidgets;
    int currentWidgetNumber;
    int mouseButton[16];
    bool group_visible[32];
} deliriumUI;


void cleanUpDeliriumUI(deliriumUI*);
void setDeliriumUIGridSize(deliriumUI*, int, int, int, int);
void setDeliriumUICurrentWindowSize(deliriumUI*, int, int);
int addDeliriumUIWidget(deliriumUI*, deliriumUI_WidgetType, int, float, float, float, float, char*, int);
void displayDeliriumUIWidget(deliriumUI*, cairo_t*, int);
void displayAllDeliriumUIWidgets(deliriumUI*, cairo_t*);
void isMouseOverDeliriumUIWidget(deliriumUI*, cairo_t*, int, int);
void setValueFromMousePosition(deliriumUI*, int, int, int);
void hasMouseClickedDeliriumUIWidget(deliriumUI*, int, int);
void setValue(deliriumUI*, cairo_t*, int, float);
void decValue(deliriumUI*, cairo_t*);
void zeroValue(deliriumUI*, cairo_t*);
void incValue(deliriumUI*, cairo_t*);
void setMinMax(deliriumUI*,   int, float, float);

void displayDeliriumUIButton(deliriumUI*, cairo_t*, int);
void displayDeliriumUIKnob(deliriumUI*, cairo_t*, int);
void displayDeliriumUIMicroKnob(deliriumUI*, cairo_t*, int);
void displayDeliriumUIFader(deliriumUI*, cairo_t*, int);
void displayDeliriumUISwitch(deliriumUI*, cairo_t*, int);
void displayDeliriumUIADSR(deliriumUI*, cairo_t*, int);

int getNumberOfWidgets(deliriumUI*);

void setValueDeliriumUIFader(deliriumUI*, int, float);
void setValueDeliriumUISwitch(deliriumUI*, int, float);
void setValueDeliriumUIADSR(deliriumUI*, int, float);

void setControllerDeliriumUI(LV2UI_Controller, LV2UI_Write_Function);

/*
static void roundedBox(cairo_t* cr, double x, double y, double w, double h) {
    static const double radius  = 10;
    static const double degrees = 3.14159265 / 180.0;

    cairo_new_sub_path(cr);
    cairo_arc(cr,
              x + w - radius,
              y + radius,
              radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr,
              x + w - radius, y + h - radius,
              radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr,
              x + radius, y + h - radius,
              radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr,
              x + radius, y + radius,
              radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);
}
*/
