/**
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
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
 * File:   25LCxx_driver.c
 * Author: Cedric Akilimali
 *
 * Created on August 13, 2022, 3:43 PM
 */


#include "25LCxx_driver.h"

/**
 * @brief chip information definition
 */


#define CHIP_NAME                 "25LCxxx"              /**< chip name for spi version */
#define INTERFACE                 "SPI"                  /**< interface 1 protocol */
#define MANUFACTURER_NAME         "Microchip Technology" /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.5f                   /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                   /**< chip max supply voltage */
#define MAX_CURRENT               10.0f                  /**< chip max current (mA)*/
#define MIN_CURRENT               120.0f                 /**< chip min current (mA)*/
#define TEMPERATURE_MIN           -40.0f                 /**< chip min operating temperature (°C) */
#define TEMPERATURE_MAX           125.0f                 /**< chip max operating temperature (°C) */
#define DRIVER_VERSION            1300                   /**< driver version */

/**
 * @brief This function write eeprom spi data
 * @param[in] *pHandler point to 25LCxx handle structure
 * @param[in] u16Address is the address to write to
 * @param[in] *pBuffer point to the data buffer to write
 * @param[in] iLength is the data size to be written
 * @return status code
 *          - 0 success
 *          - 1 failed write
 * @note
 */
uint8_t a_e25lcxx_spi_write(E_25LCxx_handle_t *pHandler, uint16_t u16Address, uint32_t *pBuffer, size_t iLength)
{
    pHandler->gpio_write(E_25LCxx_BOOL_TRUE); /**< disable write protect before attempt writing */
    if (pHandler->spi_write(u16Address, pBuffer, iLength) != 0)
    {
        return 1; /**< error error */
    }
    pHandler->gpio_write(E_25LCxx_BOOL_FALSE); /**< enable write protect pin after writing */
    return 0; /**<success error */

}

/**
 * @brief This function reads eeprom spi data
 * @param[in] *pHandler point to 25LCxx handle structure
 * @param[in] u16Address is the address to read
 * @param[out] *pBuffer point to the data buffer to read
 * @param[in] iLength is the data size to read
 * @return status code
 *          - 0 success
 *          - 1 failed read
 * @note
 */
uint8_t a_e25lcxx_spi_read(E_25LCxx_handle_t *pHandler, uint16_t u16Address, uint32_t *pBuffer, size_t iLength)
{

    if (pHandler->spi_read(u16Address, pBuffer, iLength) != 0)
    {
        return 1; /**< failed error */
    }
    return 0; /**< success error */
}

/**
* @brief This function prints the error message
* @param[in] *pHandle points to 25LCxx handle structure
* @param[in] *pBuffer point to the string to be printed
* @return none
* @note   none
*/
void a_e25lcxx_print_error_msg(E_25LCxx_handle_t *const pHandle, char *const pBuffer)
{
#ifdef E_25LCXX_DEBUG_MODE
    pHandle->debug_print("25LCxx: failed to %s.\r\n", pBuffer);
#endif // E_25LCXX_DEBUG_MODE
}

/**
 * @brief     This function initialize the chip
 * @param[in] *handle points to 25LCxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t E_25LCxx_init(E_25LCxx_handle_t *pHandle)
{

    if (pHandle == NULL)
        return 2; /**< return failed error  */
    if (pHandle->debug_print == NULL)
        return 3; /**< return failed error  */

    if (pHandle->delay_ms == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: delay_ms is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }

    if (pHandle->spi_init == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: initialize is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }

    if (pHandle->spi_deinit == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: de-initialize is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }


    if (pHandle->spi_read == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: spi read is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }


    if (pHandle->spi_write == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: spi write is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }


    if (pHandle->chip_select == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: chip select is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }


    if (pHandle->gpio_write == NULL)
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: gpio write is null\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 3;
    }

    if (pHandle->spi_init())
    {

#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: failed to initialize spi\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 1;
    }

    pHandle->u8Inited = 1;
    return 0; /**< return success */
}

