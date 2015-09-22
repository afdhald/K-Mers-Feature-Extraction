#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace std;

std::string kmers(int i, int K) {
    static const char* DNA = "ACGT";
    if (K==0) return std::string();
    return DNA[i%4] + kmers(i / 4, K-1);
}

const int K = 3;

int main () {
    int label,loading,m,n=0;
    std::string data;
    std::string arrData[64] = {};

    for (int i = 0; i != 1<<(2*K); ++i){
        arrData[i] = kmers(i,K);
    }

    ofstream newfile;
    newfile.open("data/latih_500bp_k3.dat");
    ifstream myfile ("data/datalatih_500bp.fna");

    if (myfile.is_open())
    {
        std::string newdata="";
        m=1;
        loading=0;
        label=1;

        while ( getline (myfile,data) )
        {
            std::string target = ">";
            int idx = data.find(target);

            if (idx!=string::npos) {
                std::cout << loading << ' ';
                loading++;
                n=0;
                if(newdata!=""){
                    newfile << label << ' ';
                    while (n<ARRAY_SIZE(arrData)) {
                        int x=0;
                        for (int i = 0; i < newdata.length(); i++) {
                            std::string str2 = newdata.substr (i,K);
                            if(str2==arrData[n]){
                                ++x;
                            }
                        }
                        n++;
                        newfile << n << ':' << x << ' ';
                    }
                    newfile << '\n';

                    m++;

                    if(m==6001){
                        label = label++;
                        m=1;
                    }
                }
                newdata="";
            }
            else {
                newdata +=data;
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}
