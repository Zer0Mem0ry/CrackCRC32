#include <iostream>
#include <string>

#include "CRC.h"

using namespace std;

string numerals = "0123456789";
string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";

// our brute force function
void CrackHash(string source, unsigned int hash, string seed, size_t length)
{
	static const int startTick = GetTickCount64();

	static int iterations; // hold the count of iterations
	static int collisions; // hold the count of collisions / hash

	iterations++; // increment on each execution

	if (length == 0)
	{
		// if input hash matches with seed hash
		if (CRC32(seed.c_str(), seed.length()) == hash)
		{
			// calculate time used
			double endTick = GetTickCount64() - startTick;
			collisions++;

			// output
			cout << "Collision #" << collisions << ", Source: " << seed << ", Hash: 0x" << StrCRC32(seed)
				<< ", Iterations: " << iterations << endl << "Ticks: " << endTick << ", Seconds: "
				<< endTick / 1000 << ", Minutes: " << endTick / 1000 / 60 << ", Hours: " << endTick / 1000 / 60 / 60;
			cout << endl << endl;
		}
		return;
	}

	// iterate through the input stringspace
	for (size_t i = 0; i < source.length(); i++)
	{
		string appended = seed + source[i];

		// continue the loop
		CrackHash(source, hash, appended, length - 1);
	}
}


int main()
{
	// our targethash, which we are going to crack
	unsigned int targetHash = 0xd87f7e0c;

	// loop our crackhash function
	while (1)
	{
		// string startlength
		static unsigned int strlen = 1;
		CrackHash(alphabetLower + alphabetUpper + numerals + specialAnsi,
			targetHash, "", strlen);
		strlen++; // increment the seed length after each iteration
	}
}
