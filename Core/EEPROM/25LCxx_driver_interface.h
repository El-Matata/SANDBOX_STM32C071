
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
 * File:   25LCxx_driver_interface.h
 * Author: Cedric Akilimali
 *
 * Created on August 16, 2022, 3:20 PM
 */

#ifndef _25LCXX_DRIVER_INTERFACE_H_INCLUDED
#define _25LCXX_DRIVER_INTERFACE_H_INCLUDED

#include "25LCxx_driver.h"

static E_25LCxx_handle_t e_25LCxx_handler;

/**
 * @brief  interface spi bus init
 * @return status code
 *         - 0 success
 *         - 1 spi init failed
 * @note   none
 */
uint8_t e_25LCxx_interface_spi_init(void);

/**
 * @brief interface spi bus deinit
 * @return status code
 *          - 0 success
 *          - 1 spi deinit fail
 */
uint8_t e_25LCxx_interface_spi_deinit(void);

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
uint8_t e_25LCxx_interface_spi_read(uint16_t u16Reg, uint32_t *pbuf, uint16_t u16Len);

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
uint8_t e_25LCxx_interface_spi_write(uint16_t u16Reg, uint32_t *pbuf, uint16_t u16Len);

/**
 * @brief   interface gpio write
 * @param[in] u8State is the state logic level to be written
 * @return status code
 *          - 0 success
 *          - 1 failed to write gpio
 */
uint8_t e_25LCxx_interface_gpio_write(uint8_t u8State);

/**
 * @brief   This function interfaces chip select
 * @param[in] u8State is the state logic level to be written
 * @return status code
 *          - 0 success
 *          - 1 failed to write gpio
 */
uint8_t e_25LCxx_interface_chip_select(uint8_t u8State);

/**
 * @brief     interface delay ms
 * @param[in] u32Ms
 * @note      none
 */
void e_25LCxx_interface_delay_ms(uint32_t u32Ms);

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void e_25LCxx_interface_debug_print(const char *const fmt, ...);

#endif // 25LCXX_DRIVER_INTERFACE_H_INCLUDED
