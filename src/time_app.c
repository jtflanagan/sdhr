#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<6502.h>
#include<time.h>

volatile uint8_t* select_device_p = (uint8_t*)0xc006;
volatile uint8_t* select_rom_p = (uint8_t*)0xc007;
volatile uint8_t* read_rom_select = (uint8_t*)0xc015;
volatile uint8_t* sdhr_command_p = (uint8_t*)0xc0a0;
volatile uint8_t* sdhr_data_p = (uint8_t*)0xc0a1;
volatile uint8_t* sdhr_request_p = (uint8_t*)0xc0a2;
volatile uint8_t* sdhr_response_p = (uint8_t*)0xc0a3;

uint8_t buf[256];

void send_sdhr_request(uint8_t cmd, uint8_t* buf, uint8_t* buf_len) {
  uint8_t i;
  //uint8_t old_rom_select = *read_rom_select & 0x80;
  //printf("old select: %02x\n", old_rom_select);
  //*select_device_p = 0;
  //old_rom_select = *read_rom_select & 0x80;
  //printf("new select: %02x\n", old_rom_select);
  *sdhr_request_p = cmd;
  //if (old_rom_select) {
  //  *select_rom_p = 0;
  //} else {
  //  *select_device_p = 0;
  //}
  *buf_len = *sdhr_response_p;
  for (i = 1; i <= *buf_len; ++i) {
    buf[i-1] = *sdhr_response_p;
  }
}
uint16_t main()
{
  uint8_t buf_len;
  uint32_t epoch_sec;
  uint16_t millis;
  char timebuf[64];
  struct tm* t;
  send_sdhr_request(0, buf, &buf_len);
  epoch_sec = buf[0];
  epoch_sec += (uint32_t)buf[1] << 8;
  epoch_sec += (uint32_t)buf[2] << 16;
  epoch_sec += (uint32_t)buf[3] << 24;
  millis = buf[4];
  millis += (uint16_t)buf[5] << 8;
  t = gmtime((time_t*)&epoch_sec);
  strftime(timebuf, 64, "%Y-%m-%dT%H:%M:%S", t);
  printf("%s.%3dZ\n",timebuf,millis);
  return 0;
}

