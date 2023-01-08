/*
 * runOneSimulation.h
 *
 * This fle contains the headers an declarations for the runOneSimulation.c
 * file which runs a single simulation.
 *
 */

#ifndef __RUNONESIMULATION_h
#define __RUNONESIMULATION_h

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <queue.h>

/*	Structure Definitions	*/

struct SimData {
	int lMaxWait;
	int lNumMoves;
	int lTotalWait;
	int lClearance;

	int rMaxWait;
	int rNumMoves;
	int rTotalWait;
	int rClearance;
};

/*	Function Prototypes	*/

struct SimData* runOneSimulation (gsl_rng*, int, int, int, int);
struct SimData* createSimData();
gsl_rng* setupRandom();

#endif
