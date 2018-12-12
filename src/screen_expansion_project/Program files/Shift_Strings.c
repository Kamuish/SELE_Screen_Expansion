/*
 * Shift_Strings.c
 *
 *  Created on: Dec 12, 2018
 *      Author: andre
 */



void shift_str(uint8_t *string_1, uint8_t *string_2){
	/*
	 *
	 * Important: Only works if string 1 has exactly 16 letters !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */
    uint8_t new_string_1[16] = "";
    uint8_t new_string_2[16] = "";

    new_string_1[0] = ' ';
    new_string_2[0] = ' ';




    int k = 0;
    for (k = 1; k <16; k++){
        new_string_1[k] = string_1[k-1];
        new_string_2[k] = string_2[k-1];

    }

    new_string_2[0] = string_1[2];

    for (k = 0; k <16;  k++){
        string_1[k] = new_string_1[k];
        string_2[k] = new_string_2[k];
    }

}
