
/**
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File:   25LCxx_driver_interface.c
 * Author: Cedric Akilimali
 *
 * Created on August 16, 2022, 4:09 PM
 */

#include "25LCxx_driver_interface.h"

/**
* @brief  interface spi bus init
* @return status code
*         - 0 success
*         - 1 spi init failed
* @note   none
*/
uint8_t e_25LCxx_interface_spi_init(void)
{
    /*call your spi initialize function here*/
    /*user code begin */

    /*user code end*/
    return 0;      /**< return success */
}

/**
 * @brief interface spi bus deinit
 * @return status code
 *          - 0 success
 *          - 1 spi deinit fail
 */
uint8_t e_25LCxx_interface_spi_deinit(void)
{
    /*call your spi deinitialize function here*/
    /*user code begin */

    /*user code end*/
    return 0;      /**< return success */
}

/**
 * @brief      interface spi bus read
 * @param[in]  u16Reg is the spi register address
 * @param[out] *pBuf points to a data buffer
 * @param[in]  u16Len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t e_25LCxx_interface_spi_read(uint16_t u16Reg, uint32_t *pbuf, uint16_t u16Len)
{
    /*call your spi read function here*/
    /*user code begin */

    /*user code end*/
    return 0;      /**< return success */
}

/**
 * @brief     interface spi bus write
 * @param[in] u16Reg is the spi register address
 * @param[in] *pbuf points to a data buffer
 * @param[in] u16Len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t e_25LCxx_interface_spi_write(uint16_t u16Reg, uint32_t *pbuf, uint16_t u16Len)
{
    /*call your spi write function here*/
    /*user code begin */

    /*user code end*/
    return 0;      /**< return success */
}

/**
 * @brief   interface gpio write (write enable or hold pin)
 * @param[in] u8State is the state logic level to be written
 * @return status code
 *          - 0 success
 *          - 1 failed to write gpio
 */
uint8_t e_25LCxx_interface_gpio_write(uint8_t u8State)
{
    /*call your gpio write function here*/
    /*user code begin */

    /*user code end*/
    return 0;       /**< return success */
}

/**
 * @brief   This function interfaces chip select
 * @param[in] u8State is the state logic level to be written
 * @return status code
 *          - 0 success
 *          - 1 failed to write gpio
 */
uint8_t e_25LCxx_interface_chip_select(uint8_t u8State)
{
    /*call your spi chip select function here*/
    /*user code begin */

    /*user code end*/
    return 0;      /**< return success */
}

/**
 * @brief  This function interface delay ms
 * @param[in] u32Ms is the time delay in milli seconds
 * @note      none
 */
void e_25LCxx_interface_delay_ms(uint32_t u32Ms)
{
    /*call your delay function here*/
    /*user code begin */

    /*user code end*/

}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void e_25LCxx_interface_debug_print(const char *const fmt, ...)
{
    /*call your call print function here*/
    /*user code begin */
#ifdef E_25LCXX_DEBUG_MODE
    volatile char str[256];
    volatile uint8_t len;
    va_list args;

    memset((char *) str, 0, sizeof (char)*256);
    va_start(args, fmt);
    vsnprintf((char *) str, 256, (char const *) fmt, args);
    va_end(args);

    len = strlen((char *) str);
    // printf((char *const)str, len);

    /*user code end*/
#endif
}
