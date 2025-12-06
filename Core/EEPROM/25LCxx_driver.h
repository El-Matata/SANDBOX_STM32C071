
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
 * File:   25LCxx_driver.h
 * Author: Cedric Akilimali
 *
 * Created on August 13, 2022, 3:43 PM
 */

#ifndef _25LCXX_DRIVER_H_INCLUDED
#define _25LCXX_DRIVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//#define E_25LCXX_DEBUG_MODE              /**< enables all printout on the code*/

/**
* @defgroup driver_25LCxx 25LCxx driver function
* @brief 25LCxx driver modules
* @{
*/

/**
 * @addtogrouup 25LCxx_base_driver
 * @{
 */

/*Control Register */

#define E_25LCXXX_READ_REG                  0x03    /**< Read data from memory array beginning at selected address */
#define E_25LCXXX_WRITE_REG                 0x02    /**< Write data to memory array beginning at selected address */
#define E_25LCXXX_WRDI_REG                  0x04    /**< Reset the write enable latch (disable write operations) */
#define E_25LCXXX_WREN_REG                  0x06    /**< Set the write enable latch (enable write operations) */
#define E_25LCXXX_RDSR_REG                  0x05    /**< Read STATUS register */
#define E_25LCXXX_WRSR_REG                  0x01    /**< Write STATUS register */


/* status Register Mask */

#define E_25LCXXX_WIP_MASK                  0x01      /**< Write-In-Process Mask */
#define E_25LCXXX_WEL_MASK                  0x02      /**< Write enable protection Mask */
#define E_25LCXXX_BP_MASK                   0x0C      /**< Block Protection Mask */
#define E_25LCXXX_WPEN_MASK                 0x80      /**< Write protect enable Mask */

/* command address */
#define E_25LCXXX_PAGE_ERASE_CMD            0x42      /**< page erase command  */
#define E_25LCXXX_SECTOR_ERASE_CMD          0xD8      /**< sector erase command */
#define E_25LCXXX_CHIP_ERASE_CMD            0xC7      /**< chip erase command*/
#define E_25LCXXX_DEEP_POWER_DOWN_MODE      0xB9      /**< deep power-down mode command */
#define E_25LCXXX_RELEASE_DPD_READ_ID       0xAB      /**< release from deep power-down and read electronic signature command */

/* utility variable */
#define DUMMY_DATA          0x00    /**< dummy data for spi read */
#define SLAVE_SELECT        0x00    /**< spi slave select pin level */
#define SLAVE_ASSERT        0x01    /**< spi slave assert pin level */
#define WRITE_TIMEOUT       100000 /**< eeprom write timeout */


/**
 * @brief 25LCxx variant enumeration
 */
typedef enum
{
    E_25LC080x_VARIANT = 1,       /**< the 25LC08xx/25AA08xx is the 8Kb variant */
    E_25LC160x_VARIANT = 2,       /**< the 25LC16xx/25AA16xx is the 16Kb variant */
    E_25LC320x_VARIANT = 3,       /**< the 25LC32xx/25AA32xx is the 32Kb variant */
    E_25LC640x_VARIANT = 4,       /**< the 25LC64xx/25AA64xx is the 64Kb variant */
    E_25LC128_VARIANT  = 5,       /**< the 25LC128xx/25AA128xx is the 128Kb variant */
    E_25LC256_VARIANT  = 6,       /**< the 25LC256xx/25AA256xx is the 256Kb variant */
    E_25LC512_VARIANT  = 7        /**< the 25LC512xx/25AA512xx is the 512Kb variant */
} E_25LCxx_variant_t;

/**
* @brief 25LCxx maximum address length enumeration
*/
typedef enum
{
    E_25LC080x_MAX_ADD = 1023U,       /**< the 25LC08xx/25AA08xx is the 8Kb (1024 byte) */
    E_25LC160x_MAX_ADD = 2047U,       /**< the 25LC16xx/25AA16xx is the 16Kb (2048 byte) */
    E_25LC320x_MAX_ADD = 4095U,       /**< the 25LC32xx/25AA32xx is the 32Kb (4096 byte) */
    E_25LC640x_MAX_ADD = 8191U,       /**< the 25LC64xx/25AA64xx is the 64Kb (8192 byte) */
    E_25LC128_MAX_ADD = 16383U,       /**< the 25LC128xx/25AA128xx is the 128Kb (16384 byte) */
    E_25LC256_MAX_ADD = 32767U,       /**< the 25LC256xx/25AA256xx is the 256Kb (32768 byte) */
    E_25LC512_MAX_ADD = 65535U        /**< the 25LC512xx/25AA512xx is the 512Kb (65536 byte) */
}E_25LCxx_max_addr_t;

/**
* @brief 25LCxx page size enumeration
*/
typedef enum
{
    E_25LCXX_PAGE_SIZE_16_BYTE  = 16,         /**< Eeprom page size 16 byte */
    E_25LCXX_PAGE_SIZE_32_BYTE  = 32,         /**< Eeprom page size 32 byte */
    E_25LCXX_PAGE_SIZE_64_BYTE  = 64,         /**< Eeprom page size 64 byte */
    E_25LCXX_PAGE_SIZE_128_BYTE = 128         /**< Eeprom page size 128 byte */
}E_25LCxx_page_size_t;

/**
 * @brief 25LCxx boolean enumeration
 */
typedef enum
{
    E_25LCxx_BOOL_FALSE = 0x00, /**< Boolean state false */
    E_25LCxx_BOOL_TRUE = 0x01   /**< Boolean state true */
} E_25LCxx_bool_t;

/**
* @brief 25LCxx Write-In-Process enumeration
*/
typedef enum
{
    _25LCxx_NOT_BUSY = 0x00,     /**< 25LCXXX is busy with a write operation */
    _25LCxx_BUSY     = 0x01      /**< 25LCXXX is not busy with a write operation  */
} E_25LCxx_write_in_process_status_t;

/**
* @brief 25LCxx Write Enable Latch enumeration
*/
typedef enum
{
    E_25LCxx_PROHIBIT_WRITE = 0x00,       /**< the latch allows writes to the array */
    E_25LCxx_ALLOW_WRITE = 0x01           /**< the latch prohibits writes to the array */
} E_25LCxx_write_en_latch_staus_t;

/**
* @brief 25LCxx Block Protection enumeration
*/
typedef enum
{
    E_25LCxx_BP00 = 0x00,     /**< Array Address Write-Protected(None)/ Array Addresses Unprotected (All)*/
    E_25LCxx_BP01 = 0x01,     /**< Array Address Write-Protected(Upper 1/4)/ Array Addresses Unprotected (Upper 3/4) */
    E_25LCxx_BP10 = 0x02,     /**< Array Address Write-Protected(Upper 1/2)/ Array Addresses Unprotected (Upper 1/2) */
    E_25LCxx_BP11 = 0x03      /**< Array Address Write-Protected(All)/ Array Addresses Unprotected (None) */
} E_25LCxx_block_protection_status_t;

/**
* @brief data read out enumeration
*/
union
{
    uint8_t buffer[8];                /**< buffer to hold data when eeprom_get is called */
    uint32_t data;          /**< */
}static dataReadOut;


/**
 * @brief 25LCxx handle structure definition
 */
typedef struct E_25LCxx_handle_s
{
    uint8_t(*spi_init)(void);                                           /**< point to a spi init function address */
    uint8_t(*spi_deinit)(void);                                         /**< point to a spi deinit function address */
    uint8_t(*spi_write)(uint16_t u16Reg, uint32_t *pBuf,  size_t iLen); /**< point to a spi write function address */
    uint8_t(*spi_read)(uint16_t u16Reg, uint32_t *pBuf,  size_t iLen);  /**< point to a spi read function address */
    uint8_t(*gpio_write)(uint8_t u8State);                              /**< point to gpio write for spi slave write enable or disable */
    uint8_t(*chip_select)(uint8_t u8State);                             /**< point to chip select for spi slave select and assert */
    void (*delay_ms)(uint32_t u32Ms);                                   /**< point to a delay_ms function address */
    void(*debug_print)(char *fmt, ...);                                 /**< point to a debug_print function address */
    uint8_t u8Device_type;                                               /**< device type */
    uint8_t iPage_size;                                                  /**< Eeprom page size in byte */
    uint8_t u8Inited;                                                    /**< inited flag */
} E_25LCxx_handle_t;
/**
 * @brief 25LCxx information structure definition
 */