/**
 * @brief     This function close the chip
 * @param[in] *handle points to 25LCxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_deinit(E_25LCxx_handle_t *pHandle)
{
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    if (pHandle->spi_deinit() != 0)
    {
        a_e25lcxx_print_error_msg(pHandle, "de-initialize");
        return 1;
    }
    pHandle->u8Inited = 0; /**< close driver */
    return 0; /**< return success */

}

/**
 * @brief     This function set the chip variant
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] variant is the chip variant
 * @return    status code
 *            - 0 success
 *            - 1 set variant failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_set_variant(E_25LCxx_handle_t *pHandle, E_25LCxx_variant_t variant)
{
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->u8Device_type = variant;

    if (pHandle->u8Device_type != variant)
    {
        a_e25lcxx_print_error_msg(pHandle, "set variant");
        return 1; /**< return failed error*/
    }
    return 0; /**< return success */
}

/**
 * @brief     This function get the chip variant
 * @param[in] *handle points to 25LCxx handle structure
 * @param[out] *pVariant point to the chip variant
 * @return    status code
 *            - 0 success
 *            - 1 get variant failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_variant(E_25LCxx_handle_t *pHandle, E_25LCxx_variant_t *pVariant)
{

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    *pVariant = (E_25LCxx_variant_t) (pHandle->u8Device_type);
    if (pHandle->u8Device_type != *pVariant)
    {
        a_e25lcxx_print_error_msg(pHandle, "get variant");
        return 1; /**< return failed error */
    }
    return 0; /**< return success */
}

/**
 * @brief     This function set eeprom page size
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] iSize is the eeprom page size in byte
 * @return    status code
 *            - 0 success
 *            - 1 set page size failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_set_page_size(E_25LCxx_handle_t *pHandle, E_25LCxx_page_size_t iSize)
{
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->iPage_size = iSize;
    if (pHandle->iPage_size != iSize)
    {
        a_e25lcxx_print_error_msg(pHandle, "set page size");
        return 1; /**< return failed error */
    }

    return 0; /**< return success */
}

/**
 * @brief     This function get eeprom page size
 * @param[in] *handle points to 25LCxx handle structure
 * @param[out] *pSize point to the eeprom page size in byte
 * @return    status code
 *            - 0 success
 *            - 1 get page size failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */

uint8_t E_25LCxx_get_page_size(E_25LCxx_handle_t *pHandle, E_25LCxx_page_size_t *pSize)
{
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    *pSize = (E_25LCxx_page_size_t) (pHandle->iPage_size);
    if (pHandle->iPage_size != *pSize)
    {
        a_e25lcxx_print_error_msg(pHandle, "get page size");
        return 1; /**< return failed error */
    }

    return 0; /**< return success */
}

/**
 * @brief     This function get write in progress status
 * @param[in] *handle points to 25LCxx handle structure
 * @param[out] *status point to write in progress status
 * @return    status code
 *            - 0 success
 *            - 1 get status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_wip_status(E_25LCxx_handle_t *pHandle, E_25LCxx_write_in_process_status_t *pStatus)
{
    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint8_t *) & status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }

    *pStatus = (E_25LCxx_write_in_process_status_t) (status & E_25LCXXX_WIP_MASK);

    return 0; /**< return success */
}

/**
 * @brief     This function get write enable latch status
 * @param[in] *handle points to 25LCxx handle structure
 * @param[out] *status point to write in progress status
 * @return    status code
 *            - 0 success
 *            - 1 get status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_wel_status(E_25LCxx_handle_t *pHandle, E_25LCxx_write_en_latch_staus_t *pStatus)
{
    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint32_t *) & status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }
    *pStatus = (E_25LCxx_write_en_latch_staus_t) ((status & E_25LCXXX_WEL_MASK) >> 1);

    return 0; /**< return success */
}

/**
 * @brief     This function set write enable latch status
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] status is the value to write
 * @return    status code
 *            - 0 success
 *            - 1 set bp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_set_bp_status(E_25LCxx_handle_t *pHandle, E_25LCxx_block_protection_status_t status)
{
    uint8_t res;
    uint8_t stat;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint8_t *) &stat, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0); /**< enable write operation */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    stat &= ~(0x03 << 2);
    stat |= (status << 2);
    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WRSR_REG, (uint8_t*) &stat, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "write status register");
        return 1; /**< return failed error **/
    }
    return 0; /**< return success */

}

