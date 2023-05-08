/**
 * @file StringC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Interface for StringC
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stddef.h>

#define NULL_CHAR '/0'

/**
 * @brief The main container for our string object. 
 * 
 * @var StringC::length 
 * The size/length of our string
 * 
 * @var StringC::max_size
 * The maximum capacity of our string
 * 
 * @var StringC::buff
 * The sequence of characters that actually define our StringC string
 * 
 */
typedef struct StringC {
    size_t length;
    size_t max_size;
    char *buff;
}StringC;

/**
 * @brief Initializes the StringC container
 * 
 * @param inital_string The initial string that will be contained within StringC. Can be an empty string. 
 * @return StringC* 
 */
StringC *StringC_init(const char *inital_string);

/**
 * @brief Converts all alphabetical characters in a StringC string to its uppercase equivalent
 * 
 * @param stringc A valid pointer to a StringC container 
 * @return The converted string
 */
char *StringC_to_upper(StringC *stringc);

/**
 * @brief Converts all alphabetical characters in a StringC string to its lowercase equivalent
 * 
 * @param stringc 
 * @return char* 
 */
char *StringC_to_lower(StringC *stringc);

