#ifndef UNIFORMGENERATOR_HPP
#define UNIFORMGENERATOR_HPP
#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
using namespace std;
class UniformGenerator
{
   public:
      UniformGenerator();
      vector<vector<double> > GenerateWeightVectors(int Objectives, int N);
      
   private:
      vector <int> generateFirstPrimes(int k);
};
#endif

UniformGenerator::UniformGenerator()
{

}
/**
   Create a list of firt primes with the sieve 
**/
vector <int> UniformGenerator::generateFirstPrimes(int k)
{
  vector<int> primes;
   int count = 0;
   long long _sieve_size = 1000001;
   bitset<10000010> bs;
   bs.set(); //set bits to 1
   bs[0] = bs[1] = 0;
   for(long long i = 2; i <=_sieve_size; i++)
   {
      if(bs[i])
	{
	   for(long long j = i*i; j <= _sieve_size; j +=i)bs[j]=0;
	   primes.push_back((int) i);
	   count++;
	}
	if(count > k)break;
   }
   return primes;
}
/**
  Here the hammersley method is implemented....
**/
vector<vector<double> > UniformGenerator::GenerateWeightVectors(int Objectives, int N)
{
   vector<vector<double > > designs;
   vector<int> primes = generateFirstPrimes(Objectives-2);
   for(int i = 0 ; i < N; i++)
   {
      vector<double> design(Objectives, 0.0);
      design[0] = (2.0*(i+1.0) - 1.0) / (2.0*N);
      for(int j = 1; j < Objectives-1; j++)
      {
	   double f = 1.0/primes[j-1];
	   int d = i+1;
	   design[j] = 0.0;
	   while(d > 0)
	   {
		design[j] += f*(d % primes[j-1]);
		d = d / primes[j-1]; // Here the floor is considered as part of the C++ language.....
		f = f / primes[j-1];
	   }
      }
	designs.push_back(design);
   }
 // The designs are transformed to weight vectors....
   vector<vector< double > > Weights;
   for(int i = 0; i < designs.size(); i++)
   {
  	vector<double> Weight(Objectives); 
	for(int j = 1; j <= Objectives; j++)
	{
	   if(i == Objectives)
	 	Weight[j-1] = 1.0;
	   else
		Weight[j-1] = 1.0 - pow(designs[i][j-1], 1.0/(Objectives-j));
	for(int k = 1; k <= j-1; k++)
	       Weight[j-1] *=  pow( designs[i][k-1], 1.0/(Objectives-k) );
	}
	Weights.push_back(Weight);
   } 
   return Weights;
}


