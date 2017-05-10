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
      vector<vector<double >> Transformation(vector< vector<double > > & designs, int dim);
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
   vector<int> primes = generateFirstPrimes(Objectives-1);


 //     vector<double> design(Objectives, 0.0);
 //     designs.push_back(design);
   for(int i = 0 ; i < N; i++)
   {
      vector<double> design(Objectives, 0.0);
      //design[0] = (2.0*(i+1.0) - 1.0) / (2.0*N);
      design[0] = (double)( (i) % (N+1)) / (double) N;
      for(int j = 1; j < Objectives; j++)
      {
	   double f = 1.0/primes[j-1];
	   int d = i;
	   design[j] = 0.0;
	   while(d > 0)
	   {
		design[j] += f*(d % primes[j-1]);
		d =   floor((double)d / primes[j-1]); // Here the floor is considered as part of the C++ language.....
		f = f / primes[j-1];
	   }
      }
	designs.push_back(design);
   }

//
//   for(int i = 0; i < N; i++)
//	{
//	for(int j = 0; j < Objectives; j++)
//	cout << designs[i][j] << " ";
//	cout << endl;
//	}
//cout << endl;
 // The designs are transformed to weight vectors....
   return Transformation(designs, Objectives); 
}
/**
   Transformation Fang and Wang 1994
**/
 vector<vector<double> > UniformGenerator::Transformation(vector< vector<double > > & designs, int dim)
{
   vector<vector< double > > U;
  for(int d = 0; d < designs.size(); d++)
   {
  	vector<double> Row(dim); 
	for(int i = 1; i <= dim; i++)
	{
	   if(i == dim)
	 	Row[i-1] = 1.0;
	   else
		Row[i-1] = 1.0 - pow(designs[d][i-1], 1.0/(dim-i));
	for(int j = 1; j <= i-1; j++)
	        Row[i-1] *=  pow( designs[d][j-1], 1.0/(dim-j) );
	}
	U.push_back(Row);
   }
	return U;
}

