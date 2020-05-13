#include<stdio.h>
#include<string.h>
#include<time.h>
#define maxsize 1000000

//Structure for time object
struct tm rtm = {0};
//Structure for record object
typedef struct trec{
	time_t t;
	char rec[512];
}record;

record r[maxsize];

//Comparator for the sort function
int cmpfunc (const void * a, const void * b) {
   return (((record*)a)->t - ((record*)b)->t);
}

//Swap function for the bubble sort
void swap(record *a, record *b){
    record temp = *a;
    *a = *b;
    *b = temp;
}

//Bubble sort
/* Code taken from GeeksforGeeks */
/* Reference Link: https://www.geeksforgeeks.org/bubble-sort/ */
void bubblesort(record *r, int count){
	int i, j; 
   	for (i=0; i<count-1; i++){   
        for (j=0; j<count-i-1; j++)  {
	    	if(r[j].t > r[j+1].t) {
	            swap(&r[j], &r[j+1]);
			}
	    }
	}   
}

//Merge Sort - Extra Memory Required
//Bubble sort
/* Code taken from GeeksforGeeks */
/* Reference Link: https://www.geeksforgeeks.org/merge-sort/ */

/* create temp arrays */
record L[maxsize/2 + 1], R[maxsize/2 + 1];
    
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(record *rc, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m;  
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = rc[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = rc[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i].t <= R[j].t) 
        { 
            rc[k] = L[i]; 
            i++; 
        } 
        else
        { 
            rc[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        rc[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        rc[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergesort(record *rc, int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergesort(rc, l, m); 
        mergesort(rc, m+1, r); 
  
        merge(rc, l, m, r); 
    } 
} 

//Quicksort Sort
/* Code taken from GeeksforGeeks */
/* Reference Link: https://www.geeksforgeeks.org/quick-sort/ */
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (record *r, int low, int high) 
{ 
	int i, j;
    record pivot = r[high];    // pivot 
    i = (low - 1);  // Index of smaller element 
  
    for (j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (r[j].t < pivot.t) 
        { 
            i++;    // increment index of smaller element 
            swap(&r[i], &r[j]); 
        } 
    } 
    swap(&r[i + 1], &r[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quicksort(record *r, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(r, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quicksort(r, low, pi - 1); 
        quicksort(r, pi + 1, high); 
    } 
} 

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("As argument 1, enter the file name on which sort is to be performed. As argument 2, enter type of sort to be performed. 1) Type 'merge' for merge sort. 2) Type 'quick' for quick sort. 3) Type 'bubble' for bubble sort.\n");
		return 0;
	}
	
	//Clock 
	clock_t start_mlt, end_mlt, start_st, end_st;
	double total_mlt, total_st, total_t;
	
	//Initializing variables
	int year, month, day, hour, min, sec, zhr, zmin;  char c;
	
	// Starting time for reading data into memory
	start_mlt = clock();
	
	// Opening the files. syslog file for reading and creating an output file for writing for each sort type and each syslog file
	FILE *fp = fopen(argv[1], "r");
	char fn[100];
	char *result = fn;
	char *outfile = strcpy(result, argv[1]);
	outfile = strcat(result, "_");
	outfile = strcat(result, argv[2]);
	outfile = strcat(result, "_output.txt");
	FILE *fw = fopen(outfile, "w");
	
	//Counting the number of lines in the file 
	int count=0, i=0, j;
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count++;
	
	//Rewinding file pointer to the start of the file
	rewind(fp);   
	// Creating a records array for storing the record data  
//	record r[count];
	
	//Reading all the records and putting them in the records array starts
	size_t maxbufsize = 1024;
	char tmpbuf[maxbufsize];
	char *tmpbufptr = tmpbuf;
	ssize_t nread;
	while((nread = getline(&tmpbufptr, &maxbufsize, fp)) != -1){
		char *tmp = strtok(tmpbufptr, "\n");
		char *record = strchr(tmp, ' ');
		record++;
		char *token = strtok(tmp, " ");

		sscanf(token, "%4d-%2d-%2dT%2d:%2d:%2d%c%2d:%2d", &year, &month, &day, &hour, &min, &sec, &c, &zhr, &zmin);
    	rtm.tm_year = year - 1900; /* years since 1900 */
    	rtm.tm_mon = month - 1;
    	rtm.tm_mday = day;
    	rtm.tm_hour = hour;
    	rtm.tm_min = min;
    	rtm.tm_sec = sec;
    	rtm.tm_isdst = -1;
    	time_t rtime = mktime(&rtm);
    	
    	//Adjust timezone
    	if(c == '+')
    		rtime+=((zhr*3600) + (zmin*60));
    	else if(c == '-')
    		rtime-=((zhr*3600) + (zmin*60));

		strncpy(r[i].rec, record, sizeof r[i].rec - 1);
		r[i++].t = rtime;
	}
	//Reading all the records and putting them in the records array ends
	
	//Ending time for reading data into memory
	end_mlt = clock();
	
	//Calculating data load time into memory
	total_mlt = ((double)(end_mlt-start_mlt))/CLOCKS_PER_SEC;
	
	//Starting time for sorting data
	start_st = clock();
	
	//sorting the records based on the timestamp
	if(strcmp(argv[2], "bubble") == 0){
		fprintf(fw, "Bubble sort!!\n");
		bubblesort(r, count);
	}
	else if(strcmp(argv[2], "merge") == 0){
		fprintf(fw, "Merge sort!!\n");
		mergesort(r, 0, count-1);
	}
	else if(strcmp(argv[2], "quick") == 0){
		fprintf(fw, "Quick sort!!\n");
		quicksort(r, 0, count-1);
	}
	
	//Ending time for sorting data
	end_st = clock();
	
	//Calculating time for sorting data
	total_st = ((double)(end_st-start_st))/CLOCKS_PER_SEC;
	
	fprintf(fw, "Time taken by CPU for loading data into memory: %f\n", total_mlt);
	fprintf(fw, "Time taken by CPU for sorting data: %f\n", total_st);
	total_t = total_mlt + total_st;
	fprintf(fw, "Total time taken by CPU: %f\n", total_t);
	fprintf(fw, "File Contents: \n");
	//Printing the records
	for(j=0; j<count; j++){
		char *t = ctime(&(r[j].t));
		if(t[strlen(t)-1] == '\n') 
			t[strlen(t)-1] = '\0';	
		fprintf(fw, "%s %s\n", t, r[j].rec);
	}
		
	return 0;
}
