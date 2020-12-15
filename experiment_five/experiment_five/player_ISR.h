#ifndef _player_MP3_H
#define _player_MP3_H

#include "board.h"

 

#define MP3_timeout_ms (12)



typedef enum {send_data_1, send_data_2, load_buf_1, load_buf_2, locate_cluster_1, locate_cluster_2, data_idle_1, data_idle_2, update_lcd_1, update_lcd_2, exit_player, init_1, init_2, init_3, init_4} play_state_t; 
// ------ Public function prototypes -------------------------------
void MP3_player_timeout_start(void);
void Play_MP3_file(uint32_t begin_cluster);
void MP3_Player_Init_Timer2(const uint16_t TICK_ms) ;




#endif