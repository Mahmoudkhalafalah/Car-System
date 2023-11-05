/*
 * functions.c
 *
 *  Created on: Aug 12, 2023
 *      Author: Mahmoud Khalafallah
 */
#include "functions.h"
#include <stdio.h>

//functions definitions

/*
 * Function for displaying the entry list
 * asking the user for entering his choice
 * displaying the user's choice
 * displaying "invalid choice" message if the user enters invalid input
 * repeats if the user chose to turn off the vehicle or entered invalid input
 * returns the user's choice "if valid"
 */
char entryOptions() {
	char choice = ' ';
	do {
		printf("\nChoose from the list.\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");

		scanf(" %c", &choice);
		switch (choice) {
		case 'a':
		case 'A':
			printf("Turning on the vehicle engine...\n");
			break;
		case 'b':
		case 'B':
			printf("Turning off the vehicle engine...\n");
			break;
		case 'c':
		case 'C':
			printf("Quitting the system...\n");
			break;
		default:
			printf("Invalid choice...\n");

		}

	} while (!(choice == 'a' || choice == 'A' || choice == 'c' || choice == 'C'));
	return choice;
}

/*
 * Function for displaying the options' list
 * sets the engine states to on
 * asking the user for entering his choice
 * returns the user's choice
 * if the engine temp controller feature is off the "set the engine temp" option won't be displayed
 */
char sensorInputsOptions(EState *engineState) {

	*engineState = ON;
	char choice = ' ';
	printf("\nChoose from the list.\n");

	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature.\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature.\n");
#endif
	scanf(" %c", &choice);
	return choice;

}

/*
 * Function for taking the decision after the user choice from the options' list
 * if the user chose to turn off the vehicle it calls the entryOptions function updating the user's choice
 * depending on user's choice it asks the user to enter the sensor reading
 * depending on the sensor reading it updates of this sensor dependent states of the car
 * if the engine temp controller feature is off the engine temp sensor will be disabled
 * if the user inputs invalid choice it prints "invalid choice" message
 * return the updated choice "from the entry list" if chosen and "empty" not
 */
char decisionMaker(char choice, char *trafficLightColor, CarStates *states) {

	char innerChoice = ' ';
	switch (choice) {
	case 'a':
	case 'A':
		printf("Turning off the vehicle engine...\n");
		states->engineState = OFF;
		innerChoice = entryOptions();
		break;
	case 'b':
	case 'B':

		do {
			printf("Enter the traffic light color:\"g, o or r\" \n");
			scanf(" %c", trafficLightColor);

			if (!(*trafficLightColor != 'G' || *trafficLightColor != 'g'
					|| *trafficLightColor != 'o' || *trafficLightColor != 'O'
					|| *trafficLightColor != 'R' || *trafficLightColor != 'r'))
				printf("Invalid Input... \n");

		} while (!(*trafficLightColor == 'G' || *trafficLightColor == 'g'
				|| *trafficLightColor == 'o' || *trafficLightColor == 'O'
				|| *trafficLightColor == 'R' || *trafficLightColor == 'r'));
		updateVehicleStates(*trafficLightColor, states);
		printVehicleState(states);
		break;
	case 'c':
	case 'C':
		printf("Enter the room temperature: \n");
		scanf("%d", &states->roomTemp);
		updateACState(states);
		printVehicleState(states);
		break;
#if WITH_ENGINE_TEMP_CONTROLLER
	case 'd':
	case 'D':

		printf("Enter the engine temperature: \n");
		scanf("%d", &states->engineTemp);
		updateEngineTempController(states);
		printVehicleState(states);
		break;
#endif
	default:
		printf("Invalid choice...\n");
	}
	return innerChoice;

}

/*
 * Function to update the vehicle's speed
 * depending on the traffic light color that the user entered
 */
void updateVehicleSpeed(int *speed, char trafficLightColor) {

	if (trafficLightColor == 'G' || trafficLightColor == 'g')
		*speed = 100;
	else if (trafficLightColor == 'O' || trafficLightColor == 'o')
		*speed = 30;
	else if (trafficLightColor == 'R' || trafficLightColor == 'r')
		*speed = 0;

}

/*
 * Function to update the AC state
 * depending on the room temperature that the user entered
 * and the vehicle's speed
 */
void updateACState(CarStates *states) {

	if (states->roomTemp <= 10 || states->roomTemp >= 30) {
		states->ACState = ON;
		states->roomTemp = 20;
	} else
		states->ACState = OFF;

	if (states->vehicleSpeed == 30) {
		states->ACState = ON;
		states->roomTemp = states->roomTemp * (5 / 4) + 1;
	}
}

/*
 * Function to update the engine temperature controller state
 * depending on the engine temperature that the user entered
 * and the vehicle's speed
 */
void updateEngineTempController(CarStates *states) {

	if (states->engineTemp <= 100 || states->engineTemp >= 150) {
		states->engineTempCtrl = ON;
		states->engineTemp = 125;
	} else
		states->engineTempCtrl = OFF;

	if (states->vehicleSpeed == 30) {
		states->engineTempCtrl = ON;
		states->engineTemp = states->engineTemp * (5 / 4) + 1;
	}
}

/*
 * Function to update all the vehicle states
 * depending on the sensor readings that the user entered
 */
void updateVehicleStates(char trafficLightColor, CarStates *states) {

	updateVehicleSpeed(&states->vehicleSpeed, trafficLightColor);
	updateACState(states);
	updateEngineTempController(states);

}

/*
 * Function to display all vehicle states
 * if the engine temp controller feature is off the Engine Temperature Controller state and the Engine Temperature won't be displayed
 */
void printVehicleState(CarStates *states) {

	printf("\nEngine is ");
	printf((states->engineState) ? "ON" : "OFF");
	printf("\n");
	printf("AC is ");
	printf((states->ACState) ? "ON" : "OFF");
	printf("\n");
	printf("Vehicle speed is ");
	printf("%d", states->vehicleSpeed);
	printf(" Km/hr\n");
	printf("Room Temperature is ");
	printf("%d", states->roomTemp);
	printf(" °C\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Engine Temperature Controller is ");
	printf((states->engineTempCtrl) ? "ON" : "OFF");
	printf("\n");
	printf("Engine Temperature is ");
	printf("%d", states->engineTemp);
	printf(" °C\n");
#endif

}

