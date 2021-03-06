/*
   Autor: Joel Chacón Castillo
   Date: 10-may-17

  Generates weights according to a uniform design of mixtures using the Hammersley lo-discrepancy sequence generator. 
This method were proposed by Berenguer and Coello Coello (2015).
References:
    Tan Y., Y. Jiao, H. Li, and X. Wang (2013).  "MOEA/D + uniform design:
        A new version of MOEA/D for optimization problems with many
        objectives."  Computers & Operations Research, 40, 1648-1660.
    Berenguer, J.A.M. and C.A. Coello Coello (2015).  "Evolutionary Many-
        Objective Optimization Based on Kuhn-Munkres' Algorithm."  Evolutionary
        Multi-Criterion Optimization: 8th International Conference, pp. 3-17.
 
*/
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
//      vector<int> primeFactors(int N);
//      int EulerPhi(int N);
      inline int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
	double Discrepance(vector< vector< double> > & d);
        double dist(vector<double> &a, vector<double> &b);

    double RadicalInverse(int index, int base);
   vector< vector< double > > UDM(int Objectives, int N);
void Hammersley( vector< vector< double> > &set, int n, int k);
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
double UniformGenerator::dist(vector<double> &a, vector<double> &b)
{
   double t = 0;
   for(int i = 0; i < a.size(); i++)
   t += pow(a[i]-b[i],2);
   return sqrt(t);
}
double UniformGenerator::Discrepance(vector< vector< double> > & d)
{
   double Average = 0;
   for(int i = 0; i < d.size(); i++)
   {
        double mindis = 1000000;
	for(int j = 0; j < d.size(); j++)
	{
	   if(i==j)continue;
	  if( mindis > dist(d[i], d[j]))
	   {
	    mindis = dist(d[i],d[j]);
	    } 
	}
	Average +=mindis;
   }
   return Average/d.size();
}
vector<vector<double> > UniformGenerator::GenerateWeightVectors(int Objectives, int N)
{

   vector<vector<double > > designs;
 //  designs =  UDM(Objectives, N);
 //  return designs;
  vector<int> primes = generateFirstPrimes(Objectives-1);
 int n = N-Objectives;
 //     vector<double> design(Objectives, 0.0);
 //     designs.push_back(design);
   for(int i = 0 ; i < n; i++)
   {
      vector<double> design(Objectives, 0.0);
      design[0] = (2.0*(i+1.0) - 1.0) / (2.0*n);
//      design[0] = (double)( (i) % (N+1)) / (double) N;
      for(int j = 1; j < Objectives-1; j++)
      {
	   double f = 1.0/primes[j-1];
	   int d = i+1;
	   design[j] = 0.0;
	   while(d > 0)
	   {
		design[j] += f*(d % primes[j-1]);
		d =   (int)((double)d / primes[j-1]); // Here the floor is considered as part of the C++ language.....
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
  Here the hammersley method is implemented....
**/
///vector<vector<double> > UniformGenerator::GenerateWeightVectors(int Objectives, int N)
///{
///   vector<vector<double > > designs;
///   vector<int> primes = generateFirstPrimes(Objectives);
///    
///  //primes.push_back(1);
///   for(int i = 2; i < N; i++)
///     if(gcd(i,N)==1)
///	primes.push_back(i);
///  //primes.push_back(13);
///
/// //     vector<double> design(Objectives, 0.0);
/// //     designs.push_back(design);
/// 
///
///double discrepancy = -10000;
///int z = 1;
/////for(int i = 0; i < primes.size(); i++)
///int i=3;
///{
///   designs.clear();
///   for(int k = 0 ; k < N; k++)
///   {
///      vector<double> design(Objectives, 0.0);
///	    design[0] = ( (2.0 * (k+1)) - 1.0) / (2.0*N);
///	    //for(int i = 1; i < Objectives; i++)
///	    {
///	        double q_ki = (  ((k+1)*primes[i]) % N);
///		if(q_ki == 0) q_ki = N;
///	 	double x_ki = ( (2.0 * q_ki) - 1.0) / (2.0*N);
/////		cout << x_ki ; getchar();
///		design[1] =x_ki ;
///
///	    }
///	    designs.push_back(design);
///   }
/// double tmp = Discrepance(designs);
///  if(discrepancy < tmp)
///   {
///	discrepancy = tmp;
///	z = i;
///   } 
///}
///
/////cout << z << endl;
/////getchar();
/////
/////   for(int i = 0; i < N; i++)
/////	{
/////	for(int j = 0; j < Objectives; j++)
/////	cout << designs[i][j] << " ";
/////	cout << endl;
/////	}
/////cout << endl;
/// // The designs are transformed to weight vectors....
///   return Transformation(designs, Objectives); 
///}
/**
   Transformation Fang and Wang 1994
**/
 vector<vector<double> > UniformGenerator::Transformation(vector< vector<double > > & designs, int dim)
{
   vector<vector< double > > U;

for(int i = 0; i<dim; i++)
   {
  	vector<double> Row(dim); 
	for(int j = 0; j < dim; j++)
	{
	  Row[j] = (i==j)?1.0:0.0;
	}
	U.push_back(Row);
   }

  for(int d = 0; d < designs.size(); d++)
   {
  	vector<double> Row(dim); 
	for(int i = 0; i < dim; i++)
	{
	   if(i == dim-1)
	 	Row[i] = 1.0;
	   else
		Row[i] = 1.0 - pow(designs[d][i], 1.0/(dim-i-1));
	for(int j = 0; j < i; j++)
	        Row[i] *=  pow( designs[d][j], 1.0/(dim-j-1) );
	}
	U.push_back(Row);
   }
//   for(int i = design.size()-1; i>=0 ;i--) U[i]=U[i];

   

	return U;
}

////////////////////////////////////////////////////////////////////77
/***************************************************
 * Uniform Design of Mixture with Hammersley Method 
 ***************************************************/


/* Radical inverse of a number (index) in a prime base */
double UniformGenerator::RadicalInverse(int index, int base)
{
    double result = 0;
    double f = 1.0/base;
    int i = index;
    while(i > 0)
    {
        result += f*(i % base);
        i = (int)(i*1.0/base);
        f = f/base;
    }
    return result;
}

vector< vector< double > > UniformGenerator::UDM(int Objectives, int N)
{   
    int i,j,h;
    int n = N - Objectives;
    int k = Objectives; 
      vector< vector< double > > w(n, vector<double>(k)), weights(N, vector<double>(Objectives));
      vector< vector< double > >set(n, vector<double>(k-1));

    Hammersley(set, n, k-1);
    for (i = 0; i < n; i++)
        for (j = 0; j < k; j++)
        {
            if (j != k-1)
                w[i][j] = 1 - pow(set[i][j],1.0/(k-j-1));
            else
                w[i][j] = 1.0;
            for (h = 0; h < j; h++)
                w[i][j] *= pow(set[i][h],1.0/(k-h-1));
        }
        
    for (i = 0; i < Objectives; i++)
    {   
        /* the first k weights vectors are extreme points */
        for (j = 0; j < Objectives; j++)
            if (i == j)
                weights[i][j] = 1.0;
            else
                weights[i][j] = 0.0;  
        
        /* the rest of weights from the mixture */
        for (j = Objectives; j < N; j++) 
	{
            weights[j][i] = w[j-Objectives][i];
	}
    }
//for(int i = 0 ; i < weights.size(); i++)
//	{
//	   for(int j = 0 ; j < weights[i].size(); j++)
//	cout << weights[i][j]<<" ";
//	   cout << endl;
//	}

 return  weights; 
}
/* Hammersley Method to construct a low discrepancy set of n design points 
 * in a k-dimensional space */
void UniformGenerator::Hammersley( vector< vector< double> > &set, int n, int k)
{

      int primes[] = {2,3,5,7,11,13,17,19,23,29}; /*first 10 prime*/
    int i,j;
    for (i = 0; i < n; i++)
    {
        set[i][0] = (2*(i+1) - 1.0)/(2*n);
        for (j = 1; j < k; j++)
            set[i][j] = RadicalInverse(i+1, primes[j-1]);            
    }                   
}
