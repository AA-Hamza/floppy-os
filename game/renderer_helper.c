#include "renderer.h"
#include "renderer_helper.h"
//#include "logic.h"
#include "game.h"
#include "math.h"
#include "assets/bird_img.h"
#include "assets/foreground_img.h"
#include "assets/tunnel_img.h"
#include "assets/font_glyphs.h"

void write_background(u8int *video_buffer);
void write_foreground(u8int *video_buffer);
void write_tunnels(u8int *video_buffer, tunnel_t *tunnels);
void write_bird(u8int *video_buffer, bird_t *bird);
void write_score(u8int *video_buffer, u32int score);

void write_background(u8int *video_buffer)
{
    u16int x, y;
    for (y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            video_buffer[y*SCREEN_WIDTH+x] = BACKGROUND_COLOR;
        }
    }
}

void write_foreground(u8int *video_buffer)
{
    /* Responsible for the movement of the ground */
    static s8int foreground_x = 0;
    foreground_x -= WORLD_SPEED;
    if (foreground_x <= -FOREGROUND_SIZE) {
        foreground_x = 0;
    }

    /* Writing the moving part */
    s16int x, y;
    s16int x_index=0, y_index=0;
    for (y = FOREGROUND_START; y < FOREGROUND_START+FOREGROUND_SIZE; ++y) {
        for (x = foreground_x; x < SCREEN_WIDTH; ++x) {
            if (x >= 0) {
                video_buffer[y*SCREEN_WIDTH+x] = foreground_img[y_index][x_index];
            }
            x_index++;
            x_index %= FOREGROUND_SIZE;
        }
        x_index = 0;
        y_index++;
    }

    /* Writing the static part */
    for (y = FOREGROUND_START+FOREGROUND_SIZE; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            video_buffer[y*SCREEN_WIDTH+x] = FOREGROUND_COLOR;
        }
    }
}

void write_tunnels(u8int *video_buffer, tunnel_t *tunnels)     // Six tunnels or sections
{
    u16int i;
    for (i = 0; i < 6; ++i) {
        if (tunnels[i].height > 0) {
            s16int x, y;                        // For the buffer
            s16int index_x = 0, index_y = 0;    // For the image
            // Lower Tunnel
            for (y = SCREEN_HEIGHT-tunnels[i].height ; y < SCREEN_HEIGHT-tunnels[i].height+4; ++y) {
                for (x = tunnels[i].x-3; x < tunnels[i].x+TUNNEL_WIDTH+3; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        video_buffer[y*SCREEN_WIDTH+x] = tunnel_top[index_y][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
                index_y++;
            }
            index_x = 0;
            for (y = SCREEN_HEIGHT-tunnels[i].height+4; y < FOREGROUND_START; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        video_buffer[y*SCREEN_WIDTH+x] = tunnel_layer[0][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
            }
            
            // Upper Tunnel
            index_x = 0;
            for (y = 0; y < SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP-4; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x > 0 && x < SCREEN_WIDTH) {
                        video_buffer[y*SCREEN_WIDTH+x] = tunnel_layer[0][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
            }
            index_y = 0;
            for (y = SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP-4; y < SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP; ++y) {
                for (x = tunnels[i].x-3; x < tunnels[i].x+TUNNEL_WIDTH+3; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        video_buffer[y*SCREEN_WIDTH+x] = tunnel_top[index_y][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
                index_y++;
            }
        }
    }
}

void write_bird(u8int *video_buffer, bird_t *bird)
{
    s32int x, y;                          // For the buffer
    s32int index_y = 0, index_x = 0;      // For the image
    
    /* Some constants, Saving some computing power especially cosine & sine */
    const double bird_center_x = bird->x+bird->width/2.0f;
    const double bird_center_y = bird->y+bird->height/2.0f;
    const double rotation_cosine = cosine(bird->rotation);
    const double rotation_sine = sine(bird->rotation);


    /* Writing of the bird to the back buffer */
    for (y = bird->y; y < bird->height+bird->y; ++y) {
        for (x = bird->x; x < bird->x+bird->width; ++x) {
            if (bird_img[index_y][index_x] != 0x0) {        // If there is data to draw, 0x0 means it is transparent
                double dx = ((double) x) - bird_center_x;
                double dy = ((double) y) - bird_center_y;

                double new_x = rotation_cosine*dx - rotation_sine*dy + bird_center_x;
                double new_y = rotation_cosine*dy + rotation_sine*dx + bird_center_y;
                video_buffer[((u32int)(new_y+0.5))*SCREEN_WIDTH+((u32int)(new_x+0.5))] = bird_img[index_y][index_x];
            }
            index_x++;
        }
        index_x = 0;
        index_y++;
    }
}

// Set a pixel in the video_buffer
inline void set_pixel(u8int *video_buffer, u32int x, u32int y, u8int color)
{
    video_buffer[y*SCREEN_WIDTH+x] = color;
}

// Draw a single char to the back buffer
void write_char(u8int *video_buffer, char chr, u32int x, u32int y, u8int color)
{
    const u8int *glyph = font_glyphs[(u8int) chr];      // a pointer to the character in font_glyphs in ./assets/font_glyph.h
    u32int index_x, index_y;                            // Bit index in the glyph
    for (index_y = 0; index_y < 8; ++index_y) {
        for (index_x = 0; index_x < 8; ++index_x) {
            if (glyph[index_y] & (1 << index_x)) {
                set_pixel(video_buffer, x+index_x, y+index_y, color);
            }
        }
    }
}

// Draw a null terminated string into the back buffer
void write_str(u8int *video_buffer, const char *str, u32int x, u32int y, u8int color)
{
    char c;
    while ((c = *str++) != 0) {
        write_char(video_buffer, c, x, y, color);
        x += 8;
    }
}


void write_score(u8int *video_buffer, u32int score) {
    char buff[80];
    u32int i = 0;
    do {
        buff[i++] = '0' + score % 10 ;
    } while (score /= 10);
    buff[i] = 0;
    // Swap all before the null
    u32int j;
    for (j = 0; j < i-1; ++j) {
        char temp = buff[j];
        buff[j] = buff[i-1-j];
        buff[i-1-j] = temp;
    }
    // For the Shadow effect
    write_str(video_buffer, buff, SCORE_X+1, SCORE_Y+1, 0x0);
    write_str(video_buffer, buff, SCORE_X, SCORE_Y, SCORE_COLOR);
}
