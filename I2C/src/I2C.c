//
// Created by dingrui on 2023/1/18.
//

#include "I2C.h"

/**
 * @brief I2C起始信号
 */
void i2c_start()
{
    // SCL高电平
    I2C_SCL = 1;
    // SDA下降沿
    I2C_SDA = 1;
    delay_10us(1);
    I2C_SDA = 0;
    delay_10us(1);
    // 占用总线
    I2C_SCL = 0;
}

/**
 * @brief I2C停止信号
 */
void i2c_stop()
{
    // scl高电平
    I2C_SCL = 1;
    // sda上升沿
    I2C_SDA = 0;
    delay_10us(1);
    I2C_SDA = 1;
    delay_10us(1);
    // 总线空闲状态
    I2C_SCL = 1;
}

/**
 * @brief 应答信号
 */
void i2c_ack()
{
    I2C_SCL = 0;
    I2C_SDA = 0;
    delay_10us(1);
    I2C_SCL = 1;
    delay_10us(1);
    I2C_SCL = 0;
}

void i2c_nack()
{
    I2C_SCL = 0;
    I2C_SDA = 1;
    delay_10us(1);
    I2C_SCL = 1;
    delay_10us(1);
    I2C_SCL = 0;
}

// 主机读取从机响应
u8 i2c_wait_ack()
{
    u8 delay = 0;
    I2C_SCL = 1;
    delay_10us(1);
    while (I2C_SDA)
    {
        delay++;
        if (delay > 100)
        {
            // 没有收到从机ack 主管认为从机不想要主机发送的信息 主机停止i2c协议
            i2c_stop();
            return SLAVE_REPLAY_NACK;
        }
    }
    // 等待ack ack是低电平
    I2C_SCL = 0;
    return SLAVE_REPLAY_ACK;
}

// 主机向从机写信息
void i2c_write_byte(u8 dat)
{
    // 字节高位往低位方向
    I2C_SCL = 0;
    for (int i = 7; i >= 0; i--)
    {
        if (((dat >> i) & 0x01) == 0)
            I2C_SDA = 0;
        else
            I2C_SDA = 1;
        I2C_SCL = 1;
        delay_10us(1);
        I2C_SCL = 0;
    }
}

/**
 * @brief 主机读取从机信息
 * @param mode 读取完之后是继续读取还是停止读取
 * @return
 */
u8 i2c_read_byte(u8 mode)
{
    u8 ret = 0; // 接收到的数据
    // 先读到的是高位
    for (int i = 0; i < 8; ++i)
    {
        I2C_SCL = 0;
        delay_10us(1);
        I2C_SCL = 1;
        delay_10us(1);
        // 读取sda数据
        ret <<= 1;
        ret |= I2C_SDA;
    }
    // 判定主机是否需要从机继续发送数据
    if (mode == SLAVE_SEND_CONTINUE) i2c_ack();
    else i2c_nack();
    return ret;
}