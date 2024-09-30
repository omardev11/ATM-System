
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "MyBankLib.h"

const string ClientsFileName = "clients.txt";
using namespace AtmSystem;
using namespace std;

int main()
{
	LoginAtm(ClientsFileName);
}


