const int n=10,p=3; //n = total number of data points, p = total number of clusters
int n1=0,n2=0,n3=0; //
double val[p][n]; //final cluster values
double tempval[p][n]; //previous cluster values
double mean[p]; //self explanatory
double deviation[p]; //difference of a data point from the mean value of the p'th cluster
double input[] = {1,2,4,5,12,13,14,17,20,34}; //sample input data
//------------------------

    
void setup()
{
Serial.begin(9600);
Serial.print("hi");
}

void loop()
{
  
    
    
    //some of the Serial.println() are added for debugging purposes
  
    //-------------------ALGORITHM-----------------------
    for(int i=0; i<p; i++) //setting dummy means as first p elements of input
    mean[i] = input[i];
    Serial.println("end1");
    int temp = 0;
    boolean flag = false;
    do
    {
      for(int i=0; i<n; i++)
      for(int j=0; j<p; j++)
      {
        Serial.println("end2");
        val[i][j] = -1; //initializing val array with arbit values
      }
      for(int i=0; i<n; i++) //adding values to cluster (3 in number for this particular case, hence n1,n2,n3)
      {
        Serial.println("end3");
        temp=clustering(input[i]);
        if(temp==0)
        val[temp][n1++] = input[i];
        else
        if(temp==1)
        val[temp][n2++] = input[i];
        else
        if(temp==2)
        val[temp][n3++] = input[i]; 
      }
      meaningful(); //calculate new means of individual clusters
      flag = terminate(); //check whether last cluster instance is same as current cluster instance
      
      if(!flag) //if last,current clusters not same, then initialze last cluster as current cluster
      {
        for(int i=0; i<p; i++)
          for(int j=0; j<n; j++)
            tempval[i][j] = val[i][j];
        
        Serial.print("loop_end");
      }
      
      n1=0;//no idea why i added this
      n2=0;
      n3=0;
      
    }
    while(!flag);
    
     Serial.println("Final clusters are:");
    for(int i=0; i<p; i++)
    {
      for(int j=0; j<n; j++)
      {
        Serial.print(val[i][j]);
      }
       Serial.println();
    }
    Serial.println("end");
    delay(2000);
    //-------------------ALGORITHM END-----------------------
  }
    
     

    int clustering(double a) //allot cluster to individual data point. Input data point, fn tell you which cluster it belongs to
  {
    Serial.println("sex1");
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
        if(val[i][j]!=-1)
        { 
          mean[i] += val[i][j];
          ctr++;
        }
      }
      mean[i]=mean[i]/ctr;
    }
  }
  
  boolean terminate() //terminate the algorithm. Check whether last and current cluster are same or !
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
    
