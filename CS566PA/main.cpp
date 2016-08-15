#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream inClientFile("input.txt", ios::in);

	// exit program if ifstream could not open the file
	if(!inClientFile)
	{
		cerr << "File cound not be opened. Please place input.txt in same directory." << endl;
		exit(1);
	}
	
	// read input file into array
	int n;
	inClientFile >> n;

	int *inarray;
	inarray = new int[n];

	for(int i = 0;i<n; i++)
	{
		inClientFile >> inarray[i];
		// Uncomment the line below to output the contents of the file number by number
		//cout << inarray[i] << " ";
	}

	int m = 1.2 * n;

	cout << "n = " << n << " m = " << m << endl << endl;

	int *hashTableLinear, *hashTableQuadratic, *hashTableDouble;
	hashTableLinear = new int[m];    // will create hash table of size m, but addressing starts at 0
	hashTableQuadratic = new int[m];
	hashTableDouble = new int[m];

	int cLinear = 0,        // our collision counters & averages for the open addressing methods
		cQuadratic = 0, 
		cDouble = 0; 
	double rLinear, 
		  rQuadratic, 
		  rDouble;


	//initialize the hash table to negative 1 values this will be our empty place value
	for(int i = 0; i<m; i++)
	{
		hashTableLinear[i] = -1;
		hashTableQuadratic[i] = -1;
		hashTableDouble[i] = -1;
	}

	int hPrime1, hPrime2, hki, c1 = 1, c2 = 3;
	bool collision = false;

	// Now for the first run with linear probing
	for(int i = 0; i<n; i++)
	{
		// First calculate h'(k) = k mod m
		hPrime1 = inarray[i] % m;
		int j = 0;

		do
		{
			// Now calculate h(k,i)
			hki = (hPrime1 + j) % m;

			
			if (hashTableLinear[hki] == -1){ // if the hash table's slot is empty
				hashTableLinear[hki] = inarray[i]; 
				collision = false;
			}
			else
			{
				//j++; moved to permit trace output 
				collision = true;
				cLinear++;
			}
			// The line below can be uncommented for trace output
			//cout << "value = " << inarray[i]  << (inarray[i] / 10 != 0?"":" ") << " h'(k) = " << hPrime1 << (hPrime1 / 10 != 0?"":" ") << " i = " << j << " h(k,i) = " << hki << (hki / 10 != 0?"":" ") << " collision = " << collision << " cLinear = " << cLinear << endl;
			if(collision) j++;
		} while(collision && j < m);

	}
	// Now calculate the average collision
	rLinear = double(cLinear) / n;

	// reset collision
	collision = false;

	// Second run now with quadratic probing
	for(int i = 0; i<n; i++)
	{
		hPrime1 = inarray[i] % m;
		int j = 0;

		do
		{
			// Now calculate h(k,i)
			hki = (hPrime1 + (c1 * j) + (c2 * j * j)) % m;

			if (hashTableQuadratic[hki] == -1) // if the hash table's slot is empty
			{	
				hashTableQuadratic[hki] = inarray[i]; 
				collision = false;
			}
			else
			{
				//j++; moved to permit trace output 
				collision = true;
				cQuadratic++;
			}
			// The line below can be uncommented for trace output
			//cout << "value = " << inarray[i]  << (inarray[i] / 10 != 0?"":" ") << " h'(k) = " << hPrime1 << (hPrime1 / 10 != 0?"":" ") << " i = " << j << (j / 10 != 0?"":" ") << " h(k,i) = " << hki << (hki / 10 != 0?"":" ") << " collision = " << collision << " cQuadratic = " << cQuadratic << endl;
			if(collision) j++;
		} while(collision && j < m);

	}
	// Now calculate the average collision
	rQuadratic = double(cQuadratic) / n;

	// Third run now with double hashing
	for(int i = 0; i<n; i++)
	{
		// We already have h1(k) = k mod m, just need to calculate h2(k) = 1 + (k % (m - 1))
		int j = 0;
		hPrime1 = inarray[i] % m;
		hPrime2 = 1 + (inarray[i] % (m - 1));

		do
		{
			// Now calculate h(k,i) = (h1(k) + ih2(k)) mod m
			hki = (hPrime1 + (hPrime2 * j)) % m;

			if (hashTableDouble[hki] == -1){ // if the hash table's slot is empty
				hashTableDouble[hki] = inarray[i]; 
				collision = false;
			}
			else
			{
				//j++;  moved to permit trace output 
				collision = true;
				cDouble++;
			}
			// The 3 lines below can be uncommented for trace output
			//cout << "n= " << i << " h1k = " << inarray[i]  << (inarray[i] / 10 != 0?"":" ") << "%" << m << "=" << hPrime1 << (hPrime1 / 10 != 0?"":" ") 
			//	 << " h2(k) = 1 + " << inarray[i]  << (inarray[i] / 10 != 0?"":" ") << "%" << m - 1 << "=" << hPrime2 << (hPrime2 / 10 != 0?"":" ") 
			//	 << " i = " << j << (j / 10 != 0?"":" ") << " h(k,i) = " << hki << (hki / 10 != 0?"":" ") << " coll? = " << collision << " c = " << cDouble << endl;
			if(collision) j++;
		
		} while(collision && j < m);

	}
	// Now calculate the average collision
	rDouble = double(cDouble) / n;

	cout << "Results: " << endl << endl;

	cout << "Linear probing yields " << cLinear << " collisions and an average collision of " << rLinear << endl << endl;

	cout << "Quadratic probing yields " << cQuadratic << " collisions and an average collision of " << rQuadratic << endl << endl;

	cout << "Double hashing yields " << cDouble << " collisions and an average collision of " << rDouble << endl << endl;

	delete [] inarray,hashTableLinear,hashTableQuadratic,hashTableDouble;
	return 0;
}