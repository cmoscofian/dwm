/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "Unifont:size=15", "monospace:size=10" };

/* trackball definitions */
static const unsigned int trackball_bottom_left     = 1;
static const unsigned int trackball_upper_left      = 2;
static const unsigned int trackball_bottom_right    = 3;
static const unsigned int trackball_upper_right     = 8;

/* nibble color scheme */
static const char black[]           = "#000000";
static const char white[]           = "#ffffff";
static const char dark_red[]        = "#800000";
static const char dark_green[]      = "#008000";
static const char dark_yellow[]     = "#808000";
static const char dark_blue[]       = "#000080";
static const char dark_fuchsia[]    = "#800080";
static const char dark_cyan[]       = "#008080";
static const char dark_grey[]       = "#404040";
static const char light_red[]       = "#ff0000";
static const char light_green[]     = "#00ff00";
static const char light_yellow[]    = "#ffff00";
static const char light_blue[]      = "#0000ff";
static const char light_fuchsia[]   = "#ff00ff";
static const char light_cyan[]      = "#00ffff";
static const char light_grey[]      = "#c0c0c0";


static const char *colors[][3]      = {
	/*               fg             bg          border     */
	[SchemeNorm] = { light_grey,    black,      light_grey },
	[SchemeSel]  = { dark_blue,     light_grey, light_cyan },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;     /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;       /* number of clients in master area */
static const int resizehints = 1;       /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "<F>",      NULL },    /* no layout function means floating behavior */
	{ "(X)",      monocle },
};

/* key definitions */
#define MOD_ALT_KEY Mod1Mask
#define MOD_WIN_KEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ MOD_ALT_KEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MOD_ALT_KEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MOD_ALT_KEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MOD_ALT_KEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, NULL };
static const char *passcmd[]    = { "passmenu", NULL };
static const char *slockcmd[]   = { "slock", NULL };
static const char *termcmd[]    = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                         key             function        argument */
	{ MOD_ALT_KEY,                      XK_p,           spawn,          {.v = dmenucmd } },
	{ MOD_ALT_KEY|ShiftMask,            XK_p,           spawn,          {.v = passcmd } },
	{ MOD_ALT_KEY|ShiftMask,            XK_l,           spawn,          {.v = slockcmd } },
	{ MOD_ALT_KEY|ShiftMask,            XK_Return,      spawn,          {.v = termcmd } },
	{ MOD_ALT_KEY,                      XK_b,           togglebar,      {0} },
	{ MOD_ALT_KEY,                      XK_j,           focusstack,     {.i = +1 } },
	{ MOD_ALT_KEY,                      XK_k,           focusstack,     {.i = -1 } },
	{ MOD_ALT_KEY,                      XK_h,           setmfact,       {.f = -0.05} },
	{ MOD_ALT_KEY,                      XK_l,           setmfact,       {.f = +0.05} },
	{ MOD_ALT_KEY,                      XK_i,           incnmaster,     {.i = +1 } },
	{ MOD_ALT_KEY,                      XK_d,           incnmaster,     {.i = -1 } },
	{ MOD_ALT_KEY,                      XK_Return,      zoom,           {0} },
	{ MOD_ALT_KEY,                      XK_Tab,         view,           {0} },
	{ MOD_ALT_KEY,                      XK_q,           killclient,     {0} },
	{ MOD_ALT_KEY|ShiftMask,            XK_q,           quit,           {0} },
	{ MOD_ALT_KEY,                      XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MOD_ALT_KEY,                      XK_f,           setlayout,      {.v = &layouts[1]} },
	{ MOD_ALT_KEY,                      XK_m,           setlayout,      {.v = &layouts[2]} },
	{ MOD_ALT_KEY,                      XK_space,       setlayout,      {0} },
	{ MOD_ALT_KEY|ShiftMask,            XK_space,       togglefloating, {0} },
	{ MOD_ALT_KEY,                      XK_0,           view,           {.ui = ~0 } },
	{ MOD_ALT_KEY|ShiftMask,            XK_0,           tag,            {.ui = ~0 } },
	{ MOD_ALT_KEY,                      XK_comma,       focusmon,       {.i = -1 } },
	{ MOD_ALT_KEY,                      XK_period,      focusmon,       {.i = +1 } },
	{ MOD_ALT_KEY|ShiftMask,            XK_comma,       tagmon,         {.i = -1 } },
	{ MOD_ALT_KEY|ShiftMask,            XK_period,      tagmon,         {.i = +1 } },
	{ MOD_ALT_KEY,                      XK_backslash,   togglegaps,     {0} },
	{ MOD_ALT_KEY|ShiftMask,            XK_backslash,   restoregaps,    {0} },
	{ MOD_ALT_KEY,                      XK_Up,          incrgaps,      {.i = +1 } },
	{ MOD_ALT_KEY|ShiftMask,            XK_Up,          incrgaps,      {.i = +10 } },
	{ MOD_ALT_KEY,                      XK_Down,        incrgaps,      {.i = -1 } },
	{ MOD_ALT_KEY|ShiftMask,            XK_Down,        incrgaps,      {.i = -10 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button                      function        argument */
	{ ClkLtSymbol,          0,              trackball_bottom_left,      setlayout,      {0} },
	{ ClkLtSymbol,          0,              trackball_bottom_right,     setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              trackball_upper_left,       zoom,           {0} },
	{ ClkStatusText,        0,              trackball_upper_left,       spawn,          {.v = termcmd } },
	{ ClkClientWin,         MOD_ALT_KEY,    trackball_bottom_left,      movemouse,      {0} },
	{ ClkClientWin,         MOD_ALT_KEY,    trackball_upper_left,       togglefloating, {0} },
	{ ClkClientWin,         MOD_ALT_KEY,    trackball_bottom_right,     resizemouse,    {0} },
	{ ClkTagBar,            0,              trackball_bottom_left,      view,           {0} },
	{ ClkTagBar,            0,              trackball_bottom_right,     toggleview,     {0} },
	{ ClkTagBar,            MOD_ALT_KEY,    trackball_bottom_left,      tag,            {0} },
	{ ClkTagBar,            MOD_ALT_KEY,    trackball_bottom_right,     toggletag,      {0} },
};

