#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__


#define KEY_MENU PINF6
#define KEY_UP PINF7
#define KEY_DOWN PINF5

uint8_t get_key_press(uint8_t key_mask);
uint8_t get_key_rpt (uint8_t key_mask);
uint8_t get_key_state( uint8_t key_mask);
uint8_t get_key_short( uint8_t key_mask );
uint8_t get_key_long( uint8_t key_mask );

#endif