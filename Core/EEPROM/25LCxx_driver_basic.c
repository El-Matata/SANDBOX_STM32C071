
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
 * File:   25LCxx_driver_basic.c
 * Author: Cedric Akilimali
 *
 * Created on August 16, 2022, 5:09 PM
 */

#include "25LCxx_driver_basic.h"


/**
 * @brief basic example initialize
 * @param[in] DeviceVariant is the device type
 * @param[in] pageSize is the page size in byte
 * @return status code
 *          - 0 success
 *          - 1 initialize failed
 * @note    none
 */

uint8_t e_25LCxx_basic_initialize(E_25LCxx_variant_t DeviceVariant, E_25LCxx_page_size_t pageSize)
{
    uint8_t res;

    /*link driver functions */
    DRIVER_25LCXX_LINK_INIT(&e_25LCxx_handler, E_25LCxx_handle_t);
    DRIVER_25LCXX_LINK_SPI_INIT(&e_25LCxx_handler, e_25LCxx_interface_spi_init);
    DRIVER_25LCXX_LINK_SPI_DEINIT(&e_25LCxx_handler, e_25LCxx_interface_spi_deinit);
    DRIVER_25LCXX_LINK_SPI_READ(&e_25LCxx_handler, e_25LCxx_interface_spi_read);
    DRIVER_25LCXX_LINK_SPI_WRITE(&e_25LCxx_handler, e_25LCxx_interface_spi_write);
    DRIVER_25LCXX_LINK_CHIP_SELECT(&e_25LCxx_handler, e_25LCxx_interface_chip_select);
    DRIVER_25LCXX_LINK_GPIO_WRITE(&e_25LCxx_handler, e_25LCxx_interface_gpio_write);
    DRIVER_25LCXX_LINK_DEBUG_PRINT(&e_25LCxx_handler, e_25LCxx_interface_debug_print);
    DRIVER_25LCXX_LINK_DELAY_MS(&e_25LCxx_handler, e_25LCxx_interface_delay_ms);

    /*25LCxx initialize*/
    res = E_25LCxx_init(&e_25LCxx_handler);
    if(res)
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "initialize failed");
        return 1;
    }

    res = E_25LCxx_set_variant(&e_25LCxx_handler, DeviceVariant);
    if(res)
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "set device variant");
        return 1;
    }

    res = E_25LCxx_set_page_size(&e_25LCxx_handler, pageSize);
    if(res)
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "set page size");
        return 1;
    }

    res = E_25LCxx_set_bp_status(&e_25LCxx_handler, E_25LCxx_BP01);
    if(res)
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "set block protect status");
        return 1;
    }
    e_25LCxx_interface_delay_ms(10);
    res = E_25LCxx_set_write_protect_enable(&e_25LCxx_handler, E_25LCxx_BOOL_FALSE);
    if(res)
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "set write protect status");
        return 1;
    }

    e_25LCxx_interface_delay_ms(10);                                                        /**< delay 10ms after initializing */
    return 0;                                                                               /**< return success */
}

/**
 * @brief basic write byte example
 * @param[in] u16Address is the address to write
 * @param[in] u16Size is the data size
 * @param[in] *pBuffer point to data be written
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_write_byte(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size)
{
    if(E_25LCxx_write_byte(&e_25LCxx_handler, u16Address, (uint8_t *)pBuffer, u16Size) != 0)
    {
        return 1;                                                                            /**< return failed error */
    }

    if(e_25LCxx_basic_get_wip_status())                                                      /**< check write in progress status */
    {
        return 1;                                                                            /**< return error */
    }

    return 0;                                                                                /**< return success */
}

/**
 * @brief basic function to write number greater than a byte
 * @param[in] u16Address is the address to write
 * @param[in] u16Size is the data size
 * @param[in] *pBuffer point to data be written
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    equivalent to eeprom.put on Arduino
 */
uint8_t e_25LCxx_basic_put_byte(uint16_t u16Address, unsigned long long *pBuffer, uint16_t u16Size)
{
    if(E_25LCXX_put_byte(&e_25LCxx_handler, u16Address, (unsigned long long *)pBuffer, u16Size) != NULL)
    {
        return 1;                                                                            /**< return failed error */
    }

    if(e_25LCxx_basic_get_wip_status())                                                      /**< check write in progress status */
    {
        return 1;                                                                            /**< return error */
    }

    return 0;                                                                                /**< return success */
}

/**
 * @brief basic read byte example
 * @param[in] u16Address is the address to read
 * @param[out] *pBuffer point to data read
 * @param[in] u16Size is the data size or length
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_read_byte(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size)
{
    if(E_25LCxx_read_byte(&e_25LCxx_handler, u16Address, (uint8_t *)pBuffer, u16Size) != 0)        /**< begin reading process */
    {
        return 1;                                                                                 /**< return failed error code */
    }
    return 0;                                                                                     /**< return success */
}



/**
 * @brief basic function read data greater than a byte
 * @param[in] u16Address is the start address to read
 * @param[out] *pBuffer point to data read
 * @param[in] u16Size is the data size
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    equivalent to eeprom.get on Arduino
 */
uint8_t e_25LCxx_basic_get_byte(uint16_t u16Address, uint32_t *pBuffer, uint16_t u16Size)
{
    if(E_25LCXX_get_byte(&e_25LCxx_handler, u16Address, (uint32_t *)pBuffer, u16Size) != 0)
    {
        return 1;       /**< return error, read failed */
    }
    return 0;           /**< read successful */
}

/**
 * @brief This function write a byte to the EEPROM.
 * @param[in] u16Address is the address to write
 * @param[in] *pBuffer point to data write
 * @param[in] u16Size is the data size
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    The value is written only if differs from the one already saved at the same address.
 */
uint8_t e_25LCxx_basic_update(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size)
{
    uint8_t tempBuf[u16Size];
    static uint16_t index;
    memset(tempBuf, NULL, u16Size);   /* clear memory */
    if(e_25LCxx_basic_read_byte( u16Address, (uint8_t *)tempBuf, u16Size) != 0)       /**< begin reading process */
    {
        return 1;                                                                   /**< return failed error code */
    }

    for(index = 0; index <u16Size; index++)
    {
        if(tempBuf[index] != pBuffer[index])
        {
            e_25LCxx_basic_write_byte((u16Address + index),  (uint8_t*)&pBuffer[index], 1);
        }
        else
        {
#ifdef E_25LCXX_DEBUG_MODE
//            e_25LCxx_interface_debug_print("25LCxx: address:%d did not require an update\r\n", u16Address + index);
#endif // E_25LCXX_DEBUG_MODE
        }
    }

    return 0;                                                                       /**< return success */

}

/**
 * @brief basic erase page example
 * @param[in] u16Page is the page to erase data
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    Page erase instruction will erase all bits (FFh) inside the given page.
 */
uint8_t e_25LCxx_basic_erase_page(uint16_t u16Page)
{
    uint16_t pageSize;

    if(E_25LCxx_erase_page(&e_25LCxx_handler, u16Page))                                       /**< begin erasing process */
    {
        return 1;                                                                            /**< return failed error */
    }

    if(e_25LCxx_basic_get_wip_status())                                                      /**< check write in progress status */
    {
        return 1;                                                                            /**< return error */
    }
    return 0;                                                                                /**< return success */
}

/**
 * @brief basic sector erase example
 * @param[in] startAddr is the sector start address
 * @param[in] endAddr is the sector end address
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    sector erase instruction will erase all bits (FFh) inside the given sector address
 */
uint8_t e_25LCxx_basic_erase_sector(uint16_t u16StartAddr, uint16_t u16EndAddr)
{
    uint16_t addBuffer[2];
    uint16_t addrIndex;
    const uint8_t data = 0xff;

    addBuffer[0] = u16StartAddr;
    addBuffer[1] = u16EndAddr;


    if(e_25LCxx_handler.u8Device_type != E_25LC512_VARIANT)                                     /**< currently only the 25LC512 support chip erase command */
    {
        for(addrIndex = u16StartAddr; addrIndex < ( u16EndAddr + 1); addrIndex++)
        {
            if(E_25LCxx_check_bp_before_write(&e_25LCxx_handler, addrIndex) != 0)
			{
				return 1;
			}
            if(e_25LCxx_basic_write_byte(addrIndex, (uint8_t *)&data, 1) != NULL)
            {
                break;
                return 1;           /**< return error */
            }
        }
        return 0;
    }

    if(E_25LCxx_erase_sector(&e_25LCxx_handler, (uint16_t *)addBuffer))                      /**< begin erasing process */
    {
        return 1;                                                                           /**< return failed error */
    }

    if(e_25LCxx_basic_get_wip_status())                                                     /**< check write in progress status */
    {
        return 1;                                                                           /**< return error */
    }
    return 0;                                                                               /**< return success */
}

/**
 * @brief basic chip erase example
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    chip erase instruction will erase all data (FFh) in the memory
            except for the block protected array.
 */
uint8_t e_25LCxx_basic_chip_erase(void)
{
    uint16_t index = 0;
    uint8_t data = 255;

    if(e_25LCxx_handler.u8Device_type != E_25LC512_VARIANT)                                     /**< currently only the 25LC512 support chip erase command */
    {
        for(index = 0; index < e_25LCxx_basic_get_eeprom_legth(); index++)
        {
            if(E_25LCxx_check_bp_before_write(&e_25LCxx_handler, index) != 0)
			{
				return 1;
			}
            if(e_25LCxx_basic_write_byte(index, (uint8_t*)&data, 1) != NULL)
            {
                break;
                return 1;         /* return error */
            }
        }
        return 0;
    }

    if(E_25LCxx_erase_chip(&e_25LCxx_handler))                                               /**< begin erasing process */
    {
        return 1;                                                                           /**< return failed error */
    }

    if(e_25LCxx_basic_get_wip_status())                                                     /**< check write in progress status */
    {
        return 1;                                                                           /**< return error */
    }
    return 0;                                                                               /**< return success */
}

