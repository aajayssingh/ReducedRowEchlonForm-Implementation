#include <iostream>
#include <iomanip>
#define NROW 4
#define NCOL 6


using namespace std;
void interchangeRows(int i, int j, int colNum);
void addRows(int kRow, int iRow, float Akj, int colNum);
void printMatrix(int n, int m);
bool colZero(int begRow, int jCol, int rowNum);
int rankOfAugMatrix(int n, int m);
int rankOfMatrixA(int n, int m);


//float Matrix[NROW][NCOL] = {1,  2,  1,  1, 0, 0,
//2,  5, -1,  0, 1, 0,
//3, -2, -1,  0, 0, 1};


float Matrix[NROW][NCOL] = {0, 2, 3, 0, 0, 1,
4,1, -1,0,2,0,
0,1,1,0,0,0,
1,3,1,7,-2,4};


int main()
{
//var declaration :
int row_index = 0, col_index = 0, row_tf_index = 0;
int i, j, k, m, n, numVariables = 0, rankA = 0, rankAug = 0;



n = NROW;
m = NCOL;
cout<<"given Matrix is : "<<endl;
printMatrix(n, m);
cout<<endl;
//#if 0
//cout << "Hello world!" << Matrix[0][1]/Matrix[0][2]<<endl;
/**************Begin calculating RREF*************************/
col_index = 0;
for(row_index = 0; row_index < n; row_index++)
{
//cout<<"ROW "<<row_index<<"----->"<<endl;

        while(colZero(row_index, col_index, n))
        {
           // cout<<"col zero at "<<col_index<<endl;
            col_index += 1;

            if(col_index >= m)
            {
                //The current matrix is in row echlon form.
                cout<<"Matrix in RREF"<<endl;
                printMatrix(n, m);
                {
                    numVariables = m-1; //#cols -1 = #unknown variables (removing augmentation)
                    rankA = rankOfMatrixA(n, m);
                    rankAug = rankOfAugMatrix(n, m);
                    cout<<"The Matrix rank is "<<rankAug<<endl;
                    if(rankA == rankAug)
                    {
                        if(numVariables == rankA)
                        {
                            cout<<"The system has unique sol (";
                            //printing last col of augmented matrix
                            for(i = 0; i < n; i++)
                                cout<<Matrix[i][m-1]<<" ";

                            cout<<")";
                        }
                        else if(rankA < numVariables)
                        {
                            cout<<"The system has Infinite solutions described by an affine subspace of dimension "<<(numVariables - rankA);
                        }
                    }
                    else if(rankA < rankAug)
                    {
                        cout<<"The system has No sol";
                    }




                }
                exit(0);
            }

        }
//        if(colZero(row_index, col_index, n))
//        {
//            cout<<"col zero at "<<col_index<<endl;
//            col_index += 1;
//        }




//find first non zero element in same col in lower rows in case if pivot element is 0.
    if(Matrix[row_index][col_index] == 0)
    {
        for(i = row_index + 1;i < n; i++)
        {
            if(Matrix[i][col_index] != 0)
            {
                //cout<<"interchange "<<i<<" "<<row_index<<endl;
                interchangeRows(i, row_index, m);
                break;
            }
        }
    }

    //cout<<"pivot is -->"<<Matrix[row_index][col_index]<<" at "<<row_index<<col_index<<endl<<endl;

    //ensure pivot element is 1 div each ele of row by pivot value
    //cout<<"dividing"<<endl;
    float dm = Matrix[row_index][col_index];
    for(j = 0; j < m; j++)
    {
        if(Matrix[row_index][col_index] != 0)
        {
            float nm = Matrix[row_index][j];
            //float dm =
            Matrix[row_index][j] = nm/dm;
            //cout<<" "<<nm/dm;
        }
    }

//    cout<<endl<<"after div by "<<Matrix[row_index][col_index]<<endl;
//    printMatrix(n,m);
//    cout<<endl;

    for(k = 0; k < n; k++)
    {
        if(k != row_index)
        {
            addRows(k, row_index, Matrix[k][col_index], m);
        }
    }

//    cout<<"after opn "<<endl;
   // printMatrix(n,m);




}//end for(row_index = 0; row_index < n; row_index++)




/**************End calculating RREF*************************/

cout<<"RREF form of matrix is : "<<endl;
printMatrix(n, m);
cout<<endl;
//#endif // 0

numVariables = m-1; //#cols -1 = #unknown variables (removing augmentation)
rankA = rankOfMatrixA(n, m);
rankAug = rankOfAugMatrix(n, m);
cout<<"The Matrix rank is "<<rankAug<<endl;
if(rankA == rankAug)
{
    if(numVariables == rankA)
    {
        cout<<"The system has unique sol (";
        //printing last col of augmented matrix
        for(i = 0; i < n; i++)
            cout<<Matrix[i][m-1]<<" ";

        cout<<")";
    }
    else if(rankA < numVariables)
    {
        cout<<"The system has Infinite solutions described by an affine subspace of dimension "<<(numVariables - rankA);
    }
}
else if(rankA < rankAug)
{
    cout<<"The system has No sol";
}


    return 0;
}

void interchangeRows(int i, int j, int colNum)
{
    float temp = 0;
    for(int k = 0; k < colNum; k++)
    {
        temp = Matrix[i][k];
        Matrix[i][k] = Matrix[j][k];
        Matrix[j][k] = temp;
    }

}

//Rk  <-- Rk - Ri*Akj  (Akj is pivot element)
void addRows(int kRow, int iRow, float Akj, int colNum)
{
    for(int t = 0; t < colNum ; t++)
    {
        Matrix[kRow][t] = Matrix[kRow][t] - Akj * (Matrix[iRow][t]);
    }
}

void printMatrix(int n, int m)
{
    int i = 0, j = 0;
    for(i = 0;i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            cout<<setprecision(2)<<fixed<<Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool colZero(int begRow, int jCol, int rowNum)
{
    for(int i = begRow; i < rowNum; i++)
    {
        if(Matrix[i][jCol] != 0)
        {
            return false;
        }
    }
    return true;

}

int rankOfAugMatrix(int n, int m)
{

//find nuber of 0 rows
 int i = 0, j = 0, matrixRank = 0;;
    for(i = 0;i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(0 != Matrix[i][j])
            {
                //matrixRank++;
                break;
            }
            //cout<<Matrix[i][j]<<" ";
        }
        if(j < m)
        {
            matrixRank++;
        }
    }

    return matrixRank;

}

int rankOfMatrixA(int n, int m)
{
    int i = 0, j = 0, matrixRank = 0;
    m = m-1;//remove augmentation

    for(i = 0;i < n; i++)//rows
    {
        for(j = 0; j < m; j++)//cols
        {
            if(0 != Matrix[i][j])
            {
                //matrixRank++;
                break;
            }
            //cout<<Matrix[i][j]<<" ";
        }
        if(j < m)
        {
            matrixRank++;
        }
    }

    return matrixRank;

}

