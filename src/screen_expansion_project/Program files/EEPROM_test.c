/************************************************************************
 *																		*
 *		FILE NAME: EEPROM_test.c											*
 *		PURPOSE:
 *							Performs a validity test on the used bytes of the EEPROM memory. IN the first place
 *							we save the used memory on the flash, to avoid losing information with the test.
 *							Afterwards, we write 1 on all the locations and try to read a one. We repeat the process
 *							with zero.
 *
 *							IN the end, we restore the data previously stored on the flash memory back to the original position
 *							in the eeprom memory				*
 *		FILE REFERENCES:												*
 *																		*
 *		Name			I/O			Description							*
 *		----			---			-----------							*
 *																		*
 *		EXTERNAL VARIABLES:												*
 *																		*
 *		Name	Type	I/O			Description							*
 *		----	----	---			----------- 						*
 *																		*
 *		EXTERNAL REFERENCES:											*
 *																		*
 *		Name						Description							*
 *		----						-----------							*
 *																		*
 * 		ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES: 	*
 *																		*
 * 		ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:							*
 *																		*
 *		NOTES:															*
 *																		*
 * 		REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:				*
 *																		*
 * 		DEVELOPMENT HISTORY:											*
 *																		*
 *		Date	Author	Change ID	Release		Description of change	*
 *		Dec 11, 2018	André Silva													*
 *																		*
 * 		ALGORITHM (PDL)													*
 *																		*
 ************************************************************************/


#include <EEPROM_test.h>


bool EEPROM_Test(void) {
	/*
	 * Test to verify the correct functioning of the Eeprom memory.
	 * First we write zero to all bytes, to ensure that there is no data in the eeprom
	 * Afterwards, we write one to all bytes and, if the memory is working properly, we should read 1's on all
	 * Then we repeat the process for zeros.
	 * After passing all tests we restore the previously stored data
	 */
    uint16_t real_hash = eeprom_read_word( (uint16_t *) USED_ADDR); /* Stores the real hash stored on the specified Eeprom's addr*/
    uint8_t tmp = 0;
    bool errors = 0; /* If we detect erros, we set this flag to 1*/
    for (uint16_t k = USED_ADDR; k < N_BYTES_EEPROM + USED_ADDR ; k++)
    {
        eeprom_write_byte((uint8_t *) k, 0x00);
    }
    for(uint16_t k = USED_ADDR; k < N_BYTES_EEPROM + USED_ADDR; k++)
    {
    	tmp = eeprom_read_byte((uint8_t*) k);
        if (0 == tmp)
        {
            eeprom_write_byte((uint8_t*) k ,0xFF);
        }
        else
        {
        	errors = 1;
            eeprom_write_byte((uint8_t*) k , 0xFF);
        }
    }


    for(uint16_t k = USED_ADDR; k < N_BYTES_EEPROM + USED_ADDR; k++)
    {
    	tmp=eeprom_read_byte((uint8_t*) k);
        if (0xFF == tmp)
        {
            eeprom_write_byte((uint8_t*) k ,0x00);
        }
        else
        {
        	errors = 1;
            eeprom_write_byte((uint8_t*) k, 0x00);
        }
    }

    for(uint16_t k = USED_ADDR; k < N_BYTES_EEPROM + USED_ADDR; k++)
    {
    	tmp =eeprom_read_byte((uint8_t*) k );
        if(0 != tmp)
        {
        	errors = 1;
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
