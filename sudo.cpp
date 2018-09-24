#include "sudo.hpp"
struct cordinate 
	{ int x;
	  int y;
	};

	class cell
	{
		public:
			unsigned int value;
			unsigned int x; // location
			unsigned int y; // location
			bool original; //given part of original matrix
			vector <unsigned int> probables;
			vector <unsigned int> nonProbables;
			unsigned int probCount;
			map <unsigned int, unsigned int> probFreq;

			cell() { }
			~cell() { }
	};

class sMatrix 
{
	private:
		class cell sudo[DIM][DIM];
		unsigned int emptyRowCount[DIM];
		unsigned int emptyColumnCount[DIM];

		void initializeCell();
		bool isMatrixFull();
		int findSubMatrixIndex(int, int);	
		cordinate findSubMatrixStartingPoint(int );
		void fillSubMatrix(int , int );
		void findNonprobables(int , int );

	public:
		void printMatrix();
		void solveSudoko();
		void printProbables(int,int,bool);
		void findProbables(int , int );
		void findProbableFrequencyInNeighbourHood(int, int);
		void countEmptyRows();
		void countEmptyColumns();
		void unitTest(int ,int , int );
		void iterativeTest(int );
		sMatrix()
		{

			__initialize(); // load up the given matrix	
			initializeCell();
		}			
		
};
void sMatrix::initializeCell()
{
for (int i = 0 ; i < DIM ; i++)
{
 for (int j = 0 ; j < DIM ; j++)
 {
	sudo[i][j].x = i;
	sudo[i][j].y = j;

	if (sudoko[i][j]) 
	{
			sudo[i][j].original = TRUE;
			sudo[i][j].value = sudoko[i][j];
	}	
	else
	{
			sudo[i][j].original = FALSE;
			sudo[i][j].value = 0;

	}	
	}
 }
countEmptyRows();
countEmptyColumns();
	
}

void sMatrix::countEmptyRows()
{
	unsigned int empty; 
	for (int i = 0 ; i < DIM ; i++)
	{
		 empty = 0;
	 for (int j = 0 ; j < DIM ; j++)
 	     	{
			if (!(sudo[i][j].value))
				empty++;
		}
		emptyRowCount[i]=empty;
	}
}	
void sMatrix::countEmptyColumns()
{
	unsigned int empty; 
	 for (int j = 0 ; j < DIM ; j++)
	{
		 empty = 0;
	for (int i = 0 ; i < DIM ; i++)
 	     	{
			if (!(sudo[i][j].value))
				empty++;
		}
		emptyColumnCount[j]=empty;
	}	
}

void sMatrix::printProbables(int _i, int _j, bool flag = 1)
{
	if (sudo[_i][_j].original)
		return;
	vector <unsigned int> vect;
	if (flag)
		vect = sudo[_i][_j].probables;
	else
		vect = sudo[_i][_j].nonProbables;

	cout << _i << "," << _j << ":";
	for(vector<unsigned int>::iterator it = vect.begin(); it!=vect.end(); ++it)
		cout << ' ' << *it;
	cout << "\n";
}

void sMatrix::printMatrix()
{
	for (int i = 0 ; i < DIM ; i++)
	{
 		for (int j = 0 ; j < DIM ; j++)
 		{
			cout << sudo[i][j].value << " ";
		}
		cout << "\t" << emptyRowCount[i] << "\n";
	}
		cout << "\n" ;
	for (int j = 0 ; j < DIM ; j++)
		cout  << emptyColumnCount[j] << " " ;
		cout << "\n" ;

}
void sMatrix::unitTest(int _i,int _j, int funno)
{
int result = 0;
switch (funno) {
case 1:
	result = findSubMatrixIndex(_i,_j);
	cout <<  "Index of " << _i << "," << _j << "\t:" << result << "\n";
	break;
case 2: 
	findProbables(_i,_j);;
	printProbables(_i,_j,TRUE);
	break;
	
}


}
void sMatrix::iterativeTest(int _i)
{
	for (int i = 0 ; i < DIM ; i++)
	{
 		for (int j = 0 ; j < DIM ; j++)
 		{
			unitTest(i,j,_i);
		}
	}

}


int sMatrix::findSubMatrixIndex(int _i, int _j)	
{
	int _i_,_j_,index;
	_i_ = _i/SUBDIM;
	_j_ = _j/SUBDIM;
	index = _i_*SUBDIM+_j_+1;
	return index;

}
cordinate sMatrix::findSubMatrixStartingPoint(int _index)
{
/* find an algrothm to find the starting point based on the index */
/* following methods will not work when sudoko matrix dimension is other than 9 */

cordinate submatrix[DIM] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};

if (_index < 1 && _index > DIM)
{
	printf("do error handling\n");
	return submatrix[0];
}	
return submatrix[_index-1];
}

void sMatrix::fillSubMatrix(int _i, int _j)
{
int i,j;
int index,sindex;
int i_,j_;
cordinate startpoint;

index = findSubMatrixIndex(_i,_j);
startpoint =  findSubMatrixStartingPoint(index);
i = startpoint.x;
for(i_=0;i_<SUBDIM;i_++)
{
	j = startpoint.y;
	for (j_=0;j_<SUBDIM;j_++)
	{
		if (sudo[i][j].value)
			sudo[_i][_j].nonProbables.push_back(sudo[i][j].value);
		j++;
		}
	i++;
	}

}
void sMatrix::findProbables(int _i, int _j)
{

	if (sudo[_i][_j].original)
		return;
//	if (sudo[_i][_j].value)
//		return;

	vector<unsigned int> universe; 
	bool flag;
	for (unsigned int i = 1; i <= DIM ; i++)
		universe.push_back(i);
	findNonprobables(_i,_j);
	for(vector<unsigned int>::iterator it = universe.begin(); it!=universe.end(); ++it)
	{
		flag = TRUE;
		for(vector<unsigned int>::iterator it2 = sudo[_i][_j].nonProbables.begin(); it2!=sudo[_i][_j].nonProbables.end(); ++it2)
		{
			if (*it == *it2)
			{
				flag = FALSE;
				break;
			}
		}
		if (flag)
		{
			sudo[_i][_j].probables.push_back(*it);
		}
	}

}

void sMatrix::findNonprobables(int _i, int _j)
{
	if (sudo[_i][_j].original)
		return;
//	if (sudo[_i][_j].value)
//		return;

	int i_, j_;
	fillSubMatrix(_i,_j);
	for (i_ = 0 ; i_ < DIM; i_++)
	{
		if (sudo[i_][_j].value)
			sudo[_i][_j].nonProbables.push_back(sudo[i_][_j].value);
	}
	for (j_ = 0 ; j_ < DIM ; j_++)
	{
		if (sudo[_i][j_].value)
			sudo[_i][_j].nonProbables.push_back(sudo[_i][j_].value);
	}
	sort(sudo[_i][_j].nonProbables.begin(),sudo[_i][_j].nonProbables.end());
	sudo[_i][_j].nonProbables.erase(unique(sudo[_i][_j].nonProbables.begin(),sudo[_i][_j].nonProbables.end()), sudo[_i][_j].nonProbables.end());
	return ;
} 
void sMatrix::findProbableFrequencyInNeighbourHood(int _i, int _j)
{
	if (sudo[_i][_j].original)
		return;
	

}
bool sMatrix::isMatrixFull()
{
			cout << "Matrix dull";
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			if (!sudo[i][j].value)
				return FALSE;
		}
	}
	return TRUE;
}
	
			

void sMatrix::solveSudoko()
{
	if (isMatrixFull())
		return;

	cout << "Solve Sudoko";
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			if (!sudo[i][j].value)
			{
				
				sudo[i][j].value = sudo[i][j].probables.front();
				cout << i << "," <<j << ":"<<sudo[i][j].value;
				findProbables(i,j);
			}

		}
	}
}	


int main() 
{ 
class sMatrix mySudoko; 
mySudoko.printMatrix();
mySudoko.iterativeTest(2);
//mySudoko.solveSudoko();
//mySudoko.printMatrix();
//mySudoko.iterativeTest(2);
return 1;

}
