
// 10724243 •€≈VÊX

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>

using namespace std;

typedef struct hT {
    int rid ;
    int value ;
} heapType ;

typedef enum { MIN, MAX } whichHeap ;

class DM { // Data manage and In/Output

    vector<vector<string>> orinList;
    string fname ;

    void CombName( string name ) {

        fname = name + fname.substr(5,3) ;
        fname = fname + ".txt" ;

    } // CombName()

    void Checkformat( string name ) {
        // If input a code
        if ( fname.at(0) == '1' && fname.size() == 3 ) {
            fname = name + fname + ".txt" ;
        } // if

    } // Checkformat()

    void ReadFileName() {
        cin >> fname ;
    } // ReadFileName()

public:

    string GetFileName() {
        return fname ;
    } // GetFileName()

    bool ReadFile( string fileType ) {

        orinList.clear() ;

        fstream file ;
        char buffer ;
        string data ;
        vector<string> raw ;


        /*---------- deal with File ----------*/
        do {
       		cout << "Input 101, 102, ...[0]Quit): " ;
      		fname.clear() ;
     		ReadFileName() ;

        	if ( fname == "0" ) {
        		return false ;
			} // Quit to open file

            Checkformat( fileType ) ;

			cout << endl ;

        	file.open( fname.c_str(), ios::in ) ; // open file

        	if ( !file ){
            	cout << "Error:Open file fail" << endl << endl ;
			} // if Error

		} while ( !file ) ;

		/*---------- deal with data ----------*/

        while ( file.get(buffer) ) {

            if ( buffer != '\n' ) {

                if ( buffer == '\t' ) {
                    raw.push_back(data) ; // add new data on list
                    data.clear() ; // clear data
                }else{
                    data = data + buffer ; // complete the string
                } // else

            } else {
                raw.push_back(data) ; // add new data on list
                data.clear() ;
                orinList.push_back(raw) ;
                raw.clear() ;
            } // else

        } // end while

        if ( buffer != '\n' && !raw.empty() ) {
            raw.push_back(data) ; // add new data on list
            data.clear() ;
            orinList.push_back(raw) ;
            raw.clear() ;
        } // end if



        if ( orinList.at(orinList.size()-1).at(0).compare("") == 0 && orinList.size() <= 5 ) {
            orinList.pop_back() ;
        } // if only have a data but it display 2 and the second is empty

        file.close() ;

        return true ;

    } // ReadFile()

    bool PrintAll( ) {
        if ( orinList.empty() ) {
            return false ;
        }

        for ( int i = 0 ; i < orinList.size() ; i++ ) {
        	  cout << "[" << i+1 << "] " ;
            for ( int j = 0 ; j < orinList.at(i).size() ; j++ ) {
                cout << orinList.at(i).at(j) << '\t' ;
            }
            cout << endl ;
        }
        return true ;
    } // PrintAll()

    void Write( string name ) {

        fstream file ;

        CombName( name ) ; // change fname to "ouput"

        file.open( fname.c_str(), ios::out ) ;

        for ( int i = 0 ; i < orinList.size() ; i++ ) {
            for ( int position = 0 ; position < orinList.at(i).size() ; position++ ) {
              file << orinList.at(i).at(position) << '\t' ;
            }
            file << '\n' ;
        }

        file.close();
    } // Write()

    void RemoveTitle( ) {
        orinList.erase(orinList.begin(), orinList.begin() + 3 ) ;
    } // RemoveTitle()

    string GetData( int pos, int num ) {
        return orinList.at(pos).at(num) ;
    } // GetData

    int GetSize( ) {
        return orinList.size() ;
    } // GetSize()

}; // Class FileIO

class Heap {

    heapType *maxHeap ;

    int root = 0 ;
    int bottom = 0 ;
    int cur = 0 ;
    int arrayLength = 0 ;

    void Format ( string &data ) {
        for ( int i = 0 ; i < data.size() ; i++ ) {
            int num = (int)data.at(i) - (int)'0' ;
            if ( num > 9 || num < 0 ) {
                data.erase( data.begin()+i ) ;
            }
        } // for
    } // Format()

    void ReHeapUp( int child ) {
        int parent = (child-1)/2 ;

        if ( maxHeap[child].value > maxHeap[parent].value ) {
            swap( maxHeap[child], maxHeap[parent] ) ;
            ReHeapUp(parent) ;
        } // if
    } // ReHeapUp()

public:

    Heap(int size) { maxHeap = new heapType[size] ; arrayLength = size ; } ; // build the heap

    void HeapInsert( string data ) {
        Format( data ) ;
        maxHeap[cur].value = atoi(data.c_str()) ;

        if ( cur==0 && bottom==0 ) {
            cur++ ;
        }else {
            cur++ ;
            bottom++ ;
        } // else

        maxHeap[bottom].rid = cur ;
        ReHeapUp( bottom ) ;

    } // HeapInsert()

    void Print() {
        int levelNo = floor(log2(bottom+1)) ;
        int leftmost = exp2(levelNo)-1 ;

        cout << "root: [" << maxHeap[root].rid << "] " << maxHeap[root].value << endl ;
        cout << "bottom: [" << maxHeap[bottom].rid << "] " << maxHeap[bottom].value << endl ;
        cout << "leftmost bottom: [" << maxHeap[leftmost].rid << "] " << maxHeap[leftmost].value << endl ;
    } // Print()

}; // class Heap

class Deap {

    heapType *deap ;

    int root = 0 ;
    int bottom = 0 ;
    int cur = bottom + 1 ;
    int arrayLength = 0 ;

    void Format ( string &data ) {
        for ( int i = 0 ; i < data.size() ; i++ ) {
            int num = (int)data.at(i) - (int)'0' ;
            if ( num > 9 || num < 0 ) {
                data.erase( data.begin()+i ) ;
            }
        } // for

    } // Format()

    void VerifyMin( int child ) {
        int parent = (child-1)/2 ;

        if ( deap[child].value < deap[parent].value && parent != 0 ) {
            swap( deap[child], deap[parent] ) ;
            VerifyMin(parent) ;
        } // if

    } // VerifyMin()

    void VerifyMax( int child ) {
        int parent = (child-1)/2 ;

        if ( deap[child].value > deap[parent].value && parent != 0 ) {
            swap( deap[child], deap[parent] ) ;
            VerifyMax(parent) ;
        } // if

    } // VerifyMax()

public:
    Deap(int size) { deap = new heapType[size+1] ; arrayLength = size+1 ; deap[root].rid = 0 ; deap[root].value = 0 ; } ; // build the deap

    void DeapInsert( string data ) {

        int levelNo = (int)floor(log2(cur+1)) ;
        int displacement = (int)exp2( levelNo-1 ) ;
        int leftmostOFMaxHeap = displacement*3-1 ;
        int leftmost = exp2( levelNo ) -1 ;
        whichHeap type = ( cur<leftmostOFMaxHeap ) ? MIN : MAX ;

        Format( data ) ;
        deap[cur].value = atoi( data.c_str() ) ;
        deap[cur].rid = cur ;

        if ( cur > 1 ) {
            if ( type == MIN ) {
                int correspond = leftmostOFMaxHeap + ( cur - leftmost ) ; // correspond node
                int parent = floor(( correspond-1 ) / 2 ) ;
                if ( deap[cur].value > deap[parent].value ) {
                    swap( deap[cur], deap[parent] ) ;
                    VerifyMax( parent ) ;
                }else {
                    VerifyMin( cur ) ;
                } // else

            } // if in MinHeap

            else if ( type == MAX ) {
                int correspond = leftmost + ( cur - leftmostOFMaxHeap ) ;
                if ( deap[cur].value < deap[correspond].value ) {
                    swap( deap[cur], deap[correspond] ) ;
                    VerifyMin( correspond ) ;
                }else {
                    VerifyMax( cur ) ;
                } // else

            } // if in MaxHeap

        } // if cur > 1

        cur++ ;
        bottom++ ;

    } // DeapInsert()

    void Print() {
        int levelNo = floor(log2(bottom+1)) ;
        int leftmost = exp2(levelNo)-1 ;

        cout << "bottom: [" << deap[bottom].rid << "] " << deap[bottom].value << endl ;
        cout << "leftmost bottom: [" << deap[leftmost].rid << "] " << deap[leftmost].value << endl ;
    } // Print()

}; // class Deap

void DisplayMission() {
    cout << endl << "******  Max Heap and Deap  ******" ;
    cout << endl << "                                 " ;
    cout << endl << "* 0. QUIT                       *" ;
    cout << endl << "* 1. Build a max heap           *" ;
    cout << endl << "* 2. Build a DEAP               *" ;
    // cout << endl << "* 3.                            *" ;
    cout << endl << "                                 " ;
    cout << endl << "*********************************" ;
} // End displayMission

int main()
{
    DM dataList ;
    int command ;


    do {
        DisplayMission() ;
        cout << endl << "Input a choice(0,1,2,3): " ;
        cin >> command ;
        cout << endl ;

        switch ( command ) {

            case 0:
                break ;
            case 1:
                if (dataList.ReadFile( "input" )) {
                    dataList.RemoveTitle() ;

                    Heap maxheap(dataList.GetSize()) ;

                    for( int i = 0 ; i < dataList.GetSize() ; i++ ) {
                        maxheap.HeapInsert( dataList.GetData( i, 6 ) ) ;
                    } // for

                    cout << "<MAX HEAP>" << endl ;
                    maxheap.Print() ;

                } // if
                break ;

            case 2:
                if (dataList.ReadFile( "input" )) {
                    dataList.RemoveTitle() ;

                    Deap deap(dataList.GetSize()) ;

                    for( int i = 0 ; i < dataList.GetSize() ; i++ ) {
                        deap.DeapInsert( dataList.GetData( i, 6 ) ) ;
                    } // for

                    cout << "<DEAP>" << endl ;
                    deap.Print() ;

                } // if


                break ;
            default :
                cout << "Command dose not exist!" << endl ;
        } // switch()

    } while ( command != 0 ) ;

    return 0;
}





