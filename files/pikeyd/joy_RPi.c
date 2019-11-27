


/**** joy_RPi.c ****************************/
/* M. Moller   2013-01-16                  */
/*   Universal RPi GPIO keyboard daemon    */
/*******************************************/

/*
   Copyright (C) 2013 Michael Moller.
   This file is part of the Universal Raspberry Pi GPIO keyboard daemon.

   This is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  
*/

/*******************************************/
/* based on the xmame driver by
/* Jason Birch   2012-11-21   V1.00        */
/* Joystick control for Raspberry Pi GPIO. */
/*******************************************/

//#include "xmame.h"
//#include "devices.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "joy_RPi.h"
#include "config.h"

#include <bcm2835.h>
#include "gpio_joystick.h"





#if defined RPI_JOYSTICK

#define GPIO_PERI_BASE        0x20000000
#define GPIO_BASE             (GPIO_PERI_BASE + 0x200000)
#define BLOCK_SIZE            (4 * 1024)
#define PAGE_SIZE             (4 * 1024)
#define GPIO_ADDR_OFFSET      13
#define BUFF_SIZE             128
#define JOY_BUTTONS           32
#define JOY_AXES              2
#define JOY_DIRS              2

#define BOUNCE_TIME 4

// Raspberry Pi V1 GPIO
//static int GPIO_Pin[] = { 0, 1, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 21, 22, 23, 24, 25 };
// Raspberry Pi V2 GPIO
//static int GPIO_Pin[] = { 2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27 };
//MameBox pins
//static int GPIO_Pin[] = { 4, 17, 18, 22, 23, 24, 10, 25, 11, 8, 7 };
static char GPIO_Filename[JOY_BUTTONS][BUFF_SIZE];

static int GpioFile;
static char* GpioMemory;
static char* GpioMemoryMap;
volatile unsigned* GPIO;
static int AllMask;
static int lastGpio=0;
static int xGpio=0;
static int bounceCount=0;

struct joydata_struct
{
  int fd;
  int num_axes;
  int num_buttons;
  int button_mask;
  int change_mask;
  int buttons[JOY_BUTTONS];
  int change[JOY_BUTTONS];
} joy_data[1];




int joy_RPi_init(void)
{
  FILE* File;
  int Index;
  char Buffer[BUFF_SIZE];
  int n = gpios_used();

  
  // CM
  // alten joy init code geloescht
  //



  printf("bcm open\n");
  if (!bcm2835_init())
    {
      printf("bcm open error\n");
      exit(-1);
    }
  // Set the pins to be an output
  bcm2835_gpio_fsel(CLK, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(PL, BCM2835_GPIO_FSEL_OUTP);
  // Set the pin to be an input
  bcm2835_gpio_fsel(DIN, BCM2835_GPIO_FSEL_INPT);
  
  
  /* Set the file descriptor to a dummy value. */
  joy_data[0].fd = 1;
  joy_data[0].num_buttons = n;
  joy_data[0].num_axes = 0;
  joy_data[0].button_mask=0;

  bounceCount=0;

  printf("Joystick init OK.\n");

  return 0;
}

void joy_RPi_exit(void)
{
  printf("bcm close\n");
  bcm2835_close();
}



#define NRHC165BITS 24
#define WAIT1 for(waitcount=20;waitcount--;waitcount>1 );

volatile unsigned long waitcount;

long unsigned int Read_Port_HC165()
{
  long unsigned int val=0xffffffff;
  int i;

  bcm2835_gpio_write(CLK, HIGH);
  WAIT1
  bcm2835_gpio_write(PL, LOW);
  WAIT1
  bcm2835_gpio_write(PL, HIGH);

  for(i=0;i<NRHC165BITS;i++)
    {
      val= val<<1 ;
      WAIT1
      uint8_t value = bcm2835_gpio_lev(DIN);
      val=val|value;
      bcm2835_gpio_write(CLK, LOW);
      WAIT1
      bcm2835_gpio_write(CLK, HIGH);
    }

  return val;
}



#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


void joy_RPi_poll(void)
{
  FILE* File;
  int Joystick;
  int Index;
  int Char;
  int newGpio;
  int iomask;

  Joystick = 0;

#if 0  
  if(joy_data[Joystick].fd) {			
    if (!GPIO) { /* fallback I/O? don't use - very slow. */
      for (Index = 0; Index < joy_data[Joystick].num_buttons; ++Index){
	if( (File = fopen(GPIO_Filename[Index], "r")) ){
	  Char = fgetc(File);
	  fclose(File);

	  iomask = (1 << gpio_pin(Index));
	  if (Char == '0'){
	    newGpio |= iomask;
	    //joy_data[Joystick].buttons[Index] = 1;
	  }
	  else{
	    newGpio &= ~iomask;
	    //joy_data[Joystick].buttons[Index] = 0;
	  }
	}
      }
    }

    else{
      newGpio = ((int*)GPIO)[GPIO_ADDR_OFFSET];
    }
#endif

    
    //hier muss was getan werden
    newGpio= ( (int) Read_Port_HC165()) ^ 0xffffffff;
    iomask=0xffffffff;
    
    //     printf("val: %08X ",newGpio );

    
    //    newGpio &= AllMask;

    //printf("%d: %08x\n", bounceCount, newGpio);
    
    if(newGpio != lastGpio){
      bounceCount=0;
      xGpio |= newGpio ^ lastGpio;
      //printf("%08x\n", xGpio);
    }
    lastGpio = newGpio;

    if(bounceCount>=BOUNCE_TIME) {
      joy_data[Joystick].button_mask = newGpio;
      joy_data[Joystick].change_mask = xGpio;

      for (Index = 0; Index < joy_data[Joystick].num_buttons; ++Index){
	iomask = (1 << gpio_pin(Index));
	joy_data[Joystick].buttons[Index] = !(newGpio & iomask);
	joy_data[Joystick].change[Index] = !!(xGpio & iomask);
      }
      xGpio = 0;
    }

    if(bounceCount<BOUNCE_TIME)bounceCount++;

    joy_handle_event();

    //  }
}

void joy_handle_event(void)
{
  int Joystick = 0;
  int Index;

  if(joy_data[Joystick].change_mask){
    joy_data[Joystick].change_mask = 0;
    for (Index = 0; Index < joy_data[Joystick].num_buttons; ++Index) {
      if( joy_data[Joystick].change[Index] ){
	joy_data[Joystick].change[Index] = 0;
	//printf("Button %d = %d\n", Index, joy_data[Joystick].buttons[Index]);
	send_gpio_keys(gpio_pin(Index), joy_data[Joystick].buttons[Index]);
      } 
    }
  }
}


#endif

