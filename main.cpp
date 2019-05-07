#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if(dirp->d_name[0] != '.')
            files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

bool search(int num, vector<int> done){
    for(int u = 0; u < done.size(); u++){
        if (done[u] == num){
            return(true);
        }
    }
    return (false);
}

int findfilenum(string filename, vector<string> files){
    int i = 0;
    while(filename != files[i]){
        i++;
    }
    return (i);
}

int main() {

    //Prompt Code
    //-------------------------------------------------------------------------
    int chunksize = 6;
    //-------------------------------------------------------------------------

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    getdir(dir, files);
    for (unsigned int i = 0; i < files.size(); i++) {
        cout << i << files[i] << endl;
    }

    struct hashentry{
        string filename;
        int number;
        hashentry *next;
        string chunk;
    };

    //Initialize hash table here
    //--------------------------------------------------------------------------------------07
    int maxhash = 507953;
    hashentry *hashtable[maxhash];
    for(int m = 0; m<maxhash; m++){
        hashtable[m] = NULL;
    }
    //--------------------------------------------------------------------------------------07


    //This loop reads from every file
    //-------------------------------------------------------------------------------------------00
    ifstream inFile;
    vector <string> words;
    for(int k = 0; k < files.size(); k++) {
        string doublebackslash = "\\";
        string openme = dir + doublebackslash + files[k];
        inFile.open(openme);
        if (!inFile) {
            cout << "TRAGIC\n";
            exit(-1);
        }


        //This loop reads from a file and pushes every alpha numeric string in doc to words-vector
        //---------------------------------------------------------------------------------------01
        words.clear();
        string word;
        vector<char> wordholder;
        while (inFile >> word) {
            wordholder.clear();
            for (int i = 0; i < word.size(); i++) {
                if (isalnum((int) word[i]) != 0) {
                    wordholder.push_back(word[i]);
                }
            }
            word.resize(wordholder.size());
            for (int i = 0; i < wordholder.size(); i++) {
                word[i] = wordholder[i];
            }
            words.push_back(word);
        }
        //--------------------------------------------------------------------------------------01
        //words-vector contains all words in one document
        //(DEBUG) Prints every word in file
        /*
        for (int i = 0; i < words.size(); i++) {
            cout << words[i] << "\n";
        }
        */




        //chunking code goes here
        //--------------------------------------------------------------------------------------02
        string chunk;
        for(int i = 0; i < (words.size()-(chunksize-1)); i++) {

            for(int j = i; j < (i + chunksize); j++){
                chunk = chunk + words[j];
            }

            //A chunk is made
            //Hashing code goes here
            //--------------------------------------------------------------------------------------03

            long key = 0;
            for(int l = 0; l < (chunk.size()-1); l++){
                int twenthrees = 1;
                int index = 0;
                while(index<l){
                    twenthrees = twenthrees*37;
                    index++;
                }
                key = key + (chunk[chunk.size()-l-1]*twenthrees);
            }

            if(key < 1){
                key = key * -1;
                key = key;
            }
           /*
            key = key/10;
            if(i%23 == 0)
                key = key%500000;

            if(i%37 == 0)
                key = key%100000;
            */
            /*
            int result = 1;
            for(int k = 0; k < chunk.size(); k = k+3){
                if((k%2) == 0){
                    result = (result * chunk[k])%213;
                }
                else if(k%3 == 0){
                    result = result - (chunk[k]%83);
                    if(result < 1){
                        result = result + (chunk[k]%83);
                    }
                }
                else{
                    result = result + chunk[k];
                }
            }
            int threes = 1;
            int hash = 0;
            hash = result%30;
            for(int k = 0; k < 8; k++){
                threes = threes* 3;
            }
            hash = hash * threes;
            hash = hash + (result%577);
            */

            key = key%maxhash;

            hashentry *temp = new hashentry;
            temp->next = NULL;
            temp->number = k;
            temp->filename = files[k];
            temp->chunk = chunk;
            if(hashtable[key] == NULL){
                hashtable[key] = temp;
            }
            else{

                hashentry *hold = hashtable[key];
                if(temp->chunk == hold->chunk) {
                    while (hold->next != NULL) {
                        hold = hold->next;
                    }
                    hold->next = temp;
                }
            }

            //--------------------------------------------------------------------------------------03
            chunk = "";
        }
        //--------------------------------------------------------------------------------------02
        inFile.close();
    }
    //-------------------------------------------------------------------------------------------00

    //2-D Array Code goes here
    //-------------------------------------------------------------------------------------------04

   // int collisions[files.size()][files.size()-1];


    /*


    vector<string> chunkbros;
    for(int r = 0; r < maxhash; r++){
        if (hashtable[r] != NULL){
            if (hashtable[r]->next != NULL) {
                chunkbros.push_back(hashtable[r]->filename);
                hashentry *holder = hashtable[r]->next;
                while (holder != NULL) {
                    chunkbros.push_back(holder->filename);
                    holder = holder->next;
                }

            }
        }

    }

    */


    int collisions[files.size()][files.size()];

    int z = 0;
    int q = 0;
    while( q < files.size()-1){
        while( z < files.size()){
            collisions[q][z] = 0;
            z++;
        }
        z=0;
        q++;
    }
    vector<int> done;
    vector <string> yo;
    for (int i = 0; i < maxhash; i++) {
        if(hashtable[i] != NULL) {
            if (hashtable[i]->next != NULL) {
                hashentry *ptr1 = hashtable[i];
                while (ptr1 != NULL && ptr1->next != NULL) {
                    hashentry *ptr2 = ptr1->next;
                    while (ptr2 != NULL) {
                        if ((ptr2->number) != (ptr1->number)) {
                            collisions[ptr1->number][ptr2->number]++;
                        }
                        /*else if ((ptr1->number) < (ptr2->number)) {
                            collisions[ptr1->number][ptr2->number]++;
                        }
                         */
                        ptr2 = ptr2->next;
                    }
                    ptr1 = ptr1->next;
                }
            }
        }
    }

    vector<vector<int>> print;

    for (int i = 0; i < files.size(); i ++) {
        for (int j = i + 1; j < files.size(); j ++)   {
            if (collisions[i][j] > 200) {
                vector <int> temp;
                temp.push_back(collisions[i][j]);
                temp.push_back(i);
                temp.push_back(j);
                print.push_back(temp);
            }
        }
    }
    sort(print.begin(), print.end());
    for (int i = print.size() - 1; i >= 0; i --) {
        cout << print.at(i).at(0) << ": " << files[print.at(i).at(1)] << ", " << files[print.at(i).at(2)] << endl;
    }
    //-------------------------------------------------------------------------------------------04


    return 0;
}
