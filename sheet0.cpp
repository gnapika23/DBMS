#include<iostream>
#include <fstream>
#include <ctime>
using namespace std;

class salesman{
   public:
   int * num_products = new int(8);
};
class region{
   public:
   salesman salesmen[6];
};

void convert(string data,int &region,int &salesman_id,int &product_id, int &product_quantity){
    int len=data.size();
    int value=0,ct=0;
    for(int i=0;i<len;i++){
       if(data[i]==' ' || i==len-1){
          if(ct==0){
            region=value;
            value=0;
          }
          else if(ct==1){
            salesman_id=value;
            value=0;
          }
          else if(ct==2 && i<len-1){
            product_id=value;
            value=0;  
          }
          else if(i==len-1){
            value=value*10+data[i]-'0';
            product_quantity=value;
            value=0;
          }
          ct++;
       }
       else{
         value=value*10+data[i]-'0';
       }
    }
}

int main(){
    time_t now= time(0);
    tm* timeinfo = localtime(&now);
    int year = timeinfo->tm_year + 1900; 
    int month = timeinfo->tm_mon + 1; 
    int day = timeinfo->tm_mday;

    string file = "input.csv";
    ifstream inputFile;
    inputFile.open(file);

    string file2= "output.txt";
    ofstream outputFile;
    outputFile.open(file2);    

    vector<int> price(8);
    for(int i=1;i<=8;i++) price[i-1]=2000*i;

    string line;
    getline(inputFile,line);
    
    region regions[4];
    int ct=0;
    while(1){
        ct++;
        string data;
        getline(inputFile,data);
        if(data.size()==0) break;
        int reg,salesman_id,product_id,product_quantity;
        convert(data,reg,salesman_id,product_id,product_quantity);
        regions[reg].salesmen[salesman_id].num_products[product_id]=product_quantity;
        //cout<<regions[reg].salesmen[salesman_id].num_products[product_id]<<endl;
    }
    outputFile<<"                                        ABC Company"<<endl;
    outputFile<<"                                       -------------"<<endl;
    for(int i=0;i<4;i++){
        outputFile<<"Region "<<i+1<<endl;
        outputFile<<"--------- "<<endl;
        int sum=0;
        for(int j=0;j<6;j++){
            int total=0;
            outputFile<<"Salesman ID "<<j+1;
            for(int k=0;k<8;k++){
                total+=regions[i].salesmen[j].num_products[k]*price[k];
            }
            outputFile<<"         "<<total<<endl;
            sum+=total;
        }
        outputFile<<"\n";
        outputFile<<"Total sale at Region "<<i+1<<"             "<<"Rs: "<<sum<<endl<<endl;
        outputFile<<"                                                   Date: "<<day<<"/"<<month<<"/"<<year<<"          Page Number: "<<i+1<<endl;
        outputFile<<"..........................................................................................."<<"\n";
    }
    inputFile.close();
    return 0;
}