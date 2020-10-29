/**
David Dejmal xdejma00 
BMS VUT FIT 2020 projekt - konvolucniho koder
*/

#include <iostream>
#include <iterator>
#include <string.h>
#include <bitset>
#include <algorithm>

using namespace std;

void encrypt(string message);
void decrypt(string cipher);

//slouzi pouze pro zpracovani argumentu a ocisteni vstupu
//predava rizeni funkcim encrypt a decrypt. neocekava vraceni toku rizeni
int main(int argc, char **argv)
{
//-------------ZPRACOVANI ARGUMENTU	--------------------
	if(argc!=2)	
	{
		cerr << "Spatny pocet argumentu";
		return 1;
	}
	//cout<<argv[1]<<argc<<endl;
	
	//nacteni vstupu i s whitespace, pozor \n na konci	
	istreambuf_iterator<char> begin(std::cin), end;
	string vstup(begin, end);
	//cout << vstup;
	
	if(strcmp(argv[1],"-e")==0)
	{
		//cout<<"Prepinac E:"<< vstup <<endl;
		//Osetreni vstupu
		string message("");
		for(int i=0;i<vstup.length();i++)
		{
			if((isdigit(vstup[i]))||(islower(vstup[i]))||(isupper(vstup[i])))
			{	
				message+=vstup[i];
			}
			
		}
		//cout<<"message:"<<message<<endl;	
		//funkce e s orezanym vstupem
		if(message.length()!=0)
		{
			encrypt(message);
		}
		else
		{
			cerr << "Nevalidni vstup, neni co sifrovat"<<endl;
		}
			
	}
	else if(strcmp(argv[1],"-d")==0)
	{
		cout<<"Prepinac D:"<< vstup<<endl;
		//Osetreni vstupu na [0,1]
		string cipher("");
		for(int i=0;i<vstup.length();i++)
		{
			if((vstup[i]=='1')||(vstup[i]=='0'))
			{	
				cipher+=vstup[i];
			}
			
		}
		cout<<"cipher:"<<cipher<<endl;
		//funkce d s orezanym vstupem
		if(cipher.length()!=0)
		{
			decrypt(cipher);
		}
		else
		{
			cerr << "Nevalidni vstup, neni co desifrovat"<<endl;
		}
	}
	else
	{
		cerr << "Neznamy argument, usage ./bms -e <<< [a-z][A-Z][0-9] nebo ./bms -e <<< [0,1]"<<endl;
	}
}


void encrypt(string message)
{
	//cout<<"encrypt"<<endl;
	
	//prevod message na bite stream
	string bit_stream_chars("");
	string help_bit;
	for(int i=0;i<message.length();i++)
	{
		//zarovnani na 8 bitu
		help_bit = bitset<8>(message[i]).to_string();
		//cout<<help_bit;
		bit_stream_chars+=help_bit;		
	}
	//cout<<bit_stream_chars<<endl;
	
	

	int bit_stream[bit_stream_chars.length()+6];
	//zarovnani s pametovymi bloky
	//6x nula na konce zpravy
	for(int i=0;i<6;i++)
	{
		bit_stream[i]=0;
	}	
	//dummy converze na pole intu
	for(int i=6;i<bit_stream_chars.length()+6;i++)
	{
		//POZOR - neosetrene, vstup pouze ['0','1']
		bit_stream[i]=bit_stream_chars[i-6]-48;
		//cout<<bit_stream[i];	
	}
	

	//reverse pole
	int start=0,end=bit_stream_chars.length()+5;
	while (start < end)
    {
        int temp = bit_stream[start]; 
        bit_stream[start] = bit_stream[end];
        bit_stream[end] = temp;
        start++;
        end--;
    } 
	//cout<<endl;
	//debug vypis
	/*
	for(int i=0;i<bit_stream_chars.length()+6;i++)
	{
		cout<<bit_stream[i];
	}
	cout<<endl;
	cout<<endl;
	*/
	//konvolucni logika s postupnym vypisem
	int jadro[6] = {0,0,0,0,0,0};
	//debug vypis jadra
	/*
	cout<<"Jadro "<<"start"<<":";
	for(int j=0;j<6;j++)
	{
		cout<<jadro[j];
	}
	*/
	//cout<<endl;
	
	string vypis;
	for(int i=0;i<bit_stream_chars.length()+5;i++)
	{
		//posun - shift jadra
		for(int j=5;j>0;j--)
		{
			jadro[j] = jadro[j-1];
		}
		jadro[0]=bit_stream[i];
		//debug
		/*
		cout<<"Jadro "<<i<<":";
		for(int j=0;j<6;j++)
		{
			cout<<jadro[j];
		}
		cout<<endl;
		*/
		//vypocet 2x
		
		vypis+=to_string((jadro[0]+jadro[2]+jadro[3]+jadro[4])%2);
		vypis+=to_string((jadro[0]+jadro[1]+jadro[3]+jadro[5])%2);
	}
	//reverse vypisu
	reverse(vypis.begin(), vypis.end()); 
	
	//finalni vypis
	cout<<vypis;
	
	exit(0);
}
void decrypt(string cipher)
{
	cout<<"decrypt";
	exit(0);
}