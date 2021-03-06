/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-manage' Mid-level computing, and networking
	Copyright (C) 2016 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developper] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab 
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors] Erin Main (ermain@mit.edu)
*****************************************************************************
	[This file] fm_i2c: IMU configuration
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-23 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_imu.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

struct imu_s imu;

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static HAL_StatusTypeDef imu_write(uint8_t internal_reg_addr, uint8_t* pData,
		uint16_t Size);
static HAL_StatusTypeDef imu_read(uint8_t internal_reg_addr, uint8_t *pData,
		uint16_t Size);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialize the IMU w/ default values in config registers
void init_imu(void)
{
	//Reset the IMU.
	reset_imu();
	// Initialize the config registers.
	uint8_t config[4] = { D_IMU_CONFIG, D_IMU_GYRO_CONFIG, D_IMU_ACCEL_CONFIG, \
							D_IMU_ACCEL_CONFIG2 };
	uint8_t imu_addr = IMU_CONFIG;
	for(int i = 0; i < 4; i++)
	{
		imu_write(imu_addr + i, &config[i], 1);
	}
}

// Reset the IMU to default settings
void reset_imu(void)
{
	uint8_t config = D_DEVICE_RESET;
	imu_write(IMU_PWR_MGMT_1, &config, 1);
}

// Get accel X
int16_t get_accel_x(void)
{
	uint8_t data[2] = { 0, 0 };
	imu_read(IMU_ACCEL_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}
// Get accel Y
int16_t get_accel_y(void)
{
	uint8_t data[2];
	imu_read(IMU_ACCEL_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get accel Z
int16_t get_accel_z(void)
{
	uint8_t data[2];
	imu_read(IMU_ACCEL_ZOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

//Puts all the accelerometer values in the structure:
void get_accel_xyz(void)
{
	uint8_t tmp_data[7] = {0,0,0,0,0,0};
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_ACCEL_XOUT_H, tmp_data, 7);
}

// Get gyro X
int16_t get_gyro_x(void)
{
	uint8_t data[2];
	imu_read(IMU_GYRO_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Y
int16_t get_gyro_y(void)
{
	uint8_t data[2];
	imu_read(IMU_GYRO_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Z
int16_t get_gyro_z(void)
{
	uint8_t data[2];
	imu_read(IMU_GYRO_ZOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

//Puts all the gyroscope values in the structure:
void get_gyro_xyz(void)
{
	uint8_t tmp_data[7] = {0,0,0,0,0,0,0};
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_GYRO_XOUT_H, tmp_data, 6);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//write data to an internal register of the IMU.
// you would use this function if you wanted to set configuration values
// for a particular feature of the IMU.
// uint8_t internal_reg_addr: internal register address of the IMU
// uint8_t* pData: pointer to the data we want to send to that address
// uint16_t Size: amount of bytes of data pointed to by pData

static HAL_StatusTypeDef imu_write(uint8_t internal_reg_addr, uint8_t* pData,
		uint16_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, IMU_ADDR, (uint16_t) internal_reg_addr,
	I2C_MEMADD_SIZE_8BIT, pData, Size, IMU_BLOCK_TIMEOUT);
}

//read data from an internal register of the IMU.
// you would use this function if you wanted to read data from the IMU.
// uint8_t internal_reg_addr: internal register address of the IMU
// uint8_t* pData: pointer to where we want to save the data from the IMU
// uint16_t Size: amount of bytes we want to read
static HAL_StatusTypeDef imu_read(uint8_t internal_reg_addr, uint8_t *pData,
		uint16_t Size)
{
	return HAL_I2C_Mem_Read(&hi2c1, IMU_ADDR, (uint16_t) internal_reg_addr,
	I2C_MEMADD_SIZE_8BIT, pData, Size, IMU_BLOCK_TIMEOUT);
}
