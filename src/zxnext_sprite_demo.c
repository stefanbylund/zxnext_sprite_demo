/*******************************************************************************
 * Stefan Bylund 2017
 *
 * A simple sprite demo program for Sinclair ZX Spectrum Next.
 ******************************************************************************/

#include <arch/zx.h>
#include <input.h>
#include <z80.h>
#include <stdint.h>
#include <stdbool.h>

#include "zxnext_registers.h"
#include "zxnext_sprite.h"

#pragma output CRT_ORG_CODE = 32768
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma output CLIB_STDIO_HEAP_SIZE = 0
#pragma output CLIB_FOPEN_MAX = -1

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

static void init_hardware(void);

static void create_background(void);

static void create_sprites(void);

static void update_sprites(void);

static void clear_background(void);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

typedef struct sprite_info {
    int x;  // X coordinate in pixels
    int y;  // Y coordinate in pixels
    int dx; // Horizontal displacement in pixels
    int dy; // Vertical displacement in pixels
} sprite_info_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

static const uint8_t sprite_pattern[] =
{
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xFB, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xF5, 0xF5, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xF5, 0xA8, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFF, 0xFB, 0xA8, 0x44, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0x04, 0x04, 0xFF, 0xFB, 0xA8, 0x44, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0xA8, 0x44, 0x44, 0xFB, 0xFF, 0x04, 0xE3, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0x44, 0x44, 0xFB, 0xFF, 0x04, 0x4D, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0x44, 0x44, 0x44, 0xFA, 0x4D, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0xFF, 0xF5, 0x44, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0x44, 0xF5, 0xA8, 0x04, 0xE3, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFA, 0x44, 0x04, 0xA8, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x4D, 0x4D, 0x04, 0xE3, 0x04, 0xF5, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x04, 0xE3, 0xE3, 0xE3, 0x04, 0xFA, 0x04,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x04
};

static sprite_info_t sprite = {120, 88, 1, 1};

/*******************************************************************************
 * Functions
 ******************************************************************************/

static void init_hardware(void)
{
    uint8_t peripheral_2_settings;

    // Put Z80 in 7 MHz turbo mode.

    z80_outp(REGISTER_NUMBER_PORT, PERIPHERAL_2_REGISTER);
    peripheral_2_settings = z80_inp(REGISTER_VALUE_PORT);

    z80_outp(REGISTER_NUMBER_PORT, PERIPHERAL_2_REGISTER);
    z80_outp(REGISTER_VALUE_PORT, 0x80 | peripheral_2_settings);

    z80_outp(REGISTER_NUMBER_PORT, TURBO_MODE_REGISTER);
    z80_outp(REGISTER_VALUE_PORT, 1);
}

static void create_background(void)
{
    zx_border(INK_YELLOW);
    zx_cls(BRIGHT | INK_BLACK | PAPER_WHITE);
}

static void create_sprites(void)
{
    set_sprite_slot(0);
    set_sprite_pattern(sprite_pattern);

    set_sprite_slot(0);
    set_sprite_attributes_ext(0, sprite.x, sprite.y, 0, 0, true);
}

static void update_sprites(void)
{
    // Calculate next position of sprite.
    sprite.x += sprite.dx;
    sprite.y += sprite.dy;

    // If sprite is outside the screen then clip its position and change direction.
    if (sprite.x <= 0)
    {
        sprite.x = 0;
        sprite.dx = -sprite.dx;
    }
    else if (sprite.x >= 239)
    {
        sprite.x = 239;
        sprite.dx = -sprite.dx;
    }
    if (sprite.y <= 0)
    {
        sprite.y = 0;
        sprite.dy = -sprite.dy;
    }
    else if (sprite.y >= 175)
    {
        sprite.y = 175;
        sprite.dy = -sprite.dy;
    }

    // Update sprite position.
    set_sprite_slot(0);
    set_sprite_attributes_ext(0, sprite.x, sprite.y, 0, 0, true);
}

static void clear_background(void)
{
    zx_border(INK_WHITE);
    zx_cls(INK_BLACK | PAPER_WHITE);
}

int main(void)
{
    init_hardware();
    create_background();
    create_sprites();
    set_sprite_system(true, false);

    while (true)
    {
        if (in_inkey() != 0)
        {
            break;
        }

        // Wait a short while between each movement of the sprite.
        z80_delay_ms(20);

        update_sprites();
    }

    set_sprite_system(false, false);
    clear_background();
    return 0;
}
