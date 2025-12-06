#include "EEPROM.h"

void EEPROM_CS_Select(void)
{
    HAL_GPIO_WritePin(EEPROM_CS_PORT, EEPROM_CS_PIN, GPIO_PIN_RESET);
}

// De-assert Chip Select (End SPI Transaction)
void EEPROM_CS_Deselect(void)
{
    HAL_GPIO_WritePin(EEPROM_CS_PORT, EEPROM_CS_PIN, GPIO_PIN_SET);
}


HAL_StatusTypeDef EEPROM_Write_Byte(uint16_t mem_address, uint8_t data)
{
    HAL_StatusTypeDef status;
    uint8_t tx_buffer[4]; // Command (1), Address MSB (1), Address LSB (1), Data (1)

    // 1. Send Write Enable Latch (WREN) command
    EEPROM_CS_Select();
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_WREN_REG}, 1, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    if (status != HAL_OK) return status;

    // 2. Prepare and send WRITE command, Address, and Data
    EEPROM_CS_Select();

    // Command and Address (Assuming 16-bit address for this example)
    tx_buffer[0] = EEPROM_WRITE_REG;
    tx_buffer[1] = (uint8_t)(mem_address >> 8);  // MSB
    tx_buffer[2] = (uint8_t)(mem_address & 0xFF);// LSB

    // Data byte
    tx_buffer[3] = data;

    // Transmit all four bytes at once
    status = HAL_SPI_Transmit(&hspi1, tx_buffer, 4, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    // 3. Wait for the internal write cycle to complete (Check your datasheet!)
    // For production code, use a function that polls the Status Register (RDSR)
    // to check the Write In Progress (WIP) bit.
    HAL_Delay(5);

    return status;
}


HAL_StatusTypeDef EEPROM_Read_Byte(uint16_t mem_address, uint8_t *data)
{
    HAL_StatusTypeDef status;
    uint8_t tx_buffer[3]; // Command (1), Address MSB (1), Address LSB (1)

    // 1. Select the EEPROM
    EEPROM_CS_Select();

    // Command and Address (Assuming 16-bit address)
    tx_buffer[0] = EEPROM_READ_REG;
    tx_buffer[1] = (uint8_t)(mem_address >> 8);  // MSB
    tx_buffer[2] = (uint8_t)(mem_address & 0xFF);// LSB

    // 2. Send the READ command and address bytes (3 bytes)
    status = HAL_SPI_Transmit(&hspi1, tx_buffer, 3, HAL_MAX_DELAY);

    if (status != HAL_OK) {
        EEPROM_CS_Deselect();
        return status;
    }

    // 3. Receive the data byte (1 byte)
    // The Master (STM32) sends dummy clock cycles, and the Slave (EEPROM) shifts out the data.
    status = HAL_SPI_Receive(&hspi1, data, 1, HAL_MAX_DELAY);

    // 4. De-select the EEPROM
    EEPROM_CS_Deselect();

    return status;
}

HAL_StatusTypeDef EEPROM_Page_Write(uint16_t start_address, uint8_t *pData)
{
    HAL_StatusTypeDef status;

    // Check if the start address is aligned to a page boundary (optional, but good practice)
    if (start_address % EEPROM_PAGE_SIZE != 0) {
        // Handle error or adjust address
        return HAL_ERROR;
    }

    // --- 1. Send Write Enable Latch (WREN) command ---
    EEPROM_CS_Select();
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_WREN_REG}, 1, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    if (status != HAL_OK) return status;

    // --- 2. Prepare Command and Address ---
    uint8_t header[3];
    header[0] = EEPROM_WRITE_REG;
    header[1] = (uint8_t)(start_address >> 8);  // MSB
    header[2] = (uint8_t)(start_address & 0xFF);// LSB

    // --- 3. Send Command, Address, and Page Data ---
    EEPROM_CS_Select();

    // Send the 3-byte header (WRITE command + 16-bit Address)
    status = HAL_SPI_Transmit(&hspi1, header, 3, HAL_MAX_DELAY);

    // Send the 128-byte data buffer immediately after
    if (status == HAL_OK) {
        status = HAL_SPI_Transmit(&hspi1, pData, EEPROM_PAGE_SIZE, HAL_MAX_DELAY);
    }

    EEPROM_CS_Deselect();

    // --- 4. Wait for the internal write cycle to complete (MANDATORY) ---
    // Use Status Register Polling (RDSR) for optimal performance,
    // but a delay is the simpler implementation for testing.
    HAL_Delay(5);

    return status;
}

HAL_StatusTypeDef EEPROM_Page_Read(uint16_t start_address, uint8_t *pData)
{
    HAL_StatusTypeDef status;

    // --- 1. Prepare Command and Address ---
    uint8_t header[3];
    header[0] = EEPROM_READ_REG;
    header[1] = (uint8_t)(start_address >> 8);  // MSB
    header[2] = (uint8_t)(start_address & 0xFF);// LSB

    // --- 2. Send Command and Address (Transmit Phase) ---
    EEPROM_CS_Select();

    // Send the 3-byte header
    status = HAL_SPI_Transmit(&hspi1, header, 3, HAL_MAX_DELAY);

    if (status != HAL_OK) {
        EEPROM_CS_Deselect();
        return status;
    }

    // --- 3. Receive the 128-byte data buffer ---
    // The STM32 transmits dummy data while the EEPROM streams its memory contents.
    status = HAL_SPI_Receive(&hspi1, pData, EEPROM_PAGE_SIZE, HAL_MAX_DELAY);

    // --- 4. De-select the EEPROM ---
    EEPROM_CS_Deselect();

    return status;
}

HAL_StatusTypeDef EEPROM_Write_Enable(void)
{
    HAL_StatusTypeDef status;

    EEPROM_CS_Select();
    // Send the single-byte WREN command
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_WREN_REG}, 1, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    return status;
}


HAL_StatusTypeDef EEPROM_Write_Disable(void)
{
    HAL_StatusTypeDef status;

    EEPROM_CS_Select();
    // Send the single-byte WRDI command
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_WRDI_REG}, 1, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    return status;
}

HAL_StatusTypeDef EEPROM_Page_Erase(uint16_t start_address)
{
    HAL_StatusTypeDef status;

    // 1. Send Write Enable (MANDATORY)
    if (EEPROM_Write_Enable() != HAL_OK) return HAL_ERROR;

    // 2. Prepare Command and Address
    uint8_t header[3];
    header[0] = EEPROM_PAGE_ERASE_CMD;
    header[1] = (uint8_t)(start_address >> 8);  // MSB
    header[2] = (uint8_t)(start_address & 0xFF);// LSB

    // 3. Send Command and Address
    EEPROM_CS_Select();
    status = HAL_SPI_Transmit(&hspi1, header, 3, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    // 4. Wait for the Erase Cycle to complete (Erasure takes longer than a write!)
    status = EEPROM_Wait_For_Write_Completion(ERASE_TIMEOUT_MS);

    return status;
}

HAL_StatusTypeDef EEPROM_Sector_Erase(uint16_t start_address)
{
    HAL_StatusTypeDef status;

    // 1. Send Write Enable (MANDATORY)
    if (EEPROM_Write_Enable() != HAL_OK) return HAL_ERROR;

    // 2. Prepare Command and Address
    uint8_t header[3];
    header[0] = EEPROM_SECTOR_ERASE_CMD;
    header[1] = (uint8_t)(start_address >> 8);  // MSB
    header[2] = (uint8_t)(start_address & 0xFF);// LSB

    // 3. Send Command and Address
    EEPROM_CS_Select();
    status = HAL_SPI_Transmit(&hspi1, header, 3, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    // 4. Wait for the Erase Cycle to complete
    status = EEPROM_Wait_For_Write_Completion(SECTOR_ERASE_TIMEOUT_MS);

    return status;
}

HAL_StatusTypeDef EEPROM_Chip_Erase(void)
{
    HAL_StatusTypeDef status;

    // 1. Send Write Enable (MANDATORY)
    if (EEPROM_Write_Enable() != HAL_OK) return HAL_ERROR;

    // 2. Send the single-byte CHIP_ERASE command
    EEPROM_CS_Select();
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_CHIP_ERASE_CMD}, 1, HAL_MAX_DELAY);
    EEPROM_CS_Deselect();

    // 3. Wait for the Erase Cycle to complete
    status = EEPROM_Wait_For_Write_Completion(CHIP_ERASE_TIMEOUT_MS);

    return status;
}

