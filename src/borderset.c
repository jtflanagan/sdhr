#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<6502.h>

uint8_t* border_p = (uint8_t*)0xc034;
uint8_t* key_p = (uint8_t*)0xc000;
uint8_t* key_strobe_p = (uint8_t*)0xc010;

uint16_t main()
{
  uint8_t key;
  uint8_t strobe;
  uint8_t border_color = 0;
  
  while (1) {
    key = *key_p;
    if (key & 0x80) {
      strobe = *key_strobe_p;
      key &= 0x7f;
      switch (key) {
      case 3: // ctrl-c
	return 0;
      case 8: // left arrow
	border_color = (border_color - 1) % 16;
	*border_p = border_color;
	break;
      case 21: // right arrow
	border_color = (border_color + 1) % 16;
	*border_p = border_color;
	break;
      }
      //printf("%u\n",key);
    }
  }
  return 0;
}

