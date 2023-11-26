// #include <stdio.h>
// #include <string.h>
// #include "esp_log.h"
// #include "driver/i2c.h"

// static const char *TAG = "i2c-master";

// #define DELAY_MS 1000
// #define TIMEOUT_MS 1000
// #define I2C_MASTER_SCL_IO 22        /*!< gpio number for I2C master clock */
// #define I2C_MASTER_SDA_IO 21        /*!< gpio number for I2C master data  */
// #define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
// #define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
// #define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
// #define SLAVE_ADDRESS1 0x32
// #define SLAVE_ADDRESS2 0x27
// #define I2C_MASTER_RX_BUF_LEN 128
// #define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
// #define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
// #define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
// #define ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
// #define ACK_VAL 0x0                /*!< I2C ack value */
// #define NACK_VAL 0x1               /*!< I2C nack value */
// SemaphoreHandle_t print_mux = NULL;
// int i2c_master_port = 0;

// // static esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *data_rd, size_t size)
// // {
// //     if (size == 0)
// //     {
// //         return ESP_OK;
// //     }
// //     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
// //     i2c_master_start(cmd);
// //     i2c_master_write_byte(cmd, (SLAVE_ADDRESS << 1) | READ_BIT, ACK_CHECK_EN);
// //     if (size > 1)
// //     {
// //         i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
// //     }
// //     i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
// //     i2c_master_stop(cmd);
// //     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(100));
// //     i2c_cmd_link_delete(cmd);
// //     return ret;
// // }

// static void copy_array(uint8_t *dest, uint16_t *source, int len)
// {
//     for (size_t i = 0; i < len; i++)
//     {
//         dest[i] = source[i];
//     }
// }

// static esp_err_t i2c_master_init(void)
// {

//     i2c_config_t conf = {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = I2C_MASTER_SDA_IO,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_io_num = I2C_MASTER_SCL_IO,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = I2C_MASTER_FREQ_HZ,
//         .clk_flags = 0,
//         /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
//     };
//     esp_err_t err = i2c_param_config(i2c_master_port, &conf);
//     if (err != ESP_OK)
//     {
//         return err;
//     }
//     return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
// }

// // static esp_err_t i2c_master_send(uint8_t message[], int len)
// // {
// //     // ESP_LOGI(TAG, "Sending Message = %s", message);

// //     esp_err_t ret;
// //     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
// //     i2c_master_start(cmd);
// //     i2c_master_write_byte(cmd, SLAVE_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
// //     i2c_master_write(cmd, message, len, ACK_CHECK_EN);
// //     i2c_master_stop(cmd);

// //     ret = i2c_master_cmd_begin(i2c_master_port, cmd, pdMS_TO_TICKS(100));
// //     i2c_cmd_link_delete(cmd);
// //     return ret;
// // }

// static void read_Write_Data(uint8_t device_address,const uint8_t* write_buffer, uint8_t* read_buffer){
//     i2c_master_write_read_device(i2c_master_port, 
//         device_address, 
//         write_buffer, 
//         12, 
//         read_buffer, 
//         I2C_MASTER_RX_BUF_LEN, 
//         pdMS_TO_TICKS(TIMEOUT_MS));
//         ESP_LOG_BUFFER_CHAR(TAG, read_buffer, 12);
// }

// void app_main(void)
// {
//     uint8_t command[12];
//     uint8_t command_1[12] = "0b110";
//     uint8_t command_2[12] = "0b111";
//     uint8_t rx_data[I2C_MASTER_RX_BUF_LEN]={0};
//     ESP_ERROR_CHECK(i2c_master_init());
//     ESP_LOGI(TAG, "I2C initialized successfully");
//     // CSMA CA channel
//     while (1)
//     {
//         // i2c_master_write_read_device(i2c_master_port, 
//         // 0x32, 
//         // &command_r, 
//         // sizeof(command_r), 
//         // rx_data, 
//         // I2C_MASTER_RX_BUF_LEN, 
//         // pdMS_TO_TICKS(TIMEOUT_MS));
//         // ESP_LOG_BUFFER_CHAR(TAG, rx_data, 8);
//         // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
//         // bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
//         // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
//         // i2c_master_write_read_device(i2c_master_port, 
//         // 0x31, 
//         // &command_r, 
//         // sizeof(command_r), 
//         // rx_data, 
//         // I2C_MASTER_RX_BUF_LEN, 
//         // pdMS_TO_TICKS(TIMEOUT_MS));
//         // ESP_LOG_BUFFER_CHAR(TAG, rx_data, 8);
//         // vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
//         // bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
//         read_Write_Data(SLAVE_ADDRESS1, &command_1, rx_data);
//         bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
//         vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
//         read_Write_Data(SLAVE_ADDRESS2, &command_2, rx_data);
//         bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
//         vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
//     }
// }

// #include <stdio.h>
// #include <string.h>
// #include "esp_log.h"
// #include "driver/i2c.h"

// static const char *TAG = "i2c-master";


// #define I2C_MASTER_SCL_IO 22               /*!< gpio number for I2C master clock */
// #define I2C_MASTER_SDA_IO 21               /*!< gpio number for I2C master data  */
// #define I2C_MASTER_FREQ_HZ 100000        /*!< I2C master clock frequency */
// #define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
// #define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
// #define SLAVE_ADDRESS 0x0A

// #define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
// #define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
// #define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
// #define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
// #define ACK_VAL 0x0                             /*!< I2C ack value */
// #define NACK_VAL 0x1                            /*!< I2C nack value */

// int i2c_master_port = 0;

// static esp_err_t __attribute__((unused)) i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *data_rd, size_t size)
// {
//     if (size == 0) {
//         return ESP_OK;
//     }
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (SLAVE_ADDRESS << 1) | READ_BIT, ACK_CHECK_EN);
//     if (size > 1) {
//         i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
//     }
//     i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
//     i2c_master_stop(cmd);
//     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

// static esp_err_t i2c_master_init(void)
// {
  
//     i2c_config_t conf = {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = I2C_MASTER_SDA_IO,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_io_num = I2C_MASTER_SCL_IO,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = I2C_MASTER_FREQ_HZ,
//         // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
//     };
//     esp_err_t err = i2c_param_config(i2c_master_port, &conf);
//     if (err != ESP_OK) {
//         return err;
//     }
//     return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
// }

// static esp_err_t i2c_master_send(uint8_t message[], int len)
// {
//     ESP_LOGI(TAG, "Sending Message = %s", message);   
    
//     esp_err_t ret; 
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();    
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, SLAVE_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
//     i2c_master_write(cmd, message, len, ACK_CHECK_EN);
//     i2c_master_stop(cmd);
    
//     ret = i2c_master_cmd_begin(i2c_master_port, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

// void app_main(void)
// {
//     const uint8_t  on_command[] = "LED_ON";
//     const uint8_t  off_command[] = "LED_OFF";
//     size_t slaveDataSize =5;
//     const uint8_t slaveData[5] = {};
//     ESP_ERROR_CHECK(i2c_master_init());
//     ESP_LOGI(TAG, "I2C initialized successfully");

//     while(1)
//     {
//         // i2c_master_send(on_command, sizeof(on_command));
//         // vTaskDelay(1000/ portTICK_PERIOD_MS);
//         // i2c_master_send(off_command, sizeof(off_command));
//         // vTaskDelay(1000/ portTICK_PERIOD_MS);  
//         int ret = i2c_master_read_slave(i2c_master_port, slaveData, slaveDataSize);
//         ESP_LOGI(TAG,"Return values %d---%s\n",ret,slaveData);
//         i2c_reset_rx_fifo(i2c_master_port);
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
    
// }

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
static const char *TAG = "i2c-master";
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

#define DELAY_MS 1000
#define TIMEOUT_MS 1000
#define I2C_MASTER_SCL_IO 22        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 100000   /*!< I2C master clock frequency */
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

char* vectorlocalTime(u_int8_t* counter);
u_int8_t* vectorcalculateRecvTimeStamp(u_int8_t* recvTimeStamp, uint8_t* counter,  uint8_t size);
u_int8_t* vector_event(uint8_t processId, uint8_t* counter);
u_int8_t* vector_send_Message(u_int8_t processId, u_int8_t *counter, char * rx_data);

uint8_t *messageParser(char *data) {
    static uint8_t c[3] = {-1, -1, -1};
    int startArrayIndex = 0;
    int endArrayIndex = 0;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '[') {
            startArrayIndex = i + 1;
        } else if (data[i] == ']') {
            endArrayIndex = i;
            break;
        }
    }
    char substring[endArrayIndex - startArrayIndex];
    u_int8_t start = 0;
    strncpy(substring, data + startArrayIndex, endArrayIndex - startArrayIndex);
    char *token = strtok(substring, ",");
    start = 0;
    while (token != NULL) {
        c[start] = atoi(token);
        token = strtok(NULL, ",");
        start++;
    }
    return c;

}

void swapCounter(uint8_t *old, uint8_t *new, int size) {
    uint8_t temp[size];
    for (uint8_t index = 0; index < (size); index++) {
        temp[index] = old[index];
        old[index] = new[index];
        new[index] = temp[index];
    }
}

char *vectorlocalTime(uint8_t *counter) {
    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    char *lt = asctime(localtime((const time_t *) &timeStr));
    char timeStrCounter[300];
    sprintf(timeStrCounter, "Vector Clock = {[%d,%d,%d]}, LocalTime:%s", counter[0], counter[1], counter[2], lt);
    return lt;
}

u_int8_t *vectorcalculateRecvTimeStamp(uint8_t *recvTimeStamp, uint8_t *counter, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        counter[i] = (recvTimeStamp[i] > counter[i]) ? recvTimeStamp[i] : counter[i];
    }
    return counter;
}

u_int8_t *vector_event(u_int8_t processId, u_int8_t *counter) {
    counter[processId] += 1;
    char *localtimeString = vectorlocalTime(counter);
    printf("Vector Clock = {[%d,%d,%d]}, LocalTime:%s", counter[0], counter[1], counter[2], localtimeString);
    return counter;
}



// static esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *data_rd, size_t size)
// {
//     if (size == 0)
//     {
//         return ESP_OK;
//     }
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (SLAVE_ADDRESS1 << 1) | READ_BIT, ACK_CHECK_EN);
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

// static esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size)
// {
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (SLAVE_ADDRESS1 << 1) | WRITE_BIT, ACK_CHECK_EN);
//     i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
//     i2c_master_stop(cmd);
//     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / pdMS_TO_TICKS(100));
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

void assign_uint8_t_to_char(uint8_t *uint8_array, char *char_array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        char_array[i] = (char) uint8_array[i];
    }
}

static esp_err_t i2c_master_write_read_slave(i2c_port_t i2c_num,
 u_int8_t slaveAddress,uint8_t *data_wr, size_t write_size, 
 uint8_t *data_read, size_t read_size,TickType_t ticks_to_wait){
    esp_err_t err = ESP_OK;
    u_int8_t buffer[I2C_MASTER_RX_BUF_LEN] = { 0 };
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    assert (cmd != NULL);
    err = i2c_master_start(cmd);
    if (err != ESP_OK) {
        goto end;
    }
    err = i2c_master_write_byte(cmd, slaveAddress << 1 | I2C_MASTER_WRITE, true);
    if (err != ESP_OK) {
        goto end;
    }
    err = i2c_master_write(cmd, data_wr, write_size, true);
    if (err != ESP_OK) {
        goto end;
    }
    err = i2c_master_start(cmd);
    if (err != ESP_OK) {
        goto end;
    }
    err = i2c_master_write_byte(cmd, slaveAddress << 1 | I2C_MASTER_READ, true);
    if (err != ESP_OK) {
        goto end;
    }
    err = i2c_master_read(cmd, buffer, read_size, I2C_MASTER_LAST_NACK);
    if (err != ESP_OK) {
        goto end;
    }
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(i2c_num, cmd, ticks_to_wait);
    end:
    i2c_cmd_link_delete(cmd);
    return err;
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


static void read_Write_Data(uint8_t device_address,const char * write_buffer, char * read_buffer){
    uint8_t write_Array[sizeof(write_buffer)];
    for(uint8_t i = 0; i < sizeof(write_buffer); i++) {
    write_Array[i] = (uint8_t) write_buffer[i];
    }
    uint8_t rx_data[I2C_MASTER_RX_BUF_LEN]={0};
    
    i2c_master_write_read_slave(i2c_master_port, 
        device_address, 
        write_Array, 
        128, 
        rx_data, 
        I2C_MASTER_RX_BUF_LEN, 
        pdMS_TO_TICKS(TIMEOUT_MS));

        assign_uint8_t_to_char(rx_data,read_buffer,I2C_MASTER_RX_BUF_LEN);
    // read_buffer = (char*) rx_data;
        ESP_LOG_BUFFER_CHAR(TAG, rx_data, 128);
        
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    
}

u_int8_t *vector_send_Message(u_int8_t processId, u_int8_t *counter, char * rx_data) {
    counter[processId] += 1;
    char sendMessageData[100];
    u_int8_t *receiveMessageData;
    sprintf(sendMessageData, "%d-[%d,%d,%d]",processId, counter[0], counter[1], counter[2]);
    char *timeData = vectorlocalTime(counter);
    printf("Sending vector message from processId {%d}, at {%s}", processId, timeData);
    read_Write_Data(SLAVE_ADDRESS1,sendMessageData,rx_data);
    receiveMessageData = messageParser(rx_data);
    counter = vectorcalculateRecvTimeStamp(receiveMessageData, counter, 3);
    char *timeData1 = vectorlocalTime(counter);
    printf("Receiving vector message from processId {%d}, at {%s}", processId, timeData1);
    return counter;
}

void app_main(void)
{
    // uint8_t command[12];
    // uint8_t command_1[12] = "0b111";
    // uint8_t command_2[12] = "0b101";
    char rx_data[I2C_MASTER_RX_BUF_LEN]={0};
    uint8_t counter[3] = {0,0,0};
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    // CSMA CA channel
    while (1)
    {
        vector_send_Message(0,counter,rx_data);
        // swapCounter(counter,messageParser(rx_data),3);
        bzero(rx_data,I2C_MASTER_RX_BUF_LEN);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}
