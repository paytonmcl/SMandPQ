#include <iostream>
#include <getopt.h>
#include "stocks.h"
#include <queue>
//#include <sstream>


using namespace std; 

// Declare function main() with parameters:
// argc: count of arguments on the command line 
// argv: array of char pointers to the command line arguments


int main(int argc, char *argv[]) {
	// Declare ostreamstream to flush output directly 
	ios_base::sync_with_stdio(false); 
	ostringstream os;
	// The command line arguments can be:
	static struct option longOpts[] = {
		{"verbose", no_argument, NULL, 'v'},
		{"median", no_argument, NULL, 'm'},
		{"client_info", no_argument, NULL, 'c'},
		{"time_travelers", no_argument, NULL, 't'},
		//{nullptr, 0, nullptr, 0}
	};

	// Variables for each of the flags
	bool verbose = false;
	bool median = false;
	bool client_info = false; 
	bool time_travelers = false; 

	int opt = 0, index = 0; 
	while ((opt = getopt_long(argc, argv, "vmct", longOpts, &index)) != -1) {
		switch(opt) {
			case 'v':
				// An optional flag that indicates verbose output should be 
				// generated 
				verbose = true;
				break;

			case 'm':
				// An optional flag that indicates median output should be 
				// generated 
				median = true;
				break;

			case 'c':
				// An optional flag that indicates that the client details
				// output should be generated
				client_info = true;
				break;

			case 't':
				// An optional flag that indicates that time traveler's 
				// should be generated
			    time_travelers = true;
				break; 

			default:
				// Case for when an invalid flag is read 
				cerr << "One of your flags is not recognizable." << '\n'; 
				exit(1); 
		}
	}
	// Create an instance of the stockmarket 
	Stockmarket stockmarketsim;
	// stockfunc is the main function in which the simulation is run
	stockmarketsim.stockfunc(os, verbose, median, client_info, time_travelers);
	// Flush everything to cout  
	cout << os.str();
	return 0;
}