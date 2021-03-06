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
	[This file] fm_i2c: i2c comms
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-23 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

#ifndef INC_FM_I2C_H
#define INC_FM_I2C_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern I2C_HandleTypeDef hi2c1;

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_i2c1(void);
void disable_i2c(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//set to 1 if we want to use interrupt driven I2C.
#define I2C_USE_INT 0
#define I2C_CLOCK_RATE 100000 //in Hz, corresponds to "Regular Speed" I2C

#endif //INC_FM_I2C_H

