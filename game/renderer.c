#include "../drivers/monitor.h"
#include "renderer.h"
#include "logic.h"
#include "game.h"
//#include "math.h"
#include "renderer_helper.h"
//#include "assets/bird_img.h"
//#include "assets/foreground_img.h"
//#include "assets/tunnel_img.h"
//#include "assets/font_glyphs.h"


// We render to this buffer, then copy when we are done (screen tearing & other image artifacts)
static u8int *back_video_buffer = (u8int *)(BACK_VIDEO_BUFFER_ADDRESS);

void render_to_main_screen() {
    draw_screen(back_video_buffer);
}

// Write the current scene to the back buffer
void render_scene(u8int *finised_rendering, bird_t *bird, tunnel_t *tunnels, u32int score)
{
    // This pointer is used to tell the caller function that this scene hasn't finished
    // Rendering yet. Wait until it finishes.
    *finised_rendering = 0;
    write_background(back_video_buffer);
    write_foreground(back_video_buffer);
    write_tunnels(back_video_buffer, tunnels);
    write_bird(back_video_buffer, bird);
    write_score(back_video_buffer, score);

    render_to_main_screen();
    *finised_rendering = 1;
}

void render_overlay_text(u32int x, u32int y, const char *text, u8int color, u8int shadow_color)
{
    // Write the shadow
    write_str(back_video_buffer, text, x+SHADOW_OFFSET, y+SHADOW_OFFSET, shadow_color);

    // Write the text
    write_str(back_video_buffer, text, x, y, color);

    render_to_main_screen();
}