HAL_StatusTypeDef EEPROM_Read_Status_Register(uint8_t *pStatus)
{
    HAL_StatusTypeDef status;
    uint8_t tx_command = EEPROM_RDSR_REG;

    // 1. Assert CS
    EEPROM_CS_Select();

    // 2. Send the RDSR command
    status = HAL_SPI_Transmit(&hspi1, &tx_command, 1, HAL_MAX_DELAY);

    if (status != HAL_OK) {
        EEPROM_CS_Deselect();
        return status;
    }

    // 3. Receive the Status Register byte
    // The STM32 sends a dummy byte while the EEPROM streams the status.
    status = HAL_SPI_Receive(&hspi1, pStatus, 1, HAL_MAX_DELAY);

    // 4. De-assert CS
    EEPROM_CS_Deselect();

    return status;
}

HAL_StatusTypeDef EEPROM_Wait_For_Write_Completion(uint32_t Timeout)
{
    uint8_t status_reg = 0xFF;
    uint32_t start_time = HAL_GetTick(); // Get the current system time (in ms)

    // Loop until the WIP bit is 0 (cleared) or the timeout is reached
    do
    {
        // 1. Read the Status Register
        if (EEPROM_Read_Status_Register(&status_reg) != HAL_OK) {
            return HAL_ERROR; // I/O error during status read
        }

        // 2. Check for timeout
        if ((HAL_GetTick() - start_time) > Timeout) {
            // The WIP bit is still 1 after the maximum allowed time
            return HAL_TIMEOUT;
        }

        // Optional: Introduce a small delay to avoid constantly hammering the SPI bus
        HAL_Delay(1);

    } while (status_reg & EEPROM_WIP_BIT_MASK); // Loop while WIP bit is set (i.e., status_reg & 0x01 is non-zero)

    return HAL_OK;
}

HAL_StatusTypeDef EEPROM_Deep_Power_Down(void)
{
    HAL_StatusTypeDef status;

    // 1. Assert CS
    EEPROM_CS_Select();

    // 2. Send the DPD command
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_DEEP_POWER_DOWN_MODE}, 1, HAL_MAX_DELAY);

    // 3. Immediately De-assert CS to engage the DPD mode.
    EEPROM_CS_Deselect();

    // Note: No WIP polling is needed, as the chip is now asleep.

    return status;
}

/**
  * @brief  Sends the Release from Deep Power Down (RDPD) command.
  * Wakes the chip up and allows subsequent commands.
  * @retval HAL status.
  */
HAL_StatusTypeDef EEPROM_Release_Deep_Power_Down(void)
{
    HAL_StatusTypeDef status;

    // 1. Assert CS (This initiates the wake-up sequence)
    EEPROM_CS_Select();

    // 2. Send the RDPD command
    status = HAL_SPI_Transmit(&hspi1, (uint8_t[]){EEPROM_RELEASE_DPD_READ_ID}, 1, HAL_MAX_DELAY);

    // 3. De-assert CS
    EEPROM_CS_Deselect();

    // 4. Wait for the chip to power up and stabilize.
    // Check your datasheet for the required minimum recovery time (t_RES or t_DPD_Exit).
    // A typical value is 20-30 microseconds.
    // Using HAL_Delay(1) is usually sufficient on STM32 for microsecond delays.
    HAL_Delay(1);

    return status;
}
