#include "../drivers/monitor.h"

void main() {
    char *video_memory = (char *)0xb8000;
    *video_memory = 'X';
    //monitor_clear();
    //monitor_write("Hello, world!");
}