typedef struct E_25LCxx_info_s
{
    char chip_name[10];             /**< chip name */
    char manufacturer_name[25];     /**< manufacturer name */
    char interface[8];              /**< chip interface name */
    float supply_voltage_min_v;     /**< chip min supply voltage */
    float supply_voltage_max_v;     /**< chip max supply voltage */
    float max_current_ma;           /**< chip max current */
    float temperature_min;          /**< chip min operating temperature */
    float temperature_max;          /**< chip max operating temperature */
    float driver_version;           /**< driver version */
} E_25LCxx_info_t;

/**
 * @}
 */

 /**
 * @defgroup 25LCxx_link_driver 25LCxx_ link driver function
 * @brief    25LCxx link driver modules
 * @ingroup  25LCxx driver
 * @{
 */


/**
 * @brief     initialize 25LCxx_handle_t structure
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] STRUCTURE is 25LCxx_handle_t
 * @note      none
 */
#define DRIVER_25LCXX_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to 25LCXX handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_SPI_INIT(HANDLE, FUC)              (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_SPI_DEINIT(HANDLE, FUC)            (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a spi_write function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_SPI_WRITE(HANDLE, FUC)             (HANDLE)->spi_write = FUC


/**
 * @brief     link spi_read function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a spi_read function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_SPI_READ(HANDLE, FUC)              (HANDLE)->spi_read = FUC

/**
 * @brief     link gpio write function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a gpio_write function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_GPIO_WRITE(HANDLE, FUC)            (HANDLE)->gpio_write = FUC

/**
 * @brief     This function link chip select and assert function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a gpio_write function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_CHIP_SELECT(HANDLE, FUC)            (HANDLE)->chip_select = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to 25LCxx handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_25LCXX_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup 25LCxx_base_driver 25LCxx base driver function
 * @brief    25LCxx base driver modules
 * @ingroup  25LCxx_driver
 * @{
 */

 /**
 * @brief      This function get chip's information
 * @param[out] *info points to 25LCxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t E_25LCxx_info(E_25LCxx_info_t *pInfo);

/**
 * @brief     This function initialize the chip
 * @param[in] *handle points to 25LCxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t E_25LCxx_init(E_25LCxx_handle_t *pHandle);

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
uint8_t E_25LCxx_deinit(E_25LCxx_handle_t *pHandle);

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
uint8_t E_25LCxx_set_variant(E_25LCxx_handle_t *pHandle, E_25LCxx_variant_t variant);

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
uint8_t E_25LCxx_get_variant(E_25LCxx_handle_t *pHandle, E_25LCxx_variant_t *pVariant);

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
uint8_t E_25LCxx_set_page_size(E_25LCxx_handle_t *pHandle, E_25LCxx_page_size_t iSize);


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
uint8_t E_25LCxx_get_page_size(E_25LCxx_handle_t *pHandle, E_25LCxx_page_size_t *pSize);


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
uint8_t E_25LCxx_get_wip_status(E_25LCxx_handle_t *pHandle, E_25LCxx_write_in_process_status_t *pStatus);

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
uint8_t E_25LCxx_get_wel_status(E_25LCxx_handle_t *pHandle, E_25LCxx_write_en_latch_staus_t *pStatus);

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
uint8_t E_25LCxx_set_bp_status(E_25LCxx_handle_t *pHandle, E_25LCxx_block_protection_status_t status);

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
uint8_t E_25LCxx_get_bp_status(E_25LCxx_handle_t *pHandle, E_25LCxx_block_protection_status_t *pStatus);


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
uint8_t E_25LCxx_set_write_protect_enable(E_25LCxx_handle_t *pHandle, E_25LCxx_bool_t enable);

/**
 * @brief     This function get write protect enable status
 * @param[in] *pHandle points to 25LCxx handle structure
 * @param[out] *pEnable point to the boolean status
 * @return    status code
 *            - 0 success
 *            - 1 get wpen failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t E_25LCxx_get_write_protect_enable(E_25LCxx_handle_t *pHandle, E_25LCxx_bool_t *pEnable);

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
 *            - 4 invalid address
 *            - 5 attemp to write a protected block array
 *            - 6 data length is larger than page size
 * @note      none
 */