/**
 * @brief basic set deep power down mode example
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note      All instructions given during Deep Power-Down mode are ignored except the Read Electronic Signature command
 */
uint8_t e_25LCxx_basic_set_deep_power_down_mode(void)
{
    if(E_25LCxx_set_deep_power_down_mode(&e_25LCxx_handler))
    {
        return 1;                                                                           /**< return error */
    }
    return 0;                                                                               /**< return success */
}

/**
 * @brief basic get manufacture id (read electronic signature) example
 * @param[out] *pId point to the manufacture ID
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_manufacture_id(uint8_t *pId)
{

    if(E_25LCxx_get_manufacture_id(&e_25LCxx_handler, (uint8_t *)pId))                       /**< Read manufacturer ID */
    {
        return 1;                                                                           /**< return error */
    }
    return 0;                                                                               /**< return success */
}

/**
 * @brief basic get eeprom length in byte
 * @return status code
 *          - 1 failed
 * @note    none
 */
uint32_t e_25LCxx_basic_get_eeprom_legth(void)
{
    static uint32_t eeprom_size;
    if(E_25LCxx_get_legth(&e_25LCxx_handler, (uint16_t *)&eeprom_size))
    {
        a_e25lcxx_print_error_msg(&e_25LCxx_handler, "get memory length");
        return 1;
    }
    return eeprom_size;
}

/**
 * @brief This function check if writing is not in progress
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_wip_status(void)
{
    uint8_t writeInProgess_status;
    uint32_t timeOut;

    E_25LCxx_get_wip_status(&e_25LCxx_handler, &writeInProgess_status);                       /**< read write-in-progress status bit */
    while((writeInProgess_status == _25LCxx_BUSY ) && (timeOut < WRITE_TIMEOUT))              /**< wait until writing process is complete */
    {
        if(E_25LCxx_get_wip_status(&e_25LCxx_handler, &writeInProgess_status) != 0)
        {
            break;
            return 1;                                                                        /**< return failed to read the wip status bit */
        }
        timeOut++;
    }
    return 0;                                                                                /**< return success */
}

/**
 * @brief This function reads the write enable latch status
*  @param[out] *pStatus point to the status to read
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_wel_status(uint8_t *pStatus)
{
    if(E_25LCxx_get_wel_status(&e_25LCxx_handler,(uint8_t *)pStatus) != 0)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief This function set a protected block of the memory from being written to
*  @param[out] block is the portion to protected
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_set_bp_status(E_25LCxx_block_protection_status_t block)
{
    if(E_25LCxx_set_bp_status(&e_25LCxx_handler, block) != 0)
    {
        return 1;                                            /**< return failed error */
    }
    return 0;                                                /**< return success */
}

/**
 * @brief This function get a protected block status
*  @param[out] *pBlock is the portion to protected
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_bp_status(E_25LCxx_block_protection_status_t *pBlock)
{
    if(E_25LCxx_get_bp_status(&e_25LCxx_handler, (uint8_t *)pBlock) != 0)
    {
        return 1;											 /**< return failed error */
    }
    return 0;                                                /**< return success */

}

/**
 * @brief     This function get fetch the protect enable status
 * @param[out] *pEnable point to the boolean status
 * @return    status code
 *            - 0 success
 *            - 1 get wpen failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t e_25LCxx_basic_get_write_protect_enable(E_25LCxx_bool_t *pEnable)
{
    if(E_25LCxx_get_write_protect_enable(&e_25LCxx_handler, (E_25LCxx_bool_t *)pEnable) != 0)
    {
        return 1;                                                             /**< return failed error */
    }
    return 0;                                                               /**< return success */
}

/**
* @brief  This function returns the eeprom properties
* @param[out] pMemorySize point to the total size of the chip in bytes
* @param[out] pFree_space point to the available free space on the chip in bytes
* @param[out] pUsed_space point to the use space on the memory in bytes
* @return	status code
 *          - 0 success
 *          - 1 failed
* @note		this routine reads the entire memory, assumes that address that reads 0xff are free
*/
uint8_t e_25LCxx_basic_get_memory_properties(E_25LCxx_max_addr_t *pMemorySize, uint16_t *pFree_space, uint16_t *pUsed_space)
{
	uint16_t index;
	static uint16_t counter = 0;
	static uint8_t dataRead = 0;

	for(index = 0; index < e_25LCxx_basic_get_eeprom_legth(); index++){
		if(e_25LCxx_basic_read_byte(index, (uint8_t *)&dataRead, 1) != 0){
			return 1;			/**< failed to read memory address*/
		}
		if(dataRead == 0xff){
			counter++;
		}
	}
    *pMemorySize = e_25LCxx_basic_get_eeprom_legth();
	*pFree_space = counter;
	*pUsed_space = e_25LCxx_basic_get_eeprom_legth() - counter;

	return 0;		/**< success */
}

