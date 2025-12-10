#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

#include "spi.h"


#define EEPROM_READ_REG                  	0x03    /**< Read data from memory array beginning at selected address */
#define EEPROM_WRITE_REG                 	0x02    /**< Write data to memory array beginning at selected address */
#define EEPROM_WRDI_REG                  	0x04    /**< Reset the write enable latch (disable write operations) */
#define EEPROM_WREN_REG                  	0x06    /**< Set the write enable latch (enable write operations) */
#define EEPROM_RDSR_REG                  	0x05    /**< Read STATUS register */
#define EEPROM_WRSR_REG                  	0x01    /**< Write STATUS register */

/* command address */
#define EEPROM_PAGE_ERASE_CMD            	0x42      /**< page erase command  */
#define EEPROM_SECTOR_ERASE_CMD          	0xD8      /**< sector erase command */
#define EEPROM_CHIP_ERASE_CMD            	0xC7      /**< chip erase command*/
#define EEPROM_DEEP_POWER_DOWN_MODE      	0xB9      /**< deep power-down mode command */
#define EEPROM_RELEASE_DPD_READ_ID       	0xAB      /**< release from deep power-down and read electronic signature command */

#define EEPROM_PAGE_SIZE 128    // The specific page size of the EEPROM
#define EEMPROM_NUM_PAGES 8     // 1024 / 128 = 8 pages
#define EEPROM_MAX_ADDRESS 			65535U 	  /*512Kb = 65535kB*/
#define PAGE_0_ADDRESS 0x0000 // Start of the first page

#define EEPROM_CS_PORT  EEPROM_NCS_GPIO_Port
#define EEPROM_CS_PIN   EEPROM_NCS_Pin

#define EEPROM_WIP_BIT_MASK 0x01    // Mask to check Bit 0 (Write In Progress)
#define WRITE_TIMEOUT_MS 5 // 500ms should be safe for most sector/page erases
#define ERASE_TIMEOUT_MS 500 // 500ms should be safe for most sector/page erases
#define SECTOR_ERASE_TIMEOUT_MS 500  // 500ms should be safe for most sectors (e.g., 4kB/64kB)
#define CHIP_ERASE_TIMEOUT_MS 5000 // 5000ms (5 seconds) for safety, as chip erase is the slowest

#endif // EEPROM_H_INCLUDED


/**
  * @brief  Writes a single byte to the SPI EEPROM at the specified address.
  * @param  mem_address: Internal memory address (typically 16-bit or 24-bit).
  * @param  data: The byte of data to write.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Write_Byte(uint16_t mem_address, uint8_t data);

/**
  * @brief  Reads a single byte from the SPI EEPROM at the specified address.
  * @param  mem_address: Internal memory address.
  * @param  data: Pointer to the variable to store the read data.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Read_Byte(uint16_t mem_address, uint8_t *data);

/**
  * @brief  Writes a page (128 bytes) to the SPI EEPROM.
  * @param  start_address: The starting internal memory address.
  * @param  pData: Pointer to the 128-byte data buffer to write.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Page_Write(uint16_t start_address, uint8_t *pData);

/**
  * @brief  Reads a page (128 bytes) from the SPI EEPROM.
  * @param  start_address: The starting internal memory address.
  * @param  pData: Pointer to the 128-byte buffer to store the read data.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Page_Read(uint16_t start_address, uint8_t *pData);

/**
  * @brief  Sends the Write Enable (WREN) instruction to the EEPROM.
  * Required before any WRITE or ERASE operation.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Write_Enable(void);

/**
  * @brief  Sends the Write Disable (WRDI) instruction to the EEPROM.
  * Explicitly protects the memory.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Write_Disable(void);

/**
  * @brief  Erases a single page in the EEPROM starting at the specified address.
  * @param  start_address: The starting address of the page to erase.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Page_Erase(uint16_t start_address);

/**
  * @brief  Erases an entire sector (large block) in the EEPROM.
  * @param  start_address: The starting address of the sector to erase (must be sector-aligned).
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Sector_Erase(uint16_t start_address);

/**
  * @brief  Erases the entire content of the EEPROM chip.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Chip_Erase(void);

/**
  * @brief  Reads the current value of the EEPROM's Status Register.
  * @param  pStatus: Pointer to a uint8_t to store the read status byte.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Read_Status_Register(uint8_t *pStatus);

/**
  * @brief  Polls the WIP bit until the memory operation is complete.
  * @param  Timeout: Maximum time (in milliseconds) to wait for the operation to finish.
  * @retval HAL status (HAL_OK on success, HAL_TIMEOUT if WIP never clears).
  */
HAL_StatusTypeDef EEPROM_Wait_For_Write_Completion(uint32_t Timeout);

/**
  * @brief  Sends the Deep Power Down (DPD) command to the EEPROM.
  * Puts the chip into its lowest power state.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Deep_Power_Down(void);

/**
  * @brief  Sends the Release from Deep Power Down (RDPD) command.
  * Wakes the chip up and allows subsequent commands.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Release_Deep_Power_Down(void);

void EEPROM_Write1K(SPI_HandleTypeDef *hspi, uint32_t StartAddr, uint8_t *Data, uint16_t Length);

/**
 * @brief Reads a specified length of data from the EEPROM starting at StartAddr.
 * * @param hspi Pointer to the SPI Handle (e.g., &hspi1).
 * @param StartAddr The 24-bit memory address to start reading from.
 * @param Data Pointer to the buffer where the received data will be stored.
 * @param Length The number of bytes to read (e.g., 1024).
 */
void EEPROM_Read1K(SPI_HandleTypeDef *hspi, uint32_t StartAddr, uint8_t *Data, uint16_t Length);
