/*
 * functions.h
 *
 *  Created on: Aug 12, 2023
 *      Author: Mahmoud Khalafallah
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef enum s {
	OFF, ON
} EState;

// Engine Temp controller feature "disabled"
#define WITH_ENGINE_TEMP_CONTROLLER 0

// structure to hold all vehicle's states
typedef struct states {
	EState engineState;
	EState ACState;
	EState engineTempCtrl;
	int vehicleSpeed;
	int roomTemp;
	int engineTemp;

} CarStates;

//functions declaration

char entryOptions();

char sensorInputsOptions(EState *engineState);

char decisionMaker(char choice, char *trafficLightColor, CarStates *states);

void updateVehicleSpeed(int *speed, char trafficLightColor);

void updateACState(CarStates *states);

void updateEngineTempController(CarStates *states);

void updateVehicleStates(char trafficLightColor, CarStates *states);

void printVehicleState(CarStates *states);

#endif /* FUNCTIONS_H_ */