/**
 * @brief     This function get write enable latch status
 * @param[in] *handle points to 25LCxx handle structure
 * @param[out] *pStatus is the value to write
 * @return    status code
 *            - 0 success
 *            - 1 get bp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_bp_status(E_25LCxx_handle_t *pHandle, E_25LCxx_block_protection_status_t *pStatus)
{
    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint8_t *) &status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }

    *pStatus = (E_25LCxx_block_protection_status_t) ((status & E_25LCXXX_BP_MASK) >> 2);
    return 0; /**< return success */
}

/**
 * @brief     This function set write protect enable status
 * @param[in] *pHandle points to 25LCxx handle structure
 * @param[out] enable is the is the boolean status to write
 * @return    status code
 *            - 0 success
 *            - 1 set wpen failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_set_write_protect_enable(E_25LCxx_handle_t *pHandle, E_25LCxx_bool_t enable)
{
    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint8_t *) &status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    status &= ~(1 << 7);
    status |= (enable << 7);

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WRSR_REG, (uint8_t *) &status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "write status register");
        return 1; /**< return failed error **/
    }

    return 0; /**< return success */

}

/**
 * @brief     This function fetch the protect enable status
 * @param[in] *pHandle points to 25LCxx handle structure
 * @param[out] *pEnable point to the boolean status
 * @return    status code
 *            - 0 success
 *            - 1 get wpen failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_write_protect_enable(E_25LCxx_handle_t *pHandle, E_25LCxx_bool_t *pEnable)
{
    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RDSR_REG, (uint8_t *) &status, 1);
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read status register");
        return 1; /**< return failed error **/
    }

    *pEnable = (E_25LCxx_bool_t) ((status & E_25LCXXX_WPEN_MASK) >> 7);
    return 0; /**< return success */

}

/**
 * @brief     This function write n byte to eeprom
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] addr is the eeprom address to write to
 * @param[in] *buf points to data buffer to be written
 * @param[in] u16Length is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address (failed to validate address)
 *            - 5 attempt to write a protected block array
 *            - 6 data length is larger than page can contain
 * @note      none
 */
uint8_t E_25LCxx_write_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint8_t *pBuf, uint16_t u16Length)
{
    uint8_t res;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    if (E_25LCXX_validate_page_boundary(pHandle, u16Addr, u16Length) != 0)
        return 6; /**< return failed error */
    if (E_25LCxxx_validate_address(pHandle, u16Addr) != 0) /**< check if the address to write is valid or not */
        return 4; /**< return failed error */
    if (E_25LCxx_check_bp_before_write(pHandle, u16Addr) != 0) /**< check that we're not trying to write on protected block  */
        return 5; /**< return failed error */


    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0); /**< enable write operation */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WRITE_REG, NULL, 0); /**< send write command  */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "send write command");
        return 1; /**< return failed error **/
    }
    res = a_e25lcxx_spi_write(pHandle, (u16Addr >> 8), NULL, 0); /**< write MSB of the address */
    res = a_e25lcxx_spi_write(pHandle, (uint8_t) u16Addr, (uint8_t*) pBuf, u16Length); /**< add 1 byte on the size to cater for the addr byte */

    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "write data byte");
        return 1; /**< return failed error */
    }
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */

    return 0; /**< return success */
}

/**
 * @brief     This function writes data larger than a byte
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] addr is the eeprom address to start writing
 * @param[in] *buf points to data buffer write
 * @param[in] u16Length is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address (failed to validate address)
 *            - 5 attempt to write a protected block array
 *            - 6 data length is larger than page can contain
 * @note       Equivalent to eeprom.put on Arduino
 */
uint8_t E_25LCXX_put_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, unsigned long long *pBuf, uint8_t u16Length)
{

    uint8_t res;
    static uint8_t dataIndex, wipStatus;
    uint8_t tempBuffer[u16Length]; /**< Temporarily buffer */
    unsigned long long dataOut;
    static uint8_t counter = 0;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    memcpy(tempBuffer, pBuf, u16Length);

    /**< Reverse array data to big Indian*/
    for (dataIndex = 0; dataIndex < u16Length / 2; dataIndex++)
    {
        dataOut = tempBuffer[dataIndex];
        tempBuffer[dataIndex] = tempBuffer[u16Length - dataIndex - 1];
        tempBuffer[u16Length - dataIndex - 1] = dataOut;
    }

    for (dataIndex = u16Addr; dataIndex < (u16Length + u16Addr); dataIndex++)
    {
        res = (E_25LCxx_write_byte(pHandle, dataIndex, (uint8_t *) &tempBuffer[counter], 1));
        if (res)
        {
            a_e25lcxx_print_error_msg(pHandle, "put bytes");
            return 1; /**< failed to write */
        }
        counter++;

        do
        {
            res = (E_25LCxx_get_wip_status(pHandle, (uint8_t*) & wipStatus));
            if (res)
            {
                a_e25lcxx_print_error_msg(pHandle, "read WIP status");
                break;
                return 1;
            }
        }
        while (wipStatus);   /** wait for each byte to successfully complete writing */
    }

    return 0; /**< return success */
}

/**
 * @brief     This function read n byte from EEPROM
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] addr is the EEPROM address to read
 * @param[out] *buf points to data buffer read
 * @param[in] u16Length is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address (failed to validate address)
 * @note      none
 */
uint8_t E_25LCxx_read_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint8_t *pBuf, uint16_t u16Length)
{

    uint8_t res;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    if (E_25LCxxx_validate_address(pHandle, u16Addr) != 0)
        return 4; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_READ_REG, NULL, 0); /**< send a read command */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "issue read command");
        return 1;
    }
    res = a_e25lcxx_spi_write(pHandle, (u16Addr >> 8), NULL, 0); /**< write MSb address */
    res = a_e25lcxx_spi_read(pHandle, (uint8_t) u16Addr, (uint8_t *) pBuf, u16Length); /**< read data off the buffer */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read byte");
        return 1;
    }

    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */

    return 0; /**< return success */
}

/**
 * @brief     This function reads data larger than a byte > 255
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] addr is the eeprom address to start writing
 * @param[out] *buf points to data buffer read
 * @param[in] u16Length is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address (failed to validate address)
 * @note     Equivalent to eeprom.get on Arduino
 */

uint8_t E_25LCXX_get_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint32_t *pBuf, uint8_t u16Length)
{
    static uint8_t res, index;
    uint8_t tempBuffer[u16Length];
    uint8_t count = u16Length - 1;
    static uint32_t dataOut;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    res = (E_25LCxx_read_byte(pHandle, u16Addr, (uint8_t*) tempBuffer, u16Length));
    if (res != NULL)
    {
        a_e25lcxx_print_error_msg(pHandle, "get bytes");
        return 1; /**< return error code */
    }

    /**< Reverse array data to Big Indian*/
    for (index = 0; index < u16Length / 2; index++)
    {
        dataOut = tempBuffer[index];
        tempBuffer[index] = tempBuffer[u16Length - index - 1];
        tempBuffer[u16Length - index - 1] = dataOut;
    }

    memcpy(dataReadOut.buffer, tempBuffer, u16Length);

    *pBuf = (uint32_t) dataReadOut.data;

    return 0;

}

/**
 * @brief     This function erase eeprom page
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] u16PageNumber is the eeprom page number to erase
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid page (out of boundary)
 * @note      Page erase instruction will erase all bits (FFh) inside the given page.
 */
