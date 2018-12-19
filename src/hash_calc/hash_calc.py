file_path = "../screen_expansion_project/Release/screen_expansion.hex"
#file_path = "../SPI/atmega368p_SPI/Release/atmega368p_SPI.hex"


def hex_to_hash():
    with open(file_path, mode = 'r') as file:
        hash_val = 0x0000
        n_byte = 0
        for line in file:
            if len(line) == 8:
                # EOF
                break

            for j in range(9,len(line)-3,4):
                # Joins 2 bytes together and calculates the XOR
                
                high = int(line[j],16) << 4
                low = int(line[j+1],16)
                tmp_1 = high | low

                high = int(line[j+2],16) << 4
                low = int(line[j+3],16)
                tmp_2 = high | low
                dat = (tmp_2<<8) | tmp_1

                hash_val = dat ^ hash_val

                n_byte += 2

        print(f"Number of bytes {n_byte}")
        print(f"Generated hash: {hash_val}")

      

hex_to_hash()