//==================================================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//==================================================================================================================================
//Defining structure flightseats
struct flightseats {
	char seatid[3];
	int seatavail;
	char lname[20];
	char fname[20];
};

//==================================================================================================================================
//Declaring all functions/procedures
void flightmenu(void);
void optmenu(void);
void showseats(struct flightseats *, int);
void assignseat(struct flightseats *, char *);
void createorload(struct flightseats *, char *);
void removeseat(struct flightseats *, char *);
int updateseats(struct flightseats *, char *);
void initiateall(struct flightseats *,struct flightseats *,struct flightseats *,struct flightseats *);
void structstandby(struct flightseats *);
void cleanempty(void);

//==================================================================================================================================
int main(void)
{

	//Declaration of variables
	FILE *in;
	int i = 0, nflag = 0, optisfound = 0, ascount = 0, mflag = 0;
	char choice[2], flightid[6];
	//Preparing for enum
	enum spectrum {a, b, c, d, e};
	const char * opts[] = {"a", "b", "c", "d", "e"};
	enum spectrum optalp;

	//Declaring a pointer of flightseats structure
	struct flightseats * point;

	//Declaring flightseats structures for different flights
	struct flightseats CO102[12];
	struct flightseats CO311[12];
	struct flightseats CO444[12];
	struct flightseats CO519[12];
	
	//Initialising all declared structures and assign default values
	initiateall(CO102, CO311, CO444, CO519);

	//Cleaning the cmd
	system("clear");
	//Calling function to show first menu, and listen for response from user
	flightmenu();
	printf("Choose a flight: ");
	choice[0] = getchar();					//fgets(choice, 2, stdin);
	
	//Continue loop until option e (quit) is selected
	while (mflag == 0)
	{

		//Filtering whether options are within a,b,c,d,e and flags if valid
		for (optalp = a; optalp <= e; optalp++)
		{
			if (strcmp(choice, opts[optalp]) == 0)
			{
				optisfound = 1;
				break;
			}
	
		}
		
		//Find out the option user chose when valid flag
		if (optisfound == 1)
			
			//For option a,b,c,d pointer will set to flight structure, and copy flight id
			//For option e, exit flag will be set
			switch (optalp)
			{				

				case a:		
						point = CO102;
						strcpy(flightid, "CO102");
						break;
				case b:
						point = CO311;
						strcpy(flightid, "CO311");
						break;				
				case c:
						point = CO444;
						strcpy(flightid, "CO444");			
						break;				
				case d:
						point = CO519;
						strcpy(flightid, "CO519");
						break;				
				case e:
						mflag = 1;
						break;
						
			}

		else
			//Option outside a,b,c,d,e was entered
			puts("Invalid option. Please try again");
		
		//Reset for next loop
		optisfound = 0;
		
		//mflag is always 0 unless option e (quit) was selected
		if (mflag == 0)
		{

			//Loads the flight info from .dat file
			createorload(point, flightid);
			//Clean up the screen and prepare for menu for the selected flight
			system("clear");
			optmenu();
			//	Now to confirm what this does? !!!!!!!!!!!!!!!!!!!!!!!!
			cleanempty();
			//Wait for user response
			printf("Choose an option: ");
			choice[0] = getchar();			//fgets(choice, 2, stdin);

			//Check if option in a,b,c,d,e while menu for the selected flight
			while (nflag == 0)	
			{

				for (optalp = a; optalp <= e; optalp++)
				{
					if (strcmp(choice, opts[optalp]) == 0)
					{
						optisfound = 1;
						break;
					}
		
				}
			
				//When options a,b,c,d,e was chose
				if (optisfound == 1)
			
					switch (optalp)
					{
			
						case a	:	
									//Inititates available seat counter
									ascount = 0;
									//Plus one if seat available is true
									for (i = 0; i < 12; i++)
										if (((point+i)->seatavail) == 1)
											ascount++;
									//Shows available seat count on cmd
									printf("There are %d seats available in this flight\n", ascount);
									printf("Press [enter] to continue");
									for (i = 0; i < 2; i++)
										cleanempty();
									break;				
						case b	:
									//Showing current seats availablility, with 'XX' for unavailable seats
									showseats(point, 1);
									printf("Press [enter] to continue");							
									for (i = 0; i < 2; i++)
										cleanempty();
									break;				
						case c	:
									//Showing current seats availablility, with 'XX' for unavailable seats
									showseats(point, 1);
									//Calling the seat reserve procedure
									assignseat(point, flightid);					
									break;				
						case d	:
									//Showing current reserved seats, with 'XX' for available seats
									showseats(point, 0);
									//Calling the seat free-up procedure
									removeseat(point, flightid);
									break;				
						case e	:	
									//Option to quit and return to flights selection menu
									nflag = 1;
									break;
					}
								
				else
					puts("Invalid option. Please try again");
			
				optisfound = 0;
			
				if (nflag == 0)
				{	
					system("clear");
					optmenu();
					printf("Choose an option: ");
					choice[0] = getchar();			//fgets(choice, 2, stdin);
				}
				
			}
		
			nflag = 0;
			cleanempty();
			system("clear");			
			flightmenu();
			printf("Choose a flight: ");
			choice[0] = getchar();			//fgets(choice, 2, stdin);
		
		}
	
	}
	
	system("clear");
	puts("\nOperaton terminated.\n");

	return 0;
	
}

//==================================================================================================================================
//Menu for choosing flights
void flightmenu(void)
{

	puts("\n************************************************************");
	puts("Please choose a flight below:");
	puts("************************************************************");	
	puts("a) CO102");
	puts("b) CO311");
	puts("c) CO444");
	puts("d) CO519");
	puts("e) Quit");
	puts("************************************************************\n");
		
}

//==================================================================================================================================
//Menu for choosing actions
void optmenu(void)
{

	puts("\n************************************************************");
	puts("To choose a function, enter its letter label:");
	puts("************************************************************");	
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Assign a customer to a seat assignment");
	puts("d) Delete a seat assignment");
	puts("e) Quit");
	puts("************************************************************\n");
		
}

//==================================================================================================================================
//Mode 1 is for showing available seats; Mode 0 is for showing reserved seats
void showseats(struct flightseats * ptr, int mode)
{

	//Declaration of variables
	int i;
	
	//Show message and filter seats based on mode
	if (mode == 1)
		puts("\nSeat availability:");
	else
		puts("\nCurrently reserved seats:");
	puts("==================");
	for (i = 0; i < 12; i++)
	{
		if (((ptr+i)->seatavail) == mode)
			printf("%-6s ", (ptr+i)->seatid);
		else
			printf("%-6s ", "XX");
		if (((i+1) % 3) == 0)
			printf("\n");									
	}
	puts("==================\n");	

}

//==================================================================================================================================
//Reserve seat with the pointer for selected flight and the file storing flight seat info
void assignseat(struct flightseats * ptr, char * filename)
{

	//Declaration of variables
	char seatbuff[3], lnamebuff[20], fnamebuff[20];
	int i = 0, sreserve = 0, nflag = 0;
	
	cleanempty();
	
	//Wait for user response for seat reservation
	printf("Choose an available seat: ");
	fgets(seatbuff, 3, stdin);
	seatbuff[2] = '\0';	
	
	//Check the availability of seat, flags if available for reserve
	for (i = 0; i < 12; i++)
	{
		if (strcmp(seatbuff, (ptr+i)->seatid) == 0)
			if ((ptr+i)->seatavail == 1)
			{
				sreserve = 1;
				break;
			}
	}
	
	//End without making the reservation when the seat is not available
	if (sreserve == 0)
		puts("Reservation process unsuccessful!");
	else
	{
		cleanempty();
		
		//Taking user response for the reservation
		printf("Please enter the Last name for the reservation: ");
		gets(lnamebuff);
		printf("Please enter the First name for the reservation: ");
		gets(fnamebuff);
		
		//Confirm the input from user
		printf("The seat for %s %s is %s\n", fnamebuff, lnamebuff, seatbuff);
		printf("Confirm? (y/n): ");

			if (getchar() == 'y')
				nflag = 1;
			if (getchar() == 'n')
				nflag = 0;
		
		//If user confirms the booking, pass all values to update the seat reservation
		if (nflag == 1)
		{	
			(ptr+i)->seatavail = 0;
			strcpy((ptr+i)->lname, lnamebuff);
			strcpy((ptr+i)->fname, fnamebuff);
			if (updateseats(ptr, filename) == 1)
				printf("Seat %s has been reserved for %s %s!\n", seatbuff, fnamebuff, lnamebuff);
			else
				printf("Error encountered! Seat reservation unsuccessful!");
		}
		
	}

}

//==================================================================================================================================
//Reading all records from the data file for the selected flight
void createorload(struct flightseats * ptr, char * filename)
{

	//Declaration of variables
	char locationname[40];
	int i = 0;
	FILE *in;
	
	//Assigning combination of filename and file extension to local variable
	sprintf(locationname, "%s.dat", filename);

	//Attempts to open the file with read permission to see whether the file exists
	if ((in = fopen(locationname, "r")) == NULL)
	{
		//If the file doesn't exist, terminate the attempt and open in append mode to create the file
		fclose(in);
		in = fopen(locationname, "a");
		fclose(in);
	} else {
		
		//If the file does exist, read all seat reservation records from the file
		for (i = 0; i < 12; i++)
		{
			fscanf(in, "%s", (ptr+i)->seatid);
			fscanf(in, "%d", &(ptr+i)->seatavail);
			fscanf(in, "%s", (ptr+i)->lname);
			fscanf(in, "%s", (ptr+i)->fname);
		}
			
		fclose(in);
	}	

}

//==================================================================================================================================
//Cancel the booking for a seat on a selected flight
void removeseat(struct flightseats * ptr, char * filename)
{

	//Declaration of variables
	char seatbuff[3];
	int i = 0, sreserve = 0, nflag = 0;

	cleanempty();
	
	//Wait for user response to cancel a seat reservation
	printf("Choose a reserved seat: ");
	fgets(seatbuff, 3, stdin);
	seatbuff[2] = '\0';	
	
	//Checks the reservation status of the seat selected by the user
	for (i = 0; i < 12; i++)
	{
		if (strcmp(seatbuff, (ptr+i)->seatid) == 0)
			if ((ptr+i)->seatavail == 0)
			{
				sreserve = 1;
				break;
			}
	}
	
	//If the validation does not pass there will be no changes for the procedure
	if (sreserve == 0)
		puts("Reservation process unsuccessful!");
	else
	{
		cleanempty();
		//Confirms with user before the cancellation into effect
		printf("This will remove seat %s reservation for %s %s\n", (ptr+i)->seatid, (ptr+i)->fname, (ptr+i)->lname);
		printf("Confirm? (y/n): ");

		if (getchar() == 'y')
			nflag = 1;
		if (getchar() == 'n')
			nflag = 0;
		
		//Reset the values of the seat to nothing, making it available for booking
		if (nflag == 1)
		{	
			(ptr+i)->seatavail = 1;
			strcpy((ptr+i)->lname, "n/a");
			strcpy((ptr+i)->fname, "n/a");
			if (updateseats(ptr, filename) == 1)
				printf("This seat has been made available");
			else
				printf("Error encountered! Seat reservation unsuccessful!");
		}				
		
	}

}

//==================================================================================================================================
//Updates the reservation status for the selected flight
int updateseats(struct flightseats * ptr, char * filename)
{

	//Declaration of variables
	FILE *in;
	int i;
	char filelocation[256], buff[46];
	
	//Assigning combination of filename and file extension to local variable
	sprintf("/", filelocation, "%s.dat", filename);
	
	//Checks if the file exists
	if ((in = fopen(filelocation, "w")) == NULL)
		return 0;
	else
	{	
		//Writes all seat reservation info for the flight into the data file
		for (i = 0; i < 12; i++)
		{
			sprintf(buff, "%s %d %s %s\n", (ptr+i)->seatid, (ptr+i)->seatavail, (ptr+i)->lname, (ptr+i)->fname);
			fputs(buff, in);
		}
		
		//If the file could not be closed, return update unsuccessful by signal of integer '1'
		if (fclose(in) == 0)
			return 1;
		else
			return 0;
	
	}


}

//==================================================================================================================================
//Initiates all the flight structs with default values
void initiateall(struct flightseats * CO102, struct flightseats * CO311, struct flightseats * CO444, struct flightseats * CO519)
{

	structstandby(CO102);
	structstandby(CO311);
	structstandby(CO444);
	structstandby(CO519);		
	
}

//==================================================================================================================================
//Initiates the flight structs with default values to ready the struct
void structstandby(struct flightseats * ptr)
{
	
	//Declaration of variables
	int i = 0;
	char seatno[12][4] = {"1A", "1B", "1C", "2A", "2B", "2C", "3A", "3B", "3C", "4A", "4B", "4C"};

	for (i = 0; i < 12; i++)
	{
		strcpy((ptr+i)->seatid, *(seatno+i));
		(ptr+i)->seatavail = 1;
		strcpy((ptr+i)->lname, "n/a");
		strcpy((ptr+i)->fname, "n/a");
	}

}

//==================================================================================================================================

void cleanempty(void)
{

	while (getchar() != '\n')
		continue;
		
}

//==================================================================================================================================