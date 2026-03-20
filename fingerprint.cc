#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <unordered_set>
using namespace std;

int K_MER_SIZE = 4;
int WINDOW_SIZE = 3;

vector<string> make_k_mer_groups(string allTokens, int size)
{
    vector<string> k_mer_groups;
    int start = 0; 
    int end = size - 1;
    
    ///loop until upper bound reaches end
    while(end < allTokens.length())
    {
        ///create string of size 4 and add to list
        string k_mer = allTokens.substr(start, size);
        k_mer_groups.push_back(k_mer);

        ///increment upper and lower bound
        start++;
        end++;
    }
    return k_mer_groups;
}

vector<size_t> make_encoded_k_mer_groups(vector<string> k_mer_groups)
{
    ///hash each element of k mer group list
    hash<string> h;
    vector<size_t> encoded_k_mer_groups;
    for(int i = 0; i < k_mer_groups.size(); i++)
    {
        ///create string to store hash value then add to new list
        encoded_k_mer_groups.push_back(h(k_mer_groups[i]));
    }
    return encoded_k_mer_groups;
}

vector<string> make_minimum_window_groups(vector<size_t> encoded_k_mer_groups, int size)
{
    ///Find smallest hash value in each window to get "fingerprint"
    vector<string> minimum_window_value;
    for(int i = 0; i < encoded_k_mer_groups.size(); i += WINDOW_SIZE)
    {
        size_t minVal = encoded_k_mer_groups[i];
        ///find smallest in window
        if((i + 1) < encoded_k_mer_groups.size())
        {
            ///compare current min to next two to find minimum of window
            for(int j = i + 1; j < i + WINDOW_SIZE && j < encoded_k_mer_groups.size(); j++)
            {
                if(encoded_k_mer_groups[j] < minVal)
                {
                    minVal = encoded_k_mer_groups[j];
                }
            }

            ///add smallest to list
            minimum_window_value.push_back(to_string(minVal));
        }
        else{
            ///if this is the last element it must be the smallest
            minimum_window_value.push_back(to_string(minVal));
        }
    }
    return minimum_window_value;   
}

struct Result {
    double score;
    string program_a;
    string program_b;
};

bool operator<(const Result &a, const Result &b) {
    return a.score > b.score;
}

int main(int argc, char* argv[])
{
    ///put all of tokens.txt in string
    ifstream in;
    in.open("tokens.txt");
    if(!in.is_open())
    {
        cout << "ERROR: File not found\n";
        exit(0);
    }

    ///Add all tokens to single string
    string lineInput, allTokensString = "";
    vector<string> all_programs, all_program_names;
    int lineNum = 1;
    while(getline(in, lineInput))///loop through each line of tokens.txt and add to string, then add string to list of all programs
    {
        if(lineNum % 2 == 1){all_program_names.push_back(lineInput);}
        else{
            for(int i = 0; i < lineInput.length(); i++)
            {
                if(lineInput[i] != ' ')
                {
                    allTokensString += lineInput[i];
                }
            }
            all_programs.push_back(allTokensString);
            allTokensString = "";///reset string for next program
        }
        lineNum++;///add one so it knows when even line or off line
    }
    in.close();///close file after reading


    ///separate all programs into k-mers
    vector<vector<string>> k_mer_groups;
    for(int i = 0; i < all_programs.size(); i++)
    {
        vector<string> k_mer_group = make_k_mer_groups(all_programs[i], K_MER_SIZE);
        k_mer_groups.push_back(k_mer_group);
    }

    ///Hash the k-mers
    vector<vector<size_t>> encoded_k_mer_groups;
    for(int i = 0; i < k_mer_groups.size(); i++)
    {
        vector<size_t> encoded_k_mer_group = make_encoded_k_mer_groups(k_mer_groups[i]);
        encoded_k_mer_groups.push_back(encoded_k_mer_group);
    }

    ///create list of minimums from each window for each program
    vector<vector<string>> minimum_window_value;
    for(int i = 0; i < encoded_k_mer_groups.size(); i++)
    {
        vector<string> window = make_minimum_window_groups(encoded_k_mer_groups[i], WINDOW_SIZE);
        minimum_window_value.push_back(window);
    }

    

    ///compare all pairs of windows to find similarity
    vector<vector<double>> similarity_matrix(minimum_window_value.size(), vector<double>(minimum_window_value.size()));
    for(int i = 0; i < minimum_window_value.size(); i++)    
    {
        for(int j = 0; j < minimum_window_value.size(); j++)
        {
            ///check for comparing same program
            if(i != j)
            {
                ///create sets that contain values of the vectors
                unordered_set<string> setA(minimum_window_value[i].begin(), minimum_window_value[i].end());
                unordered_set<string> setB(minimum_window_value[j].begin(), minimum_window_value[j].end());

                int matches = 0;///count matches with count variable

                for (const auto &val : setA)
                {
                    if (setB.count(val))
                    {
                        matches++;
                    }
                }

                ///double similarity = (double)matches / (setA.size() + setB.size() - matches);
                double similarity = matches / static_cast<double>(max(setA.size(), setB.size()));
                similarity_matrix[i][j] = similarity;
            }
            else{
                ///if comparing same program set similarity to 1
                similarity_matrix[i][j] = 1.0;
            }
        }
    }
    
    ///Make list of structs of similarty scores and names of files stored
    vector<Result> ordered_similarity_list;
    for(int i = 0; i < minimum_window_value.size(); i++)
    {
        for(int j = i + 1; j < minimum_window_value.size(); j++)
        {
            ///create struct to store similarity score and file name of programs being compared
            Result comparison_score;
            comparison_score.score = similarity_matrix[i][j];
            comparison_score.program_a = all_program_names[i];
            comparison_score.program_b = all_program_names[j];

            ordered_similarity_list.push_back(comparison_score);
        }
    }
    
    ///sort list created by similarity score
    sort(ordered_similarity_list.begin(), ordered_similarity_list.end());

    
    ///rank similarity scores and send results to file
    ofstream out;
    out.open("similarity_scores.txt");
    if(!out.is_open())
    {
        cout << "ERROR: File not found\n";
        exit(0);
    }


    ///print sorted scores to new file
    out << "File 1 Name:    | File 2 Name:  | Similarity Score:\n";
    for(int i = 0; i < ordered_similarity_list.size(); i++)
    {
        double similarityScore = ordered_similarity_list[i].score * 100;
        string file1Name = ordered_similarity_list[i].program_a;
        string file2Name = ordered_similarity_list[i].program_b;

        out << file1Name << "\t\t| " << file2Name << "\t| " << similarityScore << "%\n";
    }

    out.close();
    return 0;
}