

uint16_t ASCII_convert_byte_to_ascii(uint8_t byte){
    char lookup_table[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    uint8_t upper_half_word = byte/16;
    uint8_t lower_half_word = byte%16;
    return (lookup_table[upper_half_word] << 8) | lookup_table[lower_half_word];
}

uint8_t ASCII_convert_ascii_to_byte(uint16_t ascii){
    return (ASCII_convert_ascii_to_byte_lookup_table(ascii>>8) * 16) | ASCII_convert_ascii_to_byte_lookup_table(ascii);
}

static uint8_t ASCII_convert_ascii_to_byte_lookup_table(uint8_t ascii){
    if(ascii >= '0' && ascii <= '9'){
        return ascii - '0';
    }
    else if(ascii >= 'A' && ascii <= 'F'){
        return ascii - 'A' + 10;
    }
    else{
        return 0;
    }
}