uint8_t E_25LCxx_erase_page(E_25LCxx_handle_t *pHandle, uint16_t u16PageNumber)
{
    uint8_t res;
    uint16_t pageStartAdd; /**< define variable to hold page start address */
    uint8_t data[pHandle->iPage_size];

    memset(data, 0xff, pHandle->iPage_size); /**< define data to write when erasing page (default 255)*/

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    if (E_25LCxxx_validate_page(pHandle, u16PageNumber, (uint16_t *) &pageStartAdd) != NULL)
        return 4; /**< return failed error */
    if (E_25LCxx_check_bp_before_write(pHandle, pageStartAdd) != NULL)
        return 5; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0); /**< enable write operation */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip deselect */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    if (pHandle->u8Device_type == E_25LC512_VARIANT)
    {
        res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_PAGE_ERASE_CMD, NULL, 0); /**< send an erase command  */
        res = a_e25lcxx_spi_write(pHandle, (pageStartAdd >> 8), NULL, 0); /**< write MSB byte  */
        res = a_e25lcxx_spi_write(pHandle, (uint8_t) pageStartAdd, NULL, 0); /**< write LSB byte  */
    }
    else
    {

        res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WRITE_REG, NULL, 0); /**< send the write command  */
        if (res)
        {
            a_e25lcxx_print_error_msg(pHandle, "send write command");
            return 1; /**< return failed error **/
        }
        res = a_e25lcxx_spi_write(pHandle, (pageStartAdd >> 8), NULL, 0); /**< write MSB byte  */
        res = a_e25lcxx_spi_write(pHandle, (uint8_t) pageStartAdd, (uint8_t *) & data, pHandle->iPage_size); /**< write LSB byte  */
    }

    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "erase page");
        return 1; /**< return failed error **/
    }
    pHandle->chip_select(SLAVE_ASSERT); /**< chip deselect */

    return 0; /**< return success */
}

/**
 * @brief     This function erase a sector stored data
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] pSector_addr is the eeprom sector address (start address and end address) to erase
 * @return    status code
 *            - 0 success
 *            - 1 erase failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address
 * @note      sector erase instruction will erase all bits (FFh) inside the given sector
 */
uint8_t E_25LCxx_erase_sector(E_25LCxx_handle_t *pHandle, uint16_t *pSector_addr)
{

    uint8_t res;
    uint8_t index;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    for (index = 0; index < 2; index++)
    {
        if (E_25LCxxx_validate_address(pHandle, pSector_addr[index]) != NULL) /**< check if the address to erase is valid or not */
        {
            a_e25lcxx_print_error_msg(pHandle, "write, invalid address");
            return 4; /**< return failed error */
        }
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0); /**< enable write operation */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_SECTOR_ERASE_CMD, NULL, 0); /**< send an erase command and sector to erase */
    res = a_e25lcxx_spi_write(pHandle, (pSector_addr[0] >> 8), (uint8_t*) & pSector_addr[0], 1); /**< write MSB and LSB byte of the start address */
    res = a_e25lcxx_spi_write(pHandle, (pSector_addr[1] >> 8), (uint8_t*) & pSector_addr[1], 1); /**< write MSB and LSB byte of the last address */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "send erase sector");
        return 1; /**< return failed error **/
    }
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */

    return 0; /**< return success */
}

/**
 * @brief     This function erase chip stored data
 * @param[in] *handle points to 25LCxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 erase failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      chip erase instruction will erase all bits (FFh) in the array.
 */
uint8_t E_25LCxx_erase_chip(E_25LCxx_handle_t *pHandle)
{
    uint8_t res;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_WREN_REG, NULL, 0); /**< enable write operation */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "enable write operation");
        return 1; /**< return fail error */
    }

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_CHIP_ERASE_CMD, NULL, 0); /**< send an chip erase command */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "erase chip");
        return 1; /**< return failed error **/
    }
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */

    return 0; /**< return success */
}

/**
 * @brief     This function set device in deep power down mode
 * @param[in] *handle points to 25LCxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 failed to set power down
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      All instructions given during Deep Power-Down mode are ignored except the Read Electronic Signature command
 */
uint8_t E_25LCxx_set_deep_power_down_mode(E_25LCxx_handle_t *pHandle)
{
    uint8_t res;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_write(pHandle, E_25LCXXX_DEEP_POWER_DOWN_MODE, NULL, 0); /**< send the seep power down command */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "set deep power mode");
        return 1; /**< return failed error **/
    }


    return 0; /**< return success */
}

/**
 * @brief     This function get chip electronic signature
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] *Id point to manufacture ID
 * @return    status code
 *            - 0 success
 *            - 1 failed to set power down
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      All instructions given during Deep Power-Down mode are ignored except the Read Electronic Signature command
 */
uint8_t E_25LCxx_get_manufacture_id(E_25LCxx_handle_t *pHandle, uint8_t *pId)
{

    uint8_t res;
    uint8_t status;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    pHandle->chip_select(SLAVE_SELECT); /**< chip select */
    res = a_e25lcxx_spi_read(pHandle, E_25LCXXX_RELEASE_DPD_READ_ID, (uint8_t *) &status, 1); /**< send read electronic signature command */
    pHandle->chip_select(SLAVE_ASSERT); /**< chip assert */
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read Mfr ID  and release from DPD mode");
        return 1; /**< return failed error **/
    }

    *pId = status;

    return 0; /**< return success */
}

/**
 * @brief This function runs basic checks before writing
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] u16Address is the address to write
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t E_25LCxx_check_bp_before_write(E_25LCxx_handle_t *pHandle, uint16_t u16Address)
{
    uint8_t status;
    uint16_t memoryLength;
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    E_25LCxx_get_bp_status(pHandle, (uint8_t*) &status);
    E_25LCxx_get_legth(pHandle, (uint16_t *) &memoryLength);

    switch (status)
    {

    case E_25LCxx_BP00: /* write to full memory enable */
    {
        return 0;
        break;
    }

    case E_25LCxx_BP01:
    {
        if (u16Address >= (memoryLength * 0.75))
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LCxx: failed to write from address: %d, 25%% of the upper memory is write protected\r\n", u16Address);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return error */
        }
        else
        {
            return 0;
        }
        break;
    }

    case E_25LCxx_BP10:
    {
        if (u16Address >= (memoryLength * 0.5))
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LCxx: failed to write from address: %d, half of the memory is write protected\r\n", u16Address);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return error */
        }
        else
        {
            return 0;
        }
        break;
    }

    case E_25LCxx_BP11:
    {
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: write failed, eeprom full memory write protected, check the BP status\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 1; /**< return error */
        break;
    }

    default:
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx: write failed,unknown block protect status\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 1; /**< return error */
        break;

    }
}

/**
 * @brief This function validate the address to write or read
 * @param[in] *pHandle point to the handle structure
 * @param[in] u16Address is the address to validate
 * @return status code
 *          - 0 success (validated)
 *          - 1 failed validate
 *          - 2 handle is NULL
 *          - 3 handle is not initialized
 * @note    none
 */
uint8_t E_25LCxxx_validate_address(E_25LCxx_handle_t *pHandle, E_25LCxx_max_addr_t u16Address)
{

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    uint16_t address = (uint16_t) u16Address;

    switch (pHandle->u8Device_type)
    {

    case E_25LC080x_VARIANT:
    {
        if (address > E_25LC080x_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC080x: address %d is greater than max allowed %d\r\n", address, E_25LC080x_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC160x_VARIANT:
    {
        if (address > E_25LC160x_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC160x: address %d is greater than max allowed %d\r\n", address, E_25LC160x_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC320x_VARIANT:
    {
        if (address > E_25LC320x_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC320x: address %d is greater than max allowed %d\r\n", address, E_25LC320x_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC640x_VARIANT:
    {
        if (address > E_25LC640x_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC640x: address %d is greater than max allowed %d\r\n", address, E_25LC640x_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC128_VARIANT:
    {

        if (address > E_25LC128_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC128: address %d is greater than max allowed %d\r\n", address, E_25LC128_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC256_VARIANT:
    {
        if (address > E_25LC256_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC256: address %d is greater than max allowed %d\r\n", address, E_25LC256_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC512_VARIANT:
    {
        if (address > E_25LC512_MAX_ADD)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC512: address %d is greater than max allowed %d\r\n", address, E_25LC512_MAX_ADD);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    default:
#ifdef E_25LCXX_DEBUG_MODE
        pHandle->debug_print("25LCxx:failed to validate address eeprom type unknown\r\n");
#endif // E_25LCXX_DEBUG_MODE
        return 1; /**< return failed error **/
        break;
    }

    return 0; /**< address validated */

}

/**
 * @brief This function checks to make that we're not trying  to write beyond page boundary
 * @param[in] *pHandle point to the handle structure
 * @param[in] u16Address is the address to validate
 * @param[in] u816Length is data length
 * @return status code
 *          - 0 success (validated)
 *          - 1 failed to validate
 *          - 2 handle is NULL
 *          - 3 handle is not initialized
 * @note    none
 */
uint8_t E_25LCXX_validate_page_boundary(E_25LCxx_handle_t *pHandle, uint16_t u16Address, uint16_t u16Length)
{
    float status;
    uint16_t index, res;
    uint16_t startAdress, endAddress;

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    for (index = 0; index < (e_25LCxx_basic_get_eeprom_legth() / pHandle->iPage_size); index++)
    {

        if ((index * pHandle->iPage_size) > u16Address) /**< get start address page number(index) */
        {
            status = (u16Address + u16Length) / (float) pHandle->iPage_size;
            res = ceil(status);
            if (res > index)
            {
                startAdress = (uint16_t) (pHandle->iPage_size * (index - 1));
                endAddress = (startAdress + pHandle->iPage_size) - 1;
#ifdef E_25LCXX_DEBUG_MODE
                pHandle->debug_print("25LCxx: failed to execute, attempt to write beyond page boundary\r\n");
                pHandle->debug_print("25LCxx: page %d start address:%d end address:%d\r\n", index, startAdress, endAddress);
#endif // E_25LCXX_DEBUG_MODE
                return 1; /**< return failed error **/
            }
            break;
        }
    }

    return 0; /**< page boundary validated */
}

/**
 * @brief This function validate the page number to write or read
 * @param[in] *pHandle point to the handle structure
 * @param[in] u16Page is the page to validate
 * @param[out] *pStartAddr is the start address of the page to write
 * @return status code
 *          - 0 success (page)
 *          - 1 failed page (out of range)
 *           - 2 handle is NULL
 *          - 3 handle is not initialized
 * @note    none
 */
uint8_t E_25LCxxx_validate_page(E_25LCxx_handle_t *pHandle, uint16_t u16Page, uint16_t *pStartAddr)
{
    uint16_t max_page; /**< maximum number of pages starting from page 1 */

    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    switch (pHandle->u8Device_type)
    {

    case E_25LC080x_VARIANT:
    {
        max_page = ((E_25LC080x_MAX_ADD + 1) / pHandle->iPage_size);
        if (u16Page > max_page)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC080x: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC160x_VARIANT:
    {
        max_page = ((E_25LC160x_MAX_ADD + 1) / pHandle->iPage_size);
        if (u16Page > max_page)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC160x: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;
    }

    case E_25LC320x_VARIANT:
    {
        max_page = ((E_25LC320x_MAX_ADD + 1) / pHandle->iPage_size);
        if (u16Page > max_page)
        {
#ifdef E_25LCXX_DEBUG_MODE
            pHandle->debug_print("25LC320x: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
            return 1; /**< return failed error **/
        }
        break;

        case E_25LC640x_VARIANT:
        {
            max_page = ((E_25LC640x_MAX_ADD + 1) / pHandle->iPage_size);
            if (u16Page > max_page)
            {
#ifdef E_25LCXX_DEBUG_MODE
                pHandle->debug_print("25LC640x: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
                return 1; /**< return failed error **/
            }
            break;
        }

        case E_25LC128_VARIANT:
        {
            max_page = ((E_25LC128_MAX_ADD + 1) / pHandle->iPage_size);
            if (u16Page > max_page)
            {
#ifdef E_25LCXX_DEBUG_MODE
                pHandle->debug_print("25LC128: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
                return 1; /**< return failed error **/
            }
            break;
        }

        case E_25LC256_VARIANT:
        {
            max_page = ((E_25LC256_MAX_ADD + 1) / pHandle->iPage_size);
            if (u16Page > max_page)
            {
#ifdef E_25LCXX_DEBUG_MODE
                pHandle->debug_print("25LC256: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
                return 1; /**< return failed error **/
            }
            break;
        }

        case E_25LC512_VARIANT:
        {
            max_page = ((E_25LC512_MAX_ADD + 1) / pHandle->iPage_size);
            if (u16Page > max_page)
            {
#ifdef E_25LCXX_DEBUG_MODE
                pHandle->debug_print("25LC512: page %d is greater than max page number %d\r\n", u16Page, max_page);
#endif // E_25LCXX_DEBUG_MODE
                return 1; /**< return failed error **/
            }
            break;
        }

        default:
            a_e25lcxx_print_error_msg(pHandle, "validate page, device variant unknown");
            return 1; /**< return failed error **/
            break;
        }
    }
    *pStartAddr = (uint16_t) (pHandle->iPage_size * (u16Page - 1));

    return 0; /**< address validated */
}

/**
 * @brief     This function get the size of eeprom in byte
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] length is the eeprom size in byte
 * @return    status code
 *            - 0 success
 *            - 1 failed get length
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_legth(E_25LCxx_handle_t *pHandle, E_25LCxx_max_addr_t *pLength)
{
    uint8_t res;
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */

    switch (pHandle->u8Device_type)
    {
    case E_25LC080x_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC080x_MAX_ADD + 1);
        break;

    case E_25LC160x_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC160x_MAX_ADD + 1);
        break;

    case E_25LC320x_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC320x_MAX_ADD + 1);
        break;

    case E_25LC640x_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC640x_MAX_ADD + 1);
        break;

    case E_25LC128_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC128_MAX_ADD + 1);
        break;

    case E_25LC256_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC256_MAX_ADD + 1);
        break;

    case E_25LC512_VARIANT:
        *pLength = (E_25LCxx_max_addr_t) (E_25LC512_MAX_ADD + 1);
        break;

    default:
        a_e25lcxx_print_error_msg(pHandle, "invalid device variant");
        return 1; /**< return failed error **/
        break;
    }
    return 0; /**< return success */

}

/**
 * @brief     This function set the chip register
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] reg is the spi register address
 * @param[in] *buf points to a data buffer
 * @param[in] length is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_set_reg(E_25LCxx_handle_t *pHandle, uint16_t u16Reg, uint32_t *pBuf, size_t iLength)
{
    uint8_t res;
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    res = a_e25lcxx_spi_write(pHandle, u16Reg, pBuf, iLength);
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read Mfr ID  and release from DPD mode");
        return 1; /**< return failed error **/
    }
    return 0; /**< return success */
}

/**
 * @brief      This function get the chip register
 * @param[in]  *handle points to 25LCxx handle structure
 * @param[in]  reg is the spi register address
 * @param[out] *buf points to a data buffer
 * @param[in]  length is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t E_25LCxx_get_reg(E_25LCxx_handle_t *pHandle, uint16_t u16Reg, uint32_t *pBuf, size_t iLength)
{
    uint8_t res;
    if (pHandle == NULL)
        return 2; /**< return failed error */
    if (pHandle->u8Inited != 1)
        return 3; /**< return failed error */
    res = a_e25lcxx_spi_read(pHandle, u16Reg, pBuf, iLength);
    if (res)
    {
        a_e25lcxx_print_error_msg(pHandle, "read Mfr ID  and release from DPD mode");
        return 1; /**< return failed error **/
    }
    return 0; /**< return success */
}

/**
 * @brief      This function get chip's information
 * @param[out] *info points to 25LCxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */

uint8_t E_25LCxx_info(E_25LCxx_info_t *pInfo)
{
    if (pInfo == NULL) /**< check if handle is null */
    {
        return 2; /**<failed, return error */
    }
    memset(pInfo, 0, sizeof (E_25LCxx_info_t)); /**< initialize 25LCxxx info structure */
    strncpy(pInfo->chip_name, CHIP_NAME, 10); /**< copy chip name */
    strncpy(pInfo->interface, INTERFACE, 5); /**< copy interface name */
    strncpy(pInfo->manufacturer_name, MANUFACTURER_NAME, 25); /**< copy manufacturer name */
    pInfo->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX; /**< set minimal supply voltage */
    pInfo->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN; /**< set maximum supply voltage */
    pInfo->max_current_ma = MAX_CURRENT; /**< set maximum current */
    pInfo->temperature_max = TEMPERATURE_MAX; /**< set minimal temperature */
    pInfo->temperature_min = TEMPERATURE_MIN; /**< set maximum temperature */
    pInfo->driver_version = DRIVER_VERSION; /**< set driver version */

    return 0; /**< return success */
}

/*end*/
