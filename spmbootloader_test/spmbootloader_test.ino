/* flash_program
 *
 * June 2015 by Marek Wodzinski, https://github.com/majekw
 * Released to public domain
 *
 * This is example how to use optiboot.h together with Optiboot
 * bootloader to write to FLASH memory by application code.
 *
 * IMPORTANT THINGS:
 * - buffer must be page aligned (see declaration of flash_buffer)
 * - interrupts must be disabled during spm
 * - writing to EEPROM destroys temporary buffer
 * - you can write only once into one location of temporary buffer
 * - only safely and always working sequence is erase-fill-write
 * - if you want to do fill-erase-write, you must put code in NRWW
 *     and pass data!=0 for erase. It's not easy, but possible.
 *
 * WRITE SEQUENCE - option 1 (used in this example)
 * 1. Erase page by optiboot_page_erase
 * 2. Write contents of page into temporary buffer by optiboot_page_fill
 * 3. Write temporary buffer to FLASH by optiboot_page_write
 *
 * WRITE SEQUENCE - option 2 (works only for code in NRWW)
 * 1. Write contents of page into temporary buffer by optiboot_page_fill
 * 2. Erase page by optiboot_page_erase (set data to NOT zero)
 * 3. Write temporary buffer to FLASH by optiboot_page_write
 */

#define SerialX Serial1

#include <avr/boot.h>
typedef void (*do_spm_t)(uint16_t address, uint8_t command, uint16_t data);
#define SLLOCJMP ((do_spm_t)(0x70ac>>1))
const do_spm_t do_spm = SLLOCJMP;


/*
 * The same as do_spm but with disable/restore interrupts state
 * required to succesfull SPM execution
 */
void do_spm_cli(uint16_t address, uint8_t command, uint16_t data) {
  uint8_t sreg_save;

  sreg_save = SREG;  // save old SREG value
  asm volatile("cli");  // disable interrupts
  do_spm(address,command,data);
  SREG=sreg_save; // restore last interrupts state
}


/*
 * Erase page in FLASH
 */
void __page_erase(uint16_t address) {
  do_spm_cli(address,__BOOT_PAGE_ERASE,0);
}


/*
 * Write word into temporary buffer
 */
void __page_fill(uint16_t address, uint16_t data) {
  do_spm_cli(address,__BOOT_PAGE_FILL,data);
}


/*
 * Write temporary buffer into FLASH
 */
void __page_write(uint16_t address) {
  do_spm_cli(address,__BOOT_PAGE_WRITE,0);
}



#include <avr/pgmspace.h>



const char flash_buffer[SPM_PAGESIZE] __attribute__ (( aligned(SPM_PAGESIZE) )) PROGMEM= {
  "0123456789ABCDEFGHIJKLMNOPQRSTUVW"
};

void setup() {
  int i;
  uint8_t c;
  uint16_t w;
  uint8_t ram_buffer[SPM_PAGESIZE];
  pinMode(13, OUTPUT);
  
  // Init serial
  SerialX.begin(9600);
  while (!SerialX) {
         // fade in from min to max in increments of 5 points:
      for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
        // sets the value (range from 0 to 255):
        analogWrite(8, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
      }
    
      // fade out from max to min in increments of 5 points:
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
        // sets the value (range from 0 to 255):
        analogWrite(8, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
      }
  }
  // Print current flash buffer content
  SerialX.println("Current flash contents:");
  for (i=0;i<SPM_PAGESIZE;i++) {
    c = pgm_read_byte(&flash_buffer[i]);
    if (c!=0 && c!=255) {
      SerialX.write(c);
    } else {
      SerialX.print(".");
    }
  }

  // Print prompt to enter some new characters to write to flash
  SerialX.println();
  SerialX.print("Type ");
  SerialX.print(SPM_PAGESIZE);
  SerialX.println(" characters to store in flash:");

  // Get characters from serial and put into ram buffer
  i=0;
  while (i<10) {
    if (SerialX.available()>0) {
      c = SerialX.read(); // read character from serial
      SerialX.write(c); // echo character back
      ram_buffer[i] = c;
      i++;
    }
  }
  SerialX.println("\nAll chars received");
  delay(100); // wait for sending all text via serial

  // Erasing FLASH page
  SerialX.println("Erasing buffer");
  delay(100); // wait for sending all text via serial
  __page_erase((uint16_t)(void*) &flash_buffer[0]);

  // Copy ram buffer to temporary flash buffer
  SerialX.println("Writing to temporary flash buffer");
  delay(100); // wait for sending all text via serial
  for (i=0;i<SPM_PAGESIZE;i++) {
    if (i % 2 == 0) { // we must write WORDs
      w = ram_buffer[i];
    } else {
      w += (ram_buffer[i] << 8);
      __page_fill((uint16_t)(void*) &flash_buffer[i],w);
    }
  }

  // Writing temporary buffer to FLASH
  SerialX.println("Writing buffer to flash");
  delay(100); // wait for sending all text via serial
  __page_write((uint16_t)(void*) &flash_buffer[0]);

  SerialX.println("Write done, thank you!");
  SerialX.println("Now you can reset or power cycle board and check for new contents!");

    // Print current flash buffer content
  SerialX.println("Current flash contents:");
  for (i=0;i<SPM_PAGESIZE;i++) {
    c = pgm_read_byte(&flash_buffer[i]);
    if (c!=0 && c!=255) {
      SerialX.write(c);
    } else {
      SerialX.print(".");
    }
  }
}

void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}
