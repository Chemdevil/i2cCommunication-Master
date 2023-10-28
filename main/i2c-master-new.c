#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "i2c-master";

#define DELAY_MS 1000
#define TIMEOUT_MS 1000
#define I2C_MASTER_SCL_IO 22        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define SLAVE_ADDRESS1 0x32
#define SLAVE_ADDRESS2 0x27
#define I2C_MASTER_RX_BUF_LEN 128
#define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
#define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                /*!< I2C ack value */
#define NACK_VAL 0x1               /*!< I2C nack value */
SemaphoreHandle_t print_mux = NULL;
int i2c_master_port = 0;

// static esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *data_rd, size_t size)
// {
//     if (size == 0)
//     {
//         return ESP_OK;
//     }
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (SLAVE_ADDRESS << 1) | READ_BIT, ACK_CHECK_EN);
//     if (size > 1)
//     {
//         i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
//     }
//     i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
//     i2c_master_stop(cmd);
//     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(100));
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

static void copy_array(uint8_t *dest, uint16_t *source, int len)
{
    for (size_t i = 0; i < len; i++)
    {
        dest[i] = source[i];
    }
}

static esp_err_t i2c_master_init(void)
{

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
        .clk_flags = 0,
        /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    esp_err_t err = i2c_param_config(i2c_master_port, &conf);
    if (err != ESP_OK)
    {
        return err;
    }
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

// static esp_err_t i2c_master_send(uint8_t message[], int len)
// {
//     // ESP_LOGI(TAG, "Sending Message = %s", message);

//     esp_err_t ret;
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, SLAVE_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
//     i2c_master_write(cmd, message, len, ACK_CHECK_EN);
//     i2c_master_stop(cmd);

//     ret = i2c_master_cmd_begin(i2c_master_port, cmd, pdMS_TO_TICKS(100));
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

static void read_Write_Data(uint8_t device_address,const uint8_t* write_buffer, uint8_t* read_buffer){
    i2c_master_write_read_device(i2c_master_port, 
        device_address, 
        write_buffer, 
        12, 
        read_buffer, 
        I2C_MASTER_RX_BUF_LEN, 
        pdMS_TO_TICKS(TIMEOUT_MS));
        ESP_LOG_BUFFER_CHAR(TAG, read_buffer, 12);
}

void app_main(void)
{
    uint8_t command[12];
    uint8_t command_1[12] = "0b110";
    uint8_t command_2[12] = "0b111";
    uint8_t rx_data[I2C_MASTER_RX_BUF_LEN]={0};
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    // CSMA CA channel
    while (1)
    {
        // i2c_master_write_read_device(i2c_master_port, 
        // 0x32, 
        // &command_r, 
        // sizeof(command_r), 
        // rx_data, 
        // I2C_MASTER_RX_BUF_LEN, 
        // pdMS_TO_TICKS(TIMEOUT_MS));
        // ESP_LOG_BUFFER_CHAR(TAG, rx_data, 8);
        // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        // bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
        // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        // i2c_master_write_read_device(i2c_master_port, 
        // 0x31, 
        // &command_r, 
        // sizeof(command_r), 
        // rx_data, 
        // I2C_MASTER_RX_BUF_LEN, 
        // pdMS_TO_TICKS(TIMEOUT_MS));
        // ESP_LOG_BUFFER_CHAR(TAG, rx_data, 8);
        // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        // bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
        read_Write_Data(SLAVE_ADDRESS1, &command_1, rx_data);
        bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        read_Write_Data(SLAVE_ADDRESS2, &command_2, rx_data);
        bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}