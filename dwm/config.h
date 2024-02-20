/* See LICENSE file for copyright and license details. */

#define TERMINAL         "st"
#define EDITOR           "nvim"
#define BROWSER          "firefox"
#define SCREENSHOTS_PATH "/home/naki/pic/screenshots/"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int cornerrad = 0;
static const unsigned int gappih    = 5;
static const unsigned int gappiv    = 5;
static const unsigned int gappoh    = 5;
static const unsigned int gappov    = 5;
static const int smartgaps          = 0;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 5;
static const int sidepad            = 5;
static const char *fonts[]          = { "monospace:size=10", "fontawesome:size=12", "NotoColorEmoji:size=12" };
static const char dmenufont[]       = "monospace:size=10";

#include "frappe.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg,    col_bg      },
	[SchemeSel]  = { col_fg, col_actbg, col_actwin  }
};


/* tagging */
static const char *tags[] = { "", "", "", "", "一", "二", "三", "四", "五" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.70; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY    Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]       = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_actbg, "-sf", col_fg, NULL };

static const char *termcmd[]   = { TERMINAL, NULL };
static const char *editorcmd[] = { TERMINAL, EDITOR, NULL };
static const char *browsercmd[]  = { BROWSER, NULL };
static const char *discordcmd[]  = { "discord", NULL };

static const char *volupcmd[]    = { "amixer", "-D", "pulse", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[]  = { "amixer", "-D", "pulse", "sset", "Master", "5%-", "unmute", NULL };

static const char *scrotcmd[]    = { "scrot", "-s", "-f", SCREENSHOTS_PATH "/%F_%T_$wx$h.png", "-e", "xclip -selection clipboard -target image/png -i $f", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

    /* Utilities */
	{ 0,                            XK_Print,  spawn,          {.v = scrotcmd } }, /* print screen */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },

	{ MODKEY,                       0x5b,      spawn,          {.v = voldowncmd  } }, /* | Multimedia keys */
	{ MODKEY,                       0x5d,      spawn,          {.v = volupcmd    } }, /* /                 */
	{ 0,                            0x1008ff11,spawn,          {.v = voldowncmd  } }, /* | Wheel on my headphones */
	{ 0,                            0x1008ff13,spawn,          {.v = volupcmd    } }, /* /                        */

    /* Apps */
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = discordcmd  } }, /* I use discord, btw */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = browsercmd  } }, /* Browser */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd     } }, /* | Terminal and editor names defined in */
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = editorcmd   } }, /* / TERMINAL and EDITOR                  */

    /* Other */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_m,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_i,  setlayout,      {0} },
	{ MODKEY,                       XK_w,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    /* gaps */
    { MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

