#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

int K_MER_SIZE = 4;
int WINDOW_SIZE = 3;

int main()
{
    ///put all of tokens.txt in string
    ifstream in;
    in.open("tokens.txt");
    if(!in.is_open())
    {
        cout << "ERROR: File not found\n";
        exit(0);
    }

    string token, allTokens = "";
    while(in >> token)
    {
        allTokens += token;
    }


    ///separate into 4-mers
    vector<string> k_mer_groups;
    int start = 0; 
    int end = K_MER_SIZE - 1;
    
    ///loop until upper bound reaches end
    while(end < allTokens.length())
    {
        ///create string of size 4 and add to list
        string k_mer = allTokens.substr(start, 4);
        k_mer_groups.push_back(k_mer);

        ///increment upper and lower bound
        start++;
        end++;
    }


    ///hash each element of k mer group list
    hash<string> h;
    vector<string> encoded_k_mer_groups;
    for(int i = 0; i < k_mer_groups.size(); i++)
    {
        ///create string to store hash value then add to new list
        string hash;
        hash = h(k_mer_groups[i]);
        encoded_k_mer_groups.push_back(hash);
    }



    ///Find smallest hash value in each window to get "fingerprint"
    vector<string> minimum_window_value;
    for(int i = 0; i < encoded_k_mer_groups.size(); i++)
    {
        string minVal = encoded_k_mer_groups[i];
        ///find smallest in window
        if((i + 1) < encoded_k_mer_groups.size())
        {
            ///compare current min to next two to find minimum of window
            for(int j = i + 1; j < WINDOW_SIZE && j < encoded_k_mer_groups.size(); j++)
            {
                if(stoi(encoded_k_mer_groups[j]) < stoi(minVal))
                {
                    minVal = encoded_k_mer_groups[j];
                }
            }

            ///add smallest to list
            minimum_window_value.push_back(minVal);
        }
        else{
            ///if this is the last element it must be the smallest
            minimum_window_value.push_back(minVal);
        }

        ///incrememnt i based on window size
        i += (WINDOW_SIZE - 1);
    }


    


    return 0;
}