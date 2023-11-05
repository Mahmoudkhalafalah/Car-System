/*
 ============================================================================
 Name        : MiniProject.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Functions/functions.h"

int main(void) {

//SetUp scope to set variables and statements the needs to be excuted once at the beginning
	//For printing messages before scanf
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//initializing traffic light color variable
	char trafficLightColor = ' ';

	//initializing car states
	CarStates myCarSates = { OFF, OFF, OFF, 20, 25, 110 };

	//initializing choice variable
	char choice = ' ';

	//initially display the entry list
	choice = entryOptions();

	//infinite Loop
	while (1) {

		/*
		 * breaking the infinite loop "terminating the system"
		 * if the user enters 'c' or 'C' (quit the system)
		 */
		if (choice == 'c' || choice == 'C')
			break;

		//updating the user's choice after displaying the options' list
		choice = sensorInputsOptions(&myCarSates.engineState);

		/*
		 * controlling the navigation after the user chooses an option from the options' list
		 * reseting the choice if the user didn't choose to turn off the vehicle
		 * displaying the entry list and updating the choice if the user chooses to turn of the vehicle
		 */
		choice = decisionMaker(choice, &trafficLightColor, &myCarSates);
	}

	return EXIT_SUCCESS;
}