uint8_t E_25LCxx_write_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint8_t *pBuf, uint16_t u16Length);

/**
 * @brief     This function read n byte to eeprom
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] addr is the eeprom address to read
 * @param[out] *buf points to data buffer read
 * @param[in] length is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 invalid address
 * @note      none
 */
uint8_t E_25LCxx_read_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint8_t *pBuf, uint16_t u16Length);

/**
 * @brief     This function writes data larger than a byte > 255 (equivalent to eeprom.put on arduino)
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
 * @note      none
 */

uint8_t E_25LCXX_put_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, unsigned long long *pBuf, uint8_t u16Length);

/**
 * @brief     This function reads data larger than a byte > 255 (equivalent to eeprom.get on arduino)
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
 * @note      none
 */

uint8_t E_25LCXX_get_byte(E_25LCxx_handle_t *pHandle, uint16_t u16Addr, uint32_t *pBuf, uint8_t u16Length);

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
uint8_t E_25LCxx_erase_page(E_25LCxx_handle_t *pHandle, uint16_t u16PageNumber);

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
uint8_t E_25LCxx_erase_sector(E_25LCxx_handle_t *pHandle, uint16_t *pSector_addr);

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
uint8_t E_25LCxx_erase_chip(E_25LCxx_handle_t *pHandle);

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
uint8_t E_25LCxx_set_deep_power_down_mode(E_25LCxx_handle_t *pHandle);

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
uint8_t E_25LCxx_get_manufacture_id(E_25LCxx_handle_t *pHandle, uint8_t *pId);

/**
 * @brief This function runs basic checks before writing
 * @param[in] *handle points to 25LCxx handle structure
 * @param[in] u16Address is the address to write
 * @return status code
 *          - 0 success
 *          - 1 failed
 * @note    none
 */
uint8_t E_25LCxx_check_bp_before_write(E_25LCxx_handle_t *pHandle, uint16_t u16Address);


/**
 * @brief This function validate the address to write or read
 * @param[in] *pHandle point to the handle structure
 * @param[in] u16Address is the address to validate
 * @return status code
 *          - 0 success (validated)
 *          - 1 failed validate
 * @note    none
 */
uint8_t E_25LCxxx_validate_address(E_25LCxx_handle_t *pHandle, E_25LCxx_max_addr_t u16Address);

/**
 * @brief This function checks to make that we're not trying  to write beyond page boundary
 * @param[in] *pHandle point to the handle structure
 * @param[in] u16Address is the address to validate
 * @param[in] u16Length is data length
 * @return status code
 *          - 0 success (validated)
 *          - 1 failed to validate
 *          - 2 handle is NULL
 *          - 3 handle is not initialized
 * @note    none
 */
uint8_t E_25LCXX_validate_page_boundary(E_25LCxx_handle_t *pHandle, uint16_t u16Address, uint16_t u16Length);

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
uint8_t E_25LCxxx_validate_page(E_25LCxx_handle_t *pHandle, uint16_t u16Page, uint16_t *pStartAddr);

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
uint8_t E_25LCxx_get_legth(E_25LCxx_handle_t *pHandle, E_25LCxx_max_addr_t *pLength);


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
uint8_t E_25LCxx_set_reg(E_25LCxx_handle_t *pHandle, uint16_t u16Reg, uint32_t *pBuf, size_t iLength);


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
uint8_t E_25LCxx_get_reg(E_25LCxx_handle_t *pHandle, uint16_t u16Reg, uint32_t *pBuf, size_t iLength);

/**
* @}
*/

/**
 * @}
 */

#endif // 25LCXX_DRIVER_H_INCLUDED
