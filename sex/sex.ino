const int n=10;
const int p=3;
int n1,n2,n3;
double val[p][n];
double tempval[p][n];
double mean[p];
double deviation[p];
double input[] = {1,2,4,5,12,13,14,17,20,34};
    
void setup()
{}

void loop()
{
  
    
    for(int i=0; i<p; i++) //setting dummy means as first p elements of input
    mean[i] = input[i];
    
    int temp = 0;
    boolean flag = false;
        
    do
    {
      for(int i=0; i<n; i++)
      for(int j=0; j<p; j++)
      {
        val[i][j] = -1;
      }
      for(int i=0; i<n; i++) 
      {
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
      meaningful();
      flag = terminate();
      
      if(!flag)
      {
        for(int i=0; i<p; i++)
          for(int j=0; j<n; j++)
            tempval[i][j] = val[i][j];
      }
      
      n1=0, n2=0, n3=0;
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
  }
    
     

    int clustering(double a) //allot cluster to individual data point
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
        if(val[i][j]!=-1)
        { 
          mean[i] += val[i][j];
          ctr++;
        }
      }
      mean[i]=mean[i]/ctr;
    }
  }
  
  boolean terminate() //terminate the algorithm
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
    
