#include<bits/stdc++.h>
#define MOD 1024
using namespace std;

int hash10(string s){
	int hashval = 0;
	for(int i=0; i<s.length(); i++){
		hashval += ((i+1)%MOD * s[i]%MOD)%MOD;
		hashval = hashval%MOD;
	}    	
	return hashval;
}

int main(int argc, char *argv[]){
	vector<int> f1, f2;
	
	//This tp variable will contain the line
	string tp;
	// Get filename
	if(argc != 2){
		cout<<"Enter filename as commandline argument\n";
		return 0;
	}
	// Read the file line by line (Reference: Tutorials Point. Link: https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus)
	string file1 = argv[1];
	fstream rfile1;
    
    //Get the hashvalues of all the lines for the first file
	rfile1.open(file1);  // open a file to perform read operation
    if (rfile1.fail()) {
        cout << "Couldn't open the file!. Please make sure that the text file is in the same directory in which the code file is present.\n" << endl;
        return 0;
    }
    while(getline(rfile1, tp)){ //read data from file object and put it into string.
        int hashval = hash10(tp);
		f1.push_back(hashval);
    }
    rfile1.close(); //close the file object
    
    //Printing the hash values
    for(int i=0; i<f1.size(); i++){
    	cout<<f1[i]<<endl;
	}

	return 0;
}
