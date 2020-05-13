#include<bits/stdc++.h>
#define MOD 1024
using namespace std;

// Vectors to store X and Y indexes
vector<int> xind,  yind;

//Code Reference: https://www.geeksforgeeks.org/printing-longest-common-subsequence/

// Now return the LCS
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
void lcs(vector<int> &X, vector<int> &Y, int m, int n) 
{ 		
    int L[m+1][n+1]; 
  
    /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
       that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    for (int i=0; i<=m; i++) 
    { 
       for (int j=0; j<=n; j++) 
       { 
        if (i == 0 || j == 0) 
           L[i][j] = 0; 
        else if (X[i-1] == Y[j-1]) 
           L[i][j] = L[i-1][j-1] + 1; 
        else
           L[i][j] = max(L[i-1][j], L[i][j-1]); 
        } 
    } 
  
    // Following code is used to print LCS 
    int index = L[m][n]; 
  
    // Create an integer array to store the lcs string 
    int lcs[index]; 
  
    // Start from the right-most-bottom-most corner and 
    // one by one store characters in lcs[] 
    int i = m, j = n; 
    while (i > 0 && j > 0) 
    { 
        // If current character in X and Y are same, then 
        // current character is part of LCS 
        if (X[i-1] == Y[j-1]) 
        { 
            lcs[index-1] = X[i-1]; // Put current integer in result 
            xind.push_back(i);
            yind.push_back(j);
            i--; j--; index--;     // reduce values of i, j and index 
        } 
        // If not same, then find the larger of two and 
        // go in the direction of larger value 
        else if (L[i-1][j] > L[i][j-1]) 
           i--; 
        else
           j--; 
    } 
} 

int main(int argc, char *argv[]){
	vector<int> f1, f2;
	
	//This tp variable will contain the line
	string tp;
	int counter;
	// Get filename
	if(argc != 3){
		cout<<"Enter filename as commandline argument\n";
		return 0;
	}
	// Read the file line by line (Reference: Tutorials Point. Link: https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus)
	string file1 = argv[1], file2 = argv[2];
	fstream rfile1, rfile2;
    
    //Get the hashvalues of all the lines for the first file
	rfile1.open(file1);  // open a file to perform read operation
    if (rfile1.fail()) {
        cout << "Couldn't open the file!. Please make sure that the text file is in the same directory in which the code file is present.\n" << endl;
        return 0;
    }
    while(getline(rfile1, tp)){ //read data from file object and put it into string.
        int hashval = 0;
    	for(int i=0; i<tp.length(); i++){
    		hashval += ((i+1)%MOD * tp[i]%MOD)%MOD;
    		hashval = hashval%MOD;
		}    
		f1.push_back(hashval);
    }
    rfile1.close(); //close the file object
    
    //Get the hashvalues of all the lines for the second file
    rfile2.open(file2);
    if (rfile2.fail()) {
        cout << "Couldn't open the file!. Please make sure that the text file is in the same directory in which the code file is present.\n" << endl;
        return 0;
    }
    while(getline(rfile2, tp)){ //read data from file object and put it into string.
        int hashval = 0;
    	for(int i=0; i<tp.length(); i++){
    		hashval += ((i+1)%MOD * tp[i]%MOD)%MOD;
    		hashval = hashval%MOD;
		}    
		f2.push_back(hashval);
    }
    rfile2.close(); //close the file object

	// Now get the lcs
	int m = f1.size(); 
  	int n = f2.size(); 
	lcs(f1, f2, m, n); 

	// Reopening the files again
	rfile1.open(file1);  // open a file to perform read operation
	if (rfile1.fail()) {
        cout << "Couldn't open the file!. Please make sure that the text file is in the same directory in which the code file is present.\n" << endl;
        return 0;
    }
    
	// Reopening the files again
	rfile2.open(file2);  // open a file to perform read operation
	if (rfile2.fail()) {
        cout << "Couldn't open the file!. Please make sure that the text file is in the same directory in which the code file is present.\n" << endl;
        return 0;
    }
	
	int counter1 = 1, counter2 = 1;
	for(int i=xind.size()-1; i>=0; i--){
		while(counter1 != xind[i]){
			getline(rfile1, tp);
			cout<<"- "<<tp<<endl;
			counter1++;
		}
		while(counter2 != yind[i]){
			getline(rfile2, tp);
			cout<<"+ "<<tp<<endl;
			counter2++;
		}
		getline(rfile1, tp);
		getline(rfile2, tp);
		cout<<"  "<<tp<<endl;
		counter1++; counter2++;		
	}
	//Spit out whatever remains in the two files
	while(counter1 <= f1.size()){
		getline(rfile1, tp);
		cout<<"- "<<tp<<endl;
		counter1++;
	}
	while(counter2 <= f2.size()){
		getline(rfile2, tp);
		cout<<"+ "<<tp<<endl;
		counter2++;
	}
	
	//Closing both the files
	rfile1.close();
	rfile2.close();
	
	return 0;
}
