/*
 * runSimulations.c
 * This file contains the main function for the entire platform
 * and uses the other files and their contents to run 500
 * simulations and display the average of their results.
 */

#include <runSimulations.h>

/*	This is the main function of the platform and takes in
 *	four parameters from the terminal when the platform is
 *	run. These parameters are used to determine the settings
 *	for each simulation.
 *
 *	The function can output an error message to stderr if any
 *	of the given parameters are of incorrect format or type.	*/
int main(int argc, char **argv)
{	
	
	int numSims = 100;

	int lLightTime = atoi(argv[1]);
	
	int lArrivalRate = atoi(argv[2]);

	int rLightTime = atoi(argv[3]);
	
	int rArrivalRate = atoi(argv[4]);

	
	checkInputParameters(lLightTime, lArrivalRate, rLightTime, rArrivalRate);
	
	printf("Parameter values :\n");
	printf("	from left:\n");
	printf("		traffic arrival rate: 	%d\n", lArrivalRate);
	printf("		traffic light period: 	%d\n", lLightTime);
	printf("        from right:\n");
        printf("                traffic arrival rate:   %d\n", rArrivalRate);
        printf("                traffic light period:   %d\n", rLightTime);

	gsl_rng *r = setupRandom();	

 	struct SimData* averages = createSimData();
	
	int simNum;

	for (simNum=0; simNum<numSims; simNum++)
	{
		struct SimData* data = runOneSimulation(r, lLightTime, lArrivalRate, rLightTime, rArrivalRate);
		
		/*	Add the results of the simulation to the averages. 	*/

		averages->lNumMoves += data->lNumMoves;
		averages->lMaxWait += data->lMaxWait;
		averages->lClearance += data->lClearance;
		averages->lTotalWait += data->lTotalWait;
		
		averages->rNumMoves += data->rNumMoves;
                averages->rMaxWait += data->rMaxWait;
                averages->rClearance += data->rClearance;
                averages->rTotalWait += data->rTotalWait;	
	
		free(data);
	}
	
	/*	Devide the totals by the number of simulations run to calculate the averages.	*/        

	averages->lNumMoves /= numSims;
        averages->lMaxWait /= numSims;
        averages->lClearance /= numSims;
        averages->lTotalWait /= numSims;

	averages->rNumMoves /= numSims;
        averages->rMaxWait /= numSims;
        averages->rClearance /= numSims;
        averages->rTotalWait /= numSims;

	printf("Results (averaged over 100 runs):\n");
	printf("	from left:\n");
	printf("		number of vehicles :	%d\n", averages->lNumMoves);
	printf("                average waiting time :  %d\n", averages->lTotalWait);
	printf("                maximum waiting time    %d\n", averages->lMaxWait);
	printf("                clearance time :        %d\n", averages->lClearance);
	
	printf("        from right:\n");
        printf("                number of vehicles :    %d\n", averages->rNumMoves);
        printf("                average waiting time :  %d\n", averages->rTotalWait);
        printf("                maximum waiting time    %d\n", averages->rMaxWait);
        printf("                clearance time :        %d\n", averages->rClearance);

	free(averages);
	
	gsl_rng_free(r);	

	return 0;
}

/*	This function is used to check the input parameters
 *	to ensure that they are within the required range and
 *	are handled correctly. If any of the parameters are
 *	incorrect then the program is exited and an appropriate
 *	error message is written to stderr.			*/
void checkInputParameters(int lLightTime, int lArrivalRate, int rLightTime, int rArrivalRate)
{
	if (lLightTime <= 0)
	{
		fprintf(stderr, "error %d: Invalid parameter entered, lLightTime must be greater than 0.\n", errno);
		exit(1);
	}
	else if (rLightTime <= 0)
        {
                fprintf(stderr, "error %d: Invalid parameter entered, rLightTime must be greater than 0.\n", errno);
		exit(1);
        }
	else if (lArrivalRate <= 0 || lArrivalRate > 100)
        {
                fprintf(stderr, "error %d: Invalid parameter entered, lArrivalRate must be greater than 0 and less than 101.\n", errno);
        	exit(1);
	}
	else if (rArrivalRate <= 0 || rArrivalRate > 100)
        {
                fprintf(stderr, "error %d: Invalid parameter entered, lLightTime must be greater than 0 and less than 101.\n", errno);
       		exit(1);
	}
}
