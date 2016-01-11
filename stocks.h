#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <fstream>
#include "P2.h"

using namespace std;

// Struct for a Buyer client 
struct Buyer {
	Buyer(int Timestamp_in, int clientid_in, int wtobf_in,
		int amount_in, int order_in);
	int Timestamp;
	int clientid;
	int wtobf;
	int amount; 
	int order;
};

// Buyer constructor definition
Buyer::Buyer(int Timestamp_in, int clientid_in, int wtobf_in, int amount_in, int order_in)
	: Timestamp(Timestamp_in), clientid(clientid_in), wtobf(wtobf_in),
		amount(amount_in), order(order_in) {}

// Struct for a Seller client 
struct Seller {
	Seller(int Timestamp_in, int clientid_in, int wtobf_in,
		int amount_in, int order_in);
	int Timestamp;
	int clientid;
	int wtosf;
	int amount;
	int order;
};

// Seller constructor definition
Seller::Seller(int Timestamp_in, int clientid_in, int wtosf_in, int amount_in, int order_in)
	: Timestamp(Timestamp_in), clientid(clientid_in), wtosf(wtosf_in),
		amount(amount_in), order(order_in) {}

// Struct for Client 
// This is different from the Buyer and Client structs.
// It is the for the client output
struct Client {
	Client(int ID_in, int numbought_in, int numsold_in, int nettransfer_in);
	int ID;
	int numbought;
	int numsold;
	int nettransfer;
};

Client::Client(int ID_in, int numbought_in, int numsold_in, int nettransfer_in) 
	: ID(ID_in), numbought(numbought_in), numsold(numsold_in),
		nettransfer(nettransfer_in) {}

// Comparator for the Buyer priority queue
// Makes the priority queue a max PQ
class CompareBuyers {
 public:
	bool operator() (Buyer& buyer1, Buyer& buyer2) {
	 	if(buyer1.wtobf == buyer2.wtobf) {
	 		return buyer2.order < buyer1.order; 
	 	}
	 	else {
	 		return buyer1.wtobf < buyer2.wtobf; 
	 	}
	}

};

// Comparator for the Seller priority queue
// Makes the priority queue a min PQ
class CompareSellers {
 public:
	bool operator() (Seller& seller1, Seller& seller2) {
	 	if(seller2.wtosf == seller1.wtosf) {
	 		return seller2.order < seller1.order; 
	 	}
	 	else {
	 		return seller2.wtosf < seller1.wtosf; 
	 	}

	 }

};

// Comparator for the primary median priority queue
// Makes the priority queue a max PQ
class CompareMedian {
 public:
 	bool operator() (int& median1, int& median2) {
 		if(median1 <= median2) {
 			return true;
 		}
 			return false;
 	}
};

// Comparator for the secondary median priority queue
// Makes the priority queue a min PQ
class CompareMedianReverse {
 public:
 	bool operator() (int& median1, int& median2) {
 		if(median2 <= median1) {
 			return true;
 		}
 			return false; 
 	}
};

struct Equity {
	Equity(bool medianprint_in, int numoftransactions_in, bool bought_in, bool sold_in,
	int sold_order_in, int buy_order_in, int profit_in, int tt_profit_buy_in, int tt_profit_sell_in, 
	int tt_timestamp_buy_in, int tt_timestamp_sell_in, int tt_ts_buy_final_in,
	int tt_ts_sell_final_in); 
	bool medianprint;
	int numboftransactions;
	bool bought;
	bool sold;
	int sold_order;
	int buy_order;
	// Variables for Time Travelers
	int profit;
	int tt_profit_buy;
	int tt_profit_sell;
	int tt_timestamp_buy; 
	int tt_timestamp_sell;
	int tt_ts_buy_final;
	int tt_ts_sell_final; 
	priority_queue<int, vector<int>, CompareMedian> median;
	priority_queue<int, vector<int>, CompareMedianReverse> medianstorage; 
	priority_queue<Buyer, vector<Buyer>, CompareBuyers> buy;
	priority_queue<Seller, vector <Seller>, CompareSellers> sell;
};

Equity::Equity(bool medianprint_in, int numoftransactions_in, bool bought_in, bool sold_in,
	int sold_order_in, int buy_order_in, int profit_in, int tt_profit_buy_in, int tt_profit_sell_in, 
	int tt_timestamp_buy_in, int tt_timestamp_sell_in, int tt_ts_buy_final_in,
	int tt_ts_sell_final_in) 
	: medianprint(medianprint_in), numboftransactions(numoftransactions_in),
		bought(bought_in), sold(sold_in), sold_order(sold_order_in), 
		  buy_order(buy_order_in), profit(profit_in), tt_profit_buy(tt_profit_buy_in),
			tt_profit_sell(tt_profit_sell_in), tt_timestamp_buy(tt_timestamp_buy_in),
				tt_timestamp_sell(tt_timestamp_sell_in), tt_ts_buy_final(tt_ts_buy_final_in),
				tt_ts_sell_final(tt_ts_sell_final_in) {}

class Stockmarket {
 public: 
	vector<Equity> equityvector;
	vector<Client> clientvector;
	void stockfunc(ostringstream &os, bool verbose, bool median, bool client_info, 
			bool time_travelers);
	bool matchfunc(vector<Equity> &equityvector, const Buyer &buyer, const Seller &seller,
	bool bors, int EID);
	void verboseprinting(ostringstream &os,int CIDbuyer, int CIDseller, int shares, 
		int equity, int price);
	void medianprinting(ostringstream &os, vector<Equity> &equityvector, int numofequities, int timestamp);
	void client_infoprinting(ostringstream &os, vector<Client> &clientvector, int numofclients);
	void timetravelersprinting(ostringstream &os, vector<Equity> &equityvector, int numequities);
};

void Stockmarket::timetravelersprinting(ostringstream &os, vector<Equity> &equityvector, int numequities) {
	for(int c = 0; c < numequities; ++c) {
		
		if(equityvector[c].profit < 0 || equityvector[c].profit == 0) {
			os << "A time traveler would buy shares of Equity " << c <<
			" at time: -1 and sell these shares at time: -1\n";

		}
		else {
			os << "A time traveler would buy shares of Equity " << c <<
			" at time: " << equityvector[c].tt_ts_buy_final << 
				" and sell these shares at time: " << 
					equityvector[c].tt_ts_sell_final << '\n';
		}
		
	}
}


void Stockmarket::client_infoprinting(ostringstream &os, vector<Client> &clientvector, int numofclients) {
	for(int c = 0; c < numofclients; ++c) {
		os << "Client " << c << " bought " << clientvector[c].numbought <<
			" and sold " << clientvector[c].numsold << " for a net transfer of $"
				<< clientvector[c].nettransfer << '\n';
	}
}

// Median is printed out with two priority queues, pop off the primary
// priority queue until you reach the median (storing them in the
// secondary priority queue). Restore the original priority queue 
// by popping off the secondary PQ and and pushing into the original
void Stockmarket::medianprinting(ostringstream &os, vector<Equity> &equityvector, int numofequities, 
	int timestamp) { 
	for(int EID = 0; EID < numofequities; ++EID) {
		if(equityvector[EID].medianprint) {
			if(equityvector[EID].numboftransactions % 2 == 0) {
				for(int i = 0; i < (equityvector[EID].numboftransactions / 2); ++i) {
					equityvector[EID].medianstorage.push(equityvector[EID].median.top());
					equityvector[EID].median.pop(); 
				}
				os << "Median match price of Equity " << EID 
				<< " at time " << timestamp << " is $" << (equityvector[EID].median.top() 
					+ equityvector[EID].medianstorage.top())/2 << '\n';
			}
			else {
				for(int i = 0; i < (equityvector[EID].numboftransactions / 2) + 1; ++i) {
					equityvector[EID].medianstorage.push(equityvector[EID].median.top());
					equityvector[EID].median.pop();
				}
				os << "Median match price of Equity " << EID 
				<< " at time " << timestamp << " is $" << equityvector[EID].medianstorage.top() << '\n';
			}
			while(!equityvector[EID].medianstorage.empty()) {
					equityvector[EID].median.push(equityvector[EID].medianstorage.top());
					equityvector[EID].medianstorage.pop();
			}
		}
	}

}

void Stockmarket::verboseprinting(ostringstream &os, int CIDbuyer, int CIDseller, int shares, int equity, int price) {
	os << "Client " << CIDbuyer << " purchased " << shares 
		<< " shares of Equity " << equity << " from Client " 
		<< CIDseller << " for $" << price << "/share\n";
	return;  
}

bool Stockmarket::matchfunc(vector<Equity> &equityvector, const Buyer &buyer, const Seller &seller,
	bool bors, int EID) {
	if(bors) {
		if(buyer.wtobf >= equityvector[EID].sell.top().wtosf) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if(seller.wtosf <= equityvector[EID].buy.top().wtobf) {
			return true;
		}
		else {
			return false;
		}
	}
}


void Stockmarket::stockfunc (ostringstream &os, bool verbose, bool median, bool client_info, bool time_travelers) {
	string baloney, important, timestampstring, CIDstring, buyorsell, 
	EIDstring, moneystring, numberofstring;
	int numberof;
	int timestamp;
	int EID;
	int CID;
	int money;
	int clients = 0;
	int equities = 0; 
	int orders = 0;
	int random_seed = 0;
	int num_of_orders = 0;
	int arrival_rate = 0;
	int ordersprocessed = 0;
	bool PR = false;
	bool pop = false; 

	// Read in the first 3 lines of the input file 
	// to determine TL or PR input
	for(int c = 0; c < 3; ++c) {
		cin >> baloney >> important;
		switch(c) {
			case 0: {
				if(important == "PR") {
					PR = true;
				}
				continue;
			}
			case 1: {
				clients = atoi(important.c_str());
				continue;
			}
			case 2: {
				equities = atoi(important.c_str());
				continue;
			}
		} 
	}

	// Declare stringstream for PR
	stringstream ss; 

	// If the PR mode is true
	if(PR) {
		for(int c = 0; c < 3; ++c) {
			cin >> baloney >> important;
			switch(c) {
				case 0: {
					// Randomness of the orders
					random_seed = atoi(important.c_str());
					continue;
				}
				case 1: {
					// Number of orders
					num_of_orders = atoi(important.c_str());
					continue;
				}
				case 2: {
					// Orders per timestamp
					arrival_rate = atoi(important.c_str());
					continue;
				} 
			}
		}
		// PR intializer function
		P2::PR_init(ss, random_seed, equities, clients, num_of_orders, arrival_rate);
	}

	// If PR is true, inputStream is ss
	// else, inputStream is cin
	istream& inputStream = PR ? ss : cin;

	// Setting size for equity and client vector
	equityvector.reserve(equities);
	clientvector.reserve(clients);

	// Constructing equities and pushing into the vector
	for(int c = 0; c < equities; ++c) {
		equityvector.push_back(Equity(false, 0, false, false, 0, 0, 0, 0, 0, 0, 0, -1, -1));
	} 

	// Constructing clients and pushing into the vector
	for(int x = 0; x < clients; ++x) {
		clientvector.push_back(Client(x, 0, 0, 0));
	}

	int timestamptracker = 0;
	bool bors;
	os << "Processing orders...\n"; 
	while(inputStream >> timestampstring >> CIDstring >> buyorsell >> EIDstring >> moneystring >> numberofstring) {
		timestamp = atoi(timestampstring.c_str());
		if(timestamp < 0) {
			cerr << "Timestamp is a negative integer" << '\n';
			exit(1);
		}

		CID = atoi((CIDstring.substr(1)).c_str()); 
		EID = atoi((EIDstring.substr(1)).c_str());

		if(CID < 0 || CID >= clients || EID < 0 || EID >= equities) {
			cerr << "Client ID and/or Equity ID is/are not within their respective ranges\n";
			exit(1);
		}
			
		money = atoi((moneystring.substr(1)).c_str()); 
		numberof = atoi((numberofstring.substr(1)).c_str());
		if(money <= 0 || numberof <= 0) {
			cerr << "Price and/or Quantity is/are not positive\n";
			exit(1);
		}
			
		if(timestamp < timestamptracker) {
			cerr << "Timestamp does not increase\n";
			exit(1);
		}

		if(timestamp != timestamptracker) {
			if(median) {
				medianprinting(os, equityvector, equities, timestamptracker);
			}
		}

		timestamptracker = timestamp; 
			
		if(buyorsell == "BUY") {
			bors = true;
			Buyer currentbuyer = Buyer(timestamp, CID, money, numberof, orders);
			while(!equityvector[EID].sell.empty() && matchfunc(equityvector, currentbuyer, 
				equityvector[EID].sell.top(), bors, EID)) {
				ordersprocessed++;
				pop = false;
				Seller &tempseller = const_cast<Seller&>(equityvector[EID].sell.top());
					if(currentbuyer.amount > tempseller.amount) {
						if(verbose) {
							verboseprinting(os, currentbuyer.clientid, tempseller.clientid, tempseller.amount,
							EID, tempseller.wtosf);
						} 
						if(client_info) {
							clientvector[currentbuyer.clientid].numbought += tempseller.amount;
							clientvector[tempseller.clientid].numsold += tempseller.amount;
							clientvector[currentbuyer.clientid].nettransfer -= (tempseller.wtosf * tempseller.amount);
							clientvector[tempseller.clientid].nettransfer += (tempseller.wtosf * tempseller.amount);
						}
						
						currentbuyer.amount = currentbuyer.amount - tempseller.amount; 
						pop = true;
					}
					else if(currentbuyer.amount < tempseller.amount) {
						if(verbose) {
							verboseprinting(os, currentbuyer.clientid, tempseller.clientid, currentbuyer.amount,
							EID, tempseller.wtosf);
						}
						if(client_info) {
							clientvector[currentbuyer.clientid].numbought += currentbuyer.amount;
							clientvector[tempseller.clientid].numsold += currentbuyer.amount;
							clientvector[currentbuyer.clientid].nettransfer -= (tempseller.wtosf * currentbuyer.amount);
							clientvector[tempseller.clientid].nettransfer += (tempseller.wtosf * currentbuyer.amount);
						}
						tempseller.amount = tempseller.amount - currentbuyer.amount;
						currentbuyer.amount = 0;
					}
					else {
						if(verbose) {
							verboseprinting(os, currentbuyer.clientid, tempseller.clientid, currentbuyer.amount,
							EID, tempseller.wtosf);
						}
						if(client_info) {
							clientvector[currentbuyer.clientid].numbought += tempseller.amount;
							clientvector[tempseller.clientid].numsold += tempseller.amount;
							clientvector[currentbuyer.clientid].nettransfer -= (tempseller.wtosf * tempseller.amount);
							clientvector[tempseller.clientid].nettransfer += (tempseller.wtosf * tempseller.amount);
						}
						pop = true;
						currentbuyer.amount = 0;
					}
					if(median) {
						equityvector[EID].median.push(tempseller.wtosf);
						equityvector[EID].medianprint = true;
						++equityvector[EID].numboftransactions;
					}
					if(pop) {
						equityvector[EID].sell.pop();
					}
					if(currentbuyer.amount == 0) {
						break;
					}
			}

			if(time_travelers) {
				if(equityvector[EID].bought && !equityvector[EID].sold) {
					equityvector[EID].tt_profit_sell = currentbuyer.wtobf;
					equityvector[EID].tt_timestamp_sell = timestamp;
					if(equityvector[EID].tt_profit_sell - equityvector[EID].tt_profit_buy > equityvector[EID].profit) {
						equityvector[EID].profit = equityvector[EID].tt_profit_sell - equityvector[EID].tt_profit_buy;
						equityvector[EID].tt_ts_buy_final = equityvector[EID].tt_timestamp_buy;
						equityvector[EID].tt_ts_sell_final = equityvector[EID].tt_timestamp_sell;
					}
					equityvector[EID].sold = true;
				}
				if(equityvector[EID].sold) {
					if(equityvector[EID].buy_order <= orders) {
						if(equityvector[EID].profit < currentbuyer.wtobf - equityvector[EID].tt_profit_buy) {
							equityvector[EID].profit = currentbuyer.wtobf - equityvector[EID].tt_profit_buy;
							equityvector[EID].tt_ts_buy_final = equityvector[EID].tt_timestamp_buy;
							equityvector[EID].tt_ts_sell_final = timestamp;
						}
						if(currentbuyer.wtobf > equityvector[EID].tt_profit_buy) {
							equityvector[EID].tt_profit_sell = currentbuyer.wtobf;
							equityvector[EID].tt_timestamp_sell = timestamp;
						}
					}
			}
			}
			if(currentbuyer.amount != 0) {
				equityvector[EID].buy.push(currentbuyer);
			}
		}
		else if(buyorsell == "SELL") {
			bors = false;
			Seller currentseller = Seller(timestamp, CID, money, numberof, orders);
			while(!equityvector[EID].buy.empty() && matchfunc(equityvector, equityvector[EID].buy.top(), currentseller,
				bors, EID)) {
				ordersprocessed++;
				pop = false;
				Buyer &tempbuyer = const_cast<Buyer&>(equityvector[EID].buy.top());
				if(currentseller.amount > tempbuyer.amount) {
					if(verbose) {
						verboseprinting(os, tempbuyer.clientid, currentseller.clientid, tempbuyer.amount,
						EID, tempbuyer.wtobf);
					} 
					if(client_info) {
						clientvector[currentseller.clientid].numsold += tempbuyer.amount;
						clientvector[tempbuyer.clientid].numbought += tempbuyer.amount;
						clientvector[currentseller.clientid].nettransfer += (tempbuyer.wtobf * tempbuyer.amount);
						clientvector[tempbuyer.clientid].nettransfer -= (tempbuyer.wtobf * tempbuyer.amount);
					}
					currentseller.amount = currentseller.amount - tempbuyer.amount;  
					pop = true;
				}
				else if(currentseller.amount < tempbuyer.amount) {
					if(verbose) {
						verboseprinting(os, tempbuyer.clientid, currentseller.clientid, currentseller.amount,
						EID, tempbuyer.wtobf);
					}
					if(client_info) {
						clientvector[currentseller.clientid].numsold += currentseller.amount;
						clientvector[tempbuyer.clientid].numbought += currentseller.amount;
						clientvector[currentseller.clientid].nettransfer += (tempbuyer.wtobf * currentseller.amount);
						clientvector[tempbuyer.clientid].nettransfer -= (tempbuyer.wtobf * currentseller.amount);
					}
					tempbuyer.amount = tempbuyer.amount - currentseller.amount;
					currentseller.amount = 0;
					 
				}
				else {
					if(verbose) {
						verboseprinting(os, tempbuyer.clientid, currentseller.clientid, currentseller.amount,
						EID, tempbuyer.wtobf);
					}
					if(client_info) {
						clientvector[currentseller.clientid].numsold += currentseller.amount;
						clientvector[tempbuyer.clientid].numbought += currentseller.amount;
						clientvector[currentseller.clientid].nettransfer += (tempbuyer.wtobf * currentseller.amount);
						clientvector[tempbuyer.clientid].nettransfer -= (tempbuyer.wtobf * currentseller.amount);
					}
					pop = true;
					currentseller.amount = 0;
					 
				}
				if(median) {
					equityvector[EID].median.push(tempbuyer.wtobf);
					equityvector[EID].medianprint = true;
					++equityvector[EID].numboftransactions;
				}
				if(pop) {
					equityvector[EID].buy.pop();
				}
				if(currentseller.amount == 0) {
						break;
				}
				++orders;
			}
			
			if(time_travelers) {
				if(equityvector[EID].bought == false) {
					equityvector[EID].tt_profit_buy = currentseller.wtosf;
					equityvector[EID].tt_timestamp_buy = timestamp;
					equityvector[EID].bought = true;
				}
				else if(equityvector[EID].bought) {
					if(currentseller.wtosf < equityvector[EID].tt_profit_buy) {
						equityvector[EID].tt_profit_buy = currentseller.wtosf;
						equityvector[EID].tt_timestamp_buy = timestamp;
						equityvector[EID].buy_order = orders; 
						equityvector[EID].sold = false;
					}
				}
			}
			if(currentseller.amount != 0) {
				equityvector[EID].sell.push(currentseller);
			}
			
		}
		++orders;
	}
	if(median) {
		medianprinting(os, equityvector, equities, timestamptracker);
	}
	os << "---End of Day---\n";
	os << "Orders Processed: " << ordersprocessed << '\n';
	if(client_info) {
		os << "---Client Info---\n";
		client_infoprinting(os, clientvector, clients);
	} 
	if(time_travelers) {
		os << "---Time Travelers---\n";
		timetravelersprinting(os, equityvector, equities);
	}
}


