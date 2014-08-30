#include<fstream>
#include<iostream>

using namespace std;

const int n=20,p=2;
int n1,n2;
double val[p][n]; 
double tempval[p][n]; 
double mean[p]; 
double deviation[p]; 
double input[] = {1,7,6,5,2,2,4,3,3,4,3,3,5,2,6,2,2,8,1,1}; //sample input data
void setup()
{
  ifstream obj("/home/mouli/heart_rate.txt",ios::in);
  int lines = 0;
  string s;
  while(getline(obj,s))
    lines++;
  for(int i=0; i<lines; i++)
  {
    cout<<getline(obj,s);
  }

}

   int clustering(double a) //allot cluster to individual data point. 
  {
    for(int i=0; i<p; i++)
    {
      if(a>mean[i])
      deviation[i] = a-mean[i];
      else
      deviation[i] = mean[i]-a;
    }
    double min = deviation[0];
    int temp = 0;
    for(int i=1; i<p; i++)
    {
      if(deviation[i]<min)
      {
      min = deviation[i];
      temp = i;
      }
    }
    return temp;
  }
      
  void meaningful() //calculate mean of data sets
  {
    for(int i=0; i<p; i++)
    mean[i] = 0;
    
    int ctr = 0;
    for(int i=0; i<p; i++)
    {
      ctr=0;
      for(int j=0; j<n-1; j++)
      {
        if(val[i][j]!=0)
        { 
          mean[i] += val[i][j];
          ctr++;
        }
      }
      mean[i]=mean[i]/ctr;
    }
  }
  
  bool terminate2() //terminate the algorithm.
  {
    for(int i=0; i<p; i++)
    {
      for(int j=0; j<n; j++)
      {
        if(val[i][j]!=tempval[i][j])
        return false;
      }
    }
    return true;
  }
int main()
{
  ifstream obj("/home/mouli/heart_rate.txt",ios::in);
  int lines = 0,ctr = 0;
  string s;
  while(getline(obj,s))
  lines++;
  for(int i=0; i<lines; i++)
  {
    obj>>s;
    obj>>input[ctr];
    ctr++;
  }
    //START
    double max=0, min=0;
    for(int i=0; i<n; i++)
    {
      if(input[i]<=min)
      min = input[i];
      else
      if(input[i]>=max)
      max = input[i];
    }
    mean[0]=min, mean[1]=max;
    //mean allotment done. Initial means are scewed to prevent empty clusters
    
    int temp = 0;
    bool flag = false;
    do
    {
      for(int i=0; i<n; i++)
        for(int j=0; j<p; j++)
          val[j][i] = 0; 
        
      for(int i=0; i<n; i++) 
      {
        temp=clustering(input[i]);
        if(temp==0)
        val[temp][n1++] = input[i];
        else
        if(temp==1)
        val[temp][n2++] = input[i]; 
      }
      meaningful(); 
      flag = terminate2(); 
      
      if(!flag) //if last,current clusters not same. Then initialze last cluster as current cluster
      {
        for(int i=0; i<p; i++)
          for(int j=0; j<n; j++)
            tempval[i][j] = val[i][j];
      }
      
      n1=0;
      n2=0;
      
    }
    while(!flag);
    
     cout<<"\nFinal clusters are:";
    for(int i=0; i<p; i++)
    {
      for(int j=0; j<n; j++)
      {
        cout<<val[i][j];
        cout<<" , ";
      }
    }
    cout<<"\nend";
    //END
  }
    
     

 
    
