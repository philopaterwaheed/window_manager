#pragma once // #include only once
#include "main.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <vector>

// constatns
#define MOD Mod4Mask    // Usually the Windows  ey
#define ALT Mod1Mask    // Usually the Alt key
#define SHIFT ShiftMask // Usually the shift key
#define NUM_LAYOUTS 4
#define BORDER_WIDTH 2 // Width of the window border in pixels
#define BAR_Y 15       // where the bar font should be placed

static const unsigned int snap = 32; /* snap pixel */
static float master_size = .6;       // the intial size of the master window
// all about the bar
static bool SHOW_BAR = true; // Whether to show the bar or not
static std::string BAR_FONT = "NotoMono Nerd Font:size=10";
static double SPACIL_CHAR_FONT_SIZE =
    10;                       // font size for special characters and icons
static int BAR_HEIGHT = 20;   // Height of the bar in pixels
static int BUTTON_WIDTH = 30; // min  button width
static Layout LAYOUTS[NUM_LAYOUTS] = {
    {0, "[]=", tile_windows},
    {1, "M", monocle_windows},
    {2, "HH", grid_windows},
    {3, "|M|", center_master_windows},
};
struct Workspace {
  short index; // set to one for the first workspace
  bool show_bar = SHOW_BAR;
  int bar_height = (SHOW_BAR) ? BAR_HEIGHT : 0,
      bar_height_place_holder = (SHOW_BAR) ? 0 : BAR_HEIGHT;
  std::vector<Client> clients = std::vector<Client>(0);
  Window master = None;
  short layout = 0, layout_index_place_holder = 1;
  float master_persent = master_size, cfacts = 0;
};
// window
static unsigned long BORDER_COLOR =
    0xd3d3d3; // gray color for borders (hex value)
static unsigned long FOCUSED_BORDER_COLOR =
    0x000000;            // black color for focused window
static int GAP_SIZE = 2; // Size of the gap around windows in pixels
///

// all about workspaces
#define NUM_WORKSPACES 5 // Number of workspaces
static const char *workspaces_names[NUM_WORKSPACES] = {"_", "", "",
                                                       "", ""};
#define WORKSPACEKEYS(KEY, WORKSPACENUM)                                       \
  {MOD, KEY, switch_workspace, {.i = WORKSPACENUM}}, {                         \
    MOD | SHIFT, KEY, move_window_to_workspace, { .i = WORKSPACENUM }          \
  }
struct Monitor {
  short at = 0;
  int x, y, screen;
  int width, height;
  std::vector<Workspace> workspaces = std::vector<Workspace>(NUM_WORKSPACES);
  std::vector<Client> sticky;
  Workspace *current_workspace = NULL;
  Window bar;
  XftDraw *xft_draw;
  unsigned int index = 0;
};
///
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#4D4D4D"; // tages and xset root
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#FF44C6";
static const char col_gray4[] = "#BD93F9"; // font color
static const char col_cyan[] = "#282A36";
// commands
static const char *term[] = {"st", NULL};
static const char *bridown[] = {"sudo", "brillo", "-q", "-U", "5", NULL};
static const char *briup[] = {"sudo", "brillo", "-q", "-A", "5", NULL};
static const char *s_shot[] = {"flameshot", "gui", NULL}; // for screenshots
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      "0",   "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb", col_cyan, "-sf",     col_gray4, NULL};
//
// shortcuts
static std::vector<shortcut> shortcuts = {
    {MOD, XK_q, kill_focused_window, {0}},
    {MOD, XK_t, lunch, {.v = term}},
    {MOD, XK_Print, lunch, {.v = s_shot}},
    {MOD, XK_semicolon, lunch, {.v = dmenucmd}},
    {MOD, XK_F1, lunch, {.v = briup}},
    {MOD, XK_F2, lunch, {.v = bridown}},
    {MOD, XK_Return, toggle_fullscreen, {0}},
    {MOD, XK_s, toggle_sticky, {0}},
    {MOD, XK_b, toggle_bar, {0}},
    {MOD, XK_Right, move_focused_window_x, {.i = +20}},
    {MOD, XK_Left, move_focused_window_x, {.i = -20}},
    {MOD, XK_Down, move_focused_window_y, {.i = +20}},
    {MOD, XK_Up, move_focused_window_y, {.i = -20}},
    {MOD, XK_l, change_master_width, {.f = +.05}},
    {MOD, XK_h, change_master_width, {.f = -.05}},
    {MOD, XK_comma, focus_next_monitor, {0}},
    {MOD, XK_period, focus_previous_monitor, {0}},
    {MOD, XK_j, change_focused_window, {.i = +1}},
    {MOD, XK_k, change_focused_window, {.i = -1}},
    {MOD | SHIFT, XK_q, exit_pwm, {0}},
    {MOD | SHIFT, XK_space, toggle_floating, {0}},
    {MOD | SHIFT, XK_Right, resize_focused_window_x, {.i = +20}},
    {MOD | SHIFT, XK_Left, resize_focused_window_x, {.i = -20}},
    {MOD | SHIFT, XK_Down, resize_focused_window_y, {.i = +20}},
    {MOD | SHIFT, XK_Up, resize_focused_window_y, {.i = -20}},
    {MOD | SHIFT, XK_j, swap_window, {.i = +1}},
    {MOD | SHIFT, XK_k, swap_window, {.i = -1}},
    {MOD | SHIFT, XK_l, change_focused_window_cfact, {.f = +.05}},
    {MOD | SHIFT, XK_h, change_focused_window_cfact, {.f = -.05}},
    {MOD | SHIFT, XK_f, set_master, {0}},
    {MOD | SHIFT, XK_comma, sendto_next_monitor, {0}},
    {MOD | SHIFT, XK_period, sendto_previous_monitor, {0}},
    {MOD | ALT, XK_space, change_layout, {0}},
    {MOD | ALT, XK_m, change_layout, {.i = 1}},
    {MOD | ALT, XK_g, change_layout, {.i = 2}},
    {MOD | ALT, XK_c, change_layout, {.i = 3}},
    WORKSPACEKEYS(XK_1, 1),
    WORKSPACEKEYS(XK_2, 2),
    WORKSPACEKEYS(XK_3, 3),
    WORKSPACEKEYS(XK_4, 4),
    WORKSPACEKEYS(XK_5, 5),

};
static const Button buttons[] = {
    // event mask      button          function argument */
    {MOD, Button1, movemouse, {0}},
    {MOD, Button2, toggle_floating, {0}},
    {MOD, Button3, resizemouse, {21}},
};
