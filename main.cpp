/**
   Autor: Joel Chacón Castillo
   Date: 07/may/2017
   
   This is a generator of weight vectors for MOEA/D based on the paper:
  "MOEA/D + uniform design: A new version of MOEA/D for optimization problems with many objectives"
   by
   Yan-yan Tan, Yong-chang jiao, Hong Li, Xin-kuan Wang.

**/
#include <iostream>
#include "UniformGenerator.hpp"
using namespace std;
 string verbose()
{
   string message = "";
   message += "--h --help print this summary and exit\n";
   message += "--n Number of vector to generate\n";
   message += "--o Number of objectives\n";
   message += "Example:\n  ";
   return message;
}
int main(int argc, char * argv[])
{
   if(argc<2)
         {
	    
	    cout << "Unknown Argument.."<<endl;
	    cout << verbose();
	    exit(0);
	 }

  int Objectives =2, Vectors = 100;
   for(int i = 1; i < argc ; i++)
    	{
		string Terminal(argv[i]);
		if( Terminal == "--h")
			cout << verbose<<endl;
		else if(Terminal == "--o" )
			Objectives = atoi(argv[++i]);
		else if(Terminal == "--n" )
			Vectors = atoi(argv[++i]);
		else
		{
		   cout << "Unknown Argument...";
		   exit(0);
		}
	}





  UniformGenerator Obj;
  vector< vector<double> > Wvec = Obj.GenerateWeightVectors(Objectives, Vectors);
  for(int i = 0; i < Wvec.size(); i++)
  {
	for(int j = 0; j< Objectives; j++)
	cout << Wvec[i][j] << " ";
        cout << endl;
  }


   return 0;
}
