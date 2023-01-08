/*
 * runOneSimulation.c
 * This file contains the runOneSimulation and setupRandom
 * functions. Their usages are decribed below in their own
 * docstrings.
 */

#include <runOneSimulation.h>

/*	This function is used to run a simuation using the given
 *	paratemeters specified as arguments. The function
 *	returns a pointer to a SimData structure which contains
 *	the results of the simulation.				*/
struct SimData* runOneSimulation (gsl_rng* r, int lLightTime, int lArrivalRate, int rLightTime, int rArrivalRate)
{
	struct Queue* rightQ = createQueue();

	struct Queue* leftQ = createQueue();

	struct SimData* data = createSimData();

	/*	Main Loop	*/
		
	int lightColour = 0;
	
	int iterations = 0;

	int carWait;

	int lightCount = 0;

	while ((iterations < 500) || ((!isEmpty(rightQ)) || (!isEmpty(leftQ))))
	{
		
		iterations++;
		
		/*	Check if need to change the traffic light colour.	*/

		if (lightColour == 0 && lightCount < lLightTime)
			lightCount++;
		
		else if (lightColour == 1 && lightCount < rLightTime)
			lightCount++;
		else
		{
			lightCount = 0;
			
			if (lightColour == 0)
				lightColour = 1;
			else
				lightColour = 0;
			
			continue;
		}

		/*	If the iterations are less than 500 get random
		 *	values to determine whether to add cars ot not.	*/


		if (iterations < 500)
		{	
			if (gsl_ran_flat(r,0,100) < lArrivalRate)
				enQueue(leftQ);

			if (gsl_ran_flat(r,0,100) < rArrivalRate)
				enQueue(rightQ);
		}
		
		/*	Check which side light is green for and if there are cars in said queue.	*/

		if (lightColour == 0 && !isEmpty(leftQ))
		{
			carWait = deQueue(leftQ);
			data->lNumMoves++;	
			data->lTotalWait += carWait;
				
			if (carWait > data->lMaxWait)
				data->lMaxWait = carWait;
		}
		else if (lightColour == 1 && !isEmpty(rightQ))
		{
			carWait = deQueue(rightQ);
			data->rNumMoves++;
			data->rTotalWait += carWait;
			
			if (carWait > data->rMaxWait)
				data->rMaxWait = carWait;
		}
		
		/*	Check if the number of iterations >= 500 so no new cars are
 		*	being added so now just waiting to clear hence increase the
 		*	clearance numbers.						*/

		if (iterations >= 500)
		{
			if (!isEmpty(leftQ))
				data->lClearance++;
			if (!isEmpty(rightQ))
				data->rClearance++;
		}

		incrementWaitTime(leftQ);
		incrementWaitTime(rightQ);
	}
	
	data->lTotalWait /= data->lNumMoves;
	data->rTotalWait /= data->rNumMoves;
	
	/*	Free the memory asigned to both queues.	*/

	free(leftQ);

	free(rightQ);

	return data;
}

/*	This function is used to setup the gsl functions,
 *	it creates a pointer to a gsl_rng struct which is
 *	used to create the random numbers in the simulation.
 *	
 *	This function also seeds the random number sequence
 *	using the time when the program is run.		*/
gsl_rng* setupRandom()
{
	const gsl_rng_type *T;

        gsl_rng *r;

        gsl_rng_env_setup();

        T = gsl_rng_default;

        r = gsl_rng_alloc(T);

        gsl_rng_set(r, time(0));
	
	return r;
}

/*	This function is used to create a new pointer to
 *	a blank SimData structure which can be used to
 *	store the results of a simulation.		 */
struct SimData* createSimData()
{
	struct SimData* data;
	if ( !(data = (struct SimData*)malloc(sizeof(struct SimData)) ) )
	{
		fprintf(stderr, "error %d: Out of memory creating new SimData struct.", errno);
		exit(1);
	}
	data->lMaxWait = data->lNumMoves = data->lTotalWait = data->lClearance = 0;
	data->rMaxWait = data->rNumMoves = data->rTotalWait = data->rClearance = 0;
	return data;
}
