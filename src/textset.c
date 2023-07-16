#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<6502.h>

uint8_t* text_p = (uint8_t*)0xc022;
uint8_t* key_p = (uint8_t*)0xc000;
uint8_t* key_strobe_p = (uint8_t*)0xc010;

uint16_t main()
{
  uint8_t key;
  uint8_t strobe;
  uint8_t text_color = 0;
  
  while (1) {
    key = *key_p;
    if (key & 0x80) {
      strobe = *key_strobe_p;
      key &= 0x7f;
      switch (key) {
      case 3: // ctrl-c
	return 0;
      case 8: // left arrow
	text_color = (text_color - 1) % 16;
        if (text_color == 0) {
          text_color = 15;
        }
	*text_p = text_color;
	break;
      case 21: // right arrow
	text_color = (text_color + 1) % 16;
        if (text_color == 0) {
          text_color = 1;
        }
	*text_p = text_color;
	break;
      }
      //printf("%u\n",key);
    }
  }
  return 0;
}

