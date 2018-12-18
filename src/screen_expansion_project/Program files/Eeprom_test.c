
#include <Eeprom_test.h>


uint8_t Eeprom_test(void)
{
	/*
	 * Test to verify the correct functioning of the Eeprom memory.
	 * First we write zero to all bytes, to ensure that there is no data in the eeprom
	 * Afterwards, we write one to all bytes and, if the memory is working properly, we should read 1's on all
	 * Then we repeat the process for zeros.
	 * After passing all tests we restore the previously stored data
	 */
    uint16_t real_hash = eeprom_read_word( (const uint16_t*) USED_ADDR); /* Stores the real hash stored on Eeprom's addr*/
    uint8_t tmp = 0;
    uint8_t errors = 0;
    for (int k =0; k <N_BYTES_EEPROM ; k++)
    {
        eeprom_write_byte((uint8_t*) k , 0x00);
    }
    for(int k =0; k <N_BYTES_EEPROM; k++)
    {
    	tmp = eeprom_read_byte((uint8_t*) k);
        if (0 == tmp)
        {
            eeprom_write_byte((uint8_t*) k ,0xFF);
        }
        else
        {
        	errors++;
            eeprom_write_byte((uint8_t*) k , 0xFF);
        }
    }


    for(int k = 0; k < N_BYTES_EEPROM ; k++)
    {
    	tmp=eeprom_read_byte((uint8_t*) k);
        if (0xFF == tmp)
        {
            eeprom_write_byte((uint8_t*) k ,0x00);
        }
        else
        {
        	errors++;
            eeprom_write_byte((uint8_t*) k, 0x00);
        }
    }

    for (int k =0; k < N_BYTES_EEPROM; k++)
    {
    	tmp =eeprom_read_byte((uint8_t*) k );
        if(0 != tmp)
        {
        	errors++;
        }
    }
    eeprom_write_word(( uint16_t*) USED_ADDR, real_hash);
    if (0 == errors)
    {
    	return 0;
    }
    else
    {
    	return 1;
    }

}
