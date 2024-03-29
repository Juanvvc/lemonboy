#include <fcntl.h>
#include <linux/fb.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include "polluxregs.h"
#include "uppermem.h"
#include "time.h"

#ifndef __GP2X_LIB_H__
#define __GP2X_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define WIZ_A		GP2X_A
#define WIZ_B		GP2X_B
#define WIZ_X		GP2X_X
#define WIZ_Y		GP2X_Y
#define WIZ_L		GP2X_L
#define WIZ_R		GP2X_R
#define WIZ_MENU	GP2X_START
#define WIZ_SELECT	GP2X_SELECT
#define WIZ_LEFT	GP2X_LEFT
#define WIZ_RIGHT	GP2X_RIGHT
#define WIZ_UP		GP2X_UP
#define WIZ_DOWN	GP2X_DOWN
#define WIZ_VOLUP	GP2X_VOL_UP
#define WIZ_VOLDOWN	GP2X_VOL_DOWN
#define GP2X_NOBUTTON	99

#define wiz_init		gp2x_init
#define wiz_deinit		gp2x_deinit
#define wiz_set_clock		gp2x_set_clock
#define wiz_joystick_read	gp2x_joystick_read
#define wiz_video_flip		gp2x_video_flip
#define wiz_video_flip_single	gp2x_video_flip_single
#define wiz_video_setpalette	gp2x_video_setpalette
#define wiz_sound_rate		gp2x_sound_rate
#define wiz_sound_stereo	gp2x_sound_stereo
#define wiz_clock		gp2x_clock
#define wiz_timer_delay		gp2x_timer_delay
#define wiz_sound_play		gp2x_sound_play
#define wiz_joystick_press	gp2x_joystick_press
#define wiz_sound_volume	gp2x_sound_volume
#define wiz_sound_thread_mute	gp2x_sound_thread_mute
#define wiz_sound_thread_start	gp2x_sound_thread_start
#define wiz_sound_thread_stop	gp2x_sound_thread_stop
#define wiz_sound_set_rate	gp2x_sound_set_rate
#define wiz_sound_set_stereo	gp2x_sound_set_stereo
#define wiz_timer_read		gp2x_timer_read
#define wiz_timer_profile	gp2x_timer_profile
#define wiz_set_video_mode	gp2x_set_video_mode
#define wiz_printf		gp2x_printf
#define wiz_printf_init		gp2x_printf_init
#define wiz_gamelist_text_out		gp2x_gamelist_text_out
#define wiz_gamelist_text_out_fmt	gp2x_gamelist_text_out_fmt
#define wiz_video_wait_vsync		gp2x_video_wait_vsync 

extern unsigned char *fb0_8bit, *fb1_8bit; /* current buffers (8 bit) */
extern unsigned short *fb0_16bit, *fb1_16bit; /* current buffers (16 bit) */
extern void *fbfake0, *fbfake1;

#define wiz_video_color8(C,R,G,B) (wiz_video_RGB_palette[(C)].color=((R)>>3)<<11|((G)>>2)<<5|((B)>>3),wiz_video_RGB_palette[(C)].dirty=1)
#define wiz_video_color16(R,G,B)	(((((R)&0xF8)<<8)|(((G)&0xFC)<<3)|(((B)&0xF8)>>3)))
#define wiz_video_getr16(C) (((C)>>8)&0xF8)
#define wiz_video_getg16(C) (((C)>>3)&0xFC)
#define wiz_video_getb16(C) (((C)<<3)&0xF8)

extern int wiz_init(int bpp, int rate, int bits, int stereo);
extern void wiz_deinit(void);

#define BIT(number) (1<<(number))
enum {
	WIZ_A = BIT(20),
	WIZ_B = BIT(21),
	WIZ_X = BIT(22),
	WIZ_Y = BIT(23),
	WIZ_L = BIT(7),
	WIZ_R = BIT(6),
	WIZ_MENU = BIT(9),
	WIZ_SELECT = BIT(8),
	WIZ_LEFT = BIT(16),
	WIZ_RIGHT = BIT(17),
	WIZ_UP = BIT(18),
	WIZ_DOWN = BIT(19),
	WIZ_VOLUP = BIT(10),
	WIZ_VOLDOWN = BIT(11)
};

extern void wiz_set_clock(int speed); /* 200, 533, 650 */

extern unsigned int wiz_joystick_read(int n);
extern void wiz_video_flip(void);
extern void wiz_video_flip_single(void);

typedef struct wiz_palette { unsigned short color; unsigned short dirty; } wiz_palette;
extern wiz_palette wiz_video_RGB_palette[256];
extern void wiz_video_setpalette(void);

extern int wiz_sound_rate;
extern int wiz_sound_stereo;
extern int wiz_clock;

extern void wiz_timer_delay(clock_t ticks);
extern void wiz_sound_play(void *buff, int len);
extern unsigned int wiz_joystick_press (int n);
extern void wiz_sound_volume(int left, int right);
extern void wiz_sound_thread_mute(void);
extern void wiz_sound_thread_start(void);
extern void wiz_sound_thread_stop(void);
extern void wiz_sound_set_rate(int rate);
extern void wiz_sound_set_stereo(int stereo);
extern clock_t wiz_timer_read(void);
extern void wiz_timer_profile(void);

extern void wiz_set_video_mode(int bpp,int width,int height);

extern void wiz_printf(char* fmt, ...);
extern void wiz_printf_init(void);
extern void wiz_gamelist_text_out(int x, int y, char *eltexto);
extern void wiz_gamelist_text_out_fmt(int x, int y, char* fmt, ...);

extern void wiz_video_wait_vsync(void);

extern void wiz_ptimer_init(void);
extern unsigned int wiz_ptimer_get_ticks_ms(void);
extern void wiz_ptimer_delay_ms( unsigned int delay );
extern void wiz_ptimer_cleanup(void);

#define MMUHACK 1

#ifdef MMUHACK
#include "warm.h"
#endif
#include "pollux_set.h"
#include "sys_cacheflush.h"

#ifdef __cplusplus
} /* End of extern "C" */
#endif

#endif
