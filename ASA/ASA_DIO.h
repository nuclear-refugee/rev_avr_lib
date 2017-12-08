#ifndef __ASA_DIO_H__
#define __ASA_DIO_H__

/**
* @brief Replace of M128_DIO_set()
*/
char ASA_DIO_set(char LSByte, char Mask, char shift, char Data);
/**
 * @brief Replace of M128_DIO_fpt()
 */
char ASA_DIO_fpt(char LSByte, char Mask, char shift, char Data);
/**
* @brief Replace of M128_DIO_fgt()
*/
char ASA_DIO_fgt(char LSByte, char Mask, char shift, char *Data);

#endif /* __ASA_DIO_H__ */
