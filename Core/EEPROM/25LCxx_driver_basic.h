
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
 * File:   25LCxx_driver_basic.h
 * Author: Cedric Akilimali
 *
 * Created on August 16, 2022, 4:28 PM
 */

#ifndef _25LCXX_DRIVER_BASIC_H_INCLUDED
#define _25LCXX_DRIVER_BASIC_H_INCLUDED

#include "25LCxx_driver_interface.h"

/**
 * @brief basic example initialize
 * @param[in] DeviceVariant is the device type
 * @param[in] pageSize is the page size in byte
 * @return status code
 *          - 0 success
 *          - 1 initialize failed
 * @note    none
 */

uint8_t e_25LCxx_basic_initialize(E_25LCxx_variant_t DeviceVariant, E_25LCxx_page_size_t pageSize);

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
uint8_t e_25LCxx_basic_write_byte(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size);

/**
 * @brief basic function to write number greater than a byte (equivalent to eeprom.put on Arduino)
 * @param[in] u16Address is the address to write
 * @param[in] u16Size is the data size
 * @param[in] *pBuffer point to data be written
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_put_byte(uint16_t u16Address, unsigned long long *pBuffer, uint16_t u16Size);

/**
 * @brief basic read byte example
 * @param[in] u16Address is the address to write
 * @param[out] *pBuffer point to data read
 * @param[in] u16Size is the data size or length
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */

uint8_t e_25LCxx_basic_read_byte(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size);

/**
 * @brief basic function to read data greater than a byte
 * @param[in] u16Address is the address to write
 * @param[out] *pBuffer point to data read
 * @param[in] u16Size is the data size
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_byte(uint16_t u16Address, uint32_t *pBuffer, uint16_t u16Size);

/**
 * @brief This function write a byte to the EEPROM. The value is written only if differs from the one already saved at the same address.
 * @param[in] u16Address is the address to write
 * @param[in] *pBuffer point to data write
 * @param[in] u16Size is the data size
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */

uint8_t e_25LCxx_basic_update(uint16_t u16Address, uint8_t *pBuffer, uint16_t u16Size);

/**
 * @brief basic erase page example
 * @param[in] u16Page is the page to erase data
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    Page erase instruction will erase all bits (FFh) inside the given page.
 */
uint8_t e_25LCxx_basic_erase_page(uint16_t u16Page);

/**
 * @brief basic sector erase example
 * @param[in] startAddr is the sector start address
 * @param[in] u16EndAddr is the sector end address
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    sector erase instruction will erase all bits (FFh) inside the given sector address
 */
uint8_t e_25LCxx_basic_erase_sector(uint16_t u16StartAddr, uint16_t u16EndAddr);

/**
 * @brief basic chip erase example
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    chip erase instruction will erase all data (FFh) in the memory
            except for the block protected array.
 */
uint8_t e_25LCxx_basic_chip_erase(void);



/**
 * @brief basic set deep power down mode example
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note      All instructions given during Deep Power-Down mode are ignored except the Read Electronic Signature command
 */
uint8_t e_25LCxx_basic_set_deep_power_down_mode(void);


/**
 * @brief basic get_manufacture id (read electronic signature) example
 * @param[out] *pId point to the manufacture ID
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_manufacture_id(uint8_t *pId);

/**
 * @brief basic get eeprom length in byte
 * @return status code
 *          - 1 failed
 * @note    none
 */
uint32_t e_25LCxx_basic_get_eeprom_legth(void);

/**
 * @brief This function check if writing is not in progress
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_wip_status(void);

/**
 * @brief This function reads the write enable latch status
*  @param[out] *pStatus point to the status to read
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_wel_status(uint8_t *pStatus);

/**
 * @brief This function set a protected block of the memory from being written to
*  @param[out] block is the portion to protected
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_set_bp_status(E_25LCxx_block_protection_status_t block);

/**
 * @brief This function get a protected block status
*  @param[out] *pBlock is the portion to protected
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t e_25LCxx_basic_get_bp_status(E_25LCxx_block_protection_status_t *pBlock);

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
uint8_t e_25LCxx_basic_get_write_protect_enable(E_25LCxx_bool_t *pEnable);

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
uint8_t e_25LCxx_basic_get_memory_properties(E_25LCxx_max_addr_t *pMemorySize, uint16_t *pFree_space, uint16_t *pUsed_space);


#endif // 25LCXX_DRIVER_BASIC_H_INCLUDED
