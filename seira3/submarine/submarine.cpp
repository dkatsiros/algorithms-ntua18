#include <iostream>
#include <set>

using namespace std;

// Class for coordinates
class Coordinates
{
  public:
    int x, y;
    Coordinates(int a, int b)
    {
        x = a;
        y = b;
    }
};

// Class for each PilotCrossing, saving start and end point: (sx,sy) --> (ex,ey)
class PilotCrossing
{
  public:
    int sValue, eValue;
    Coordinates *s = NULL, *e = NULL;

    PilotCrossing(void)
    {
        s = NULL;
        e = NULL;
        sValue = 0;
        eValue = 0;
    }
    void initializePilotCrossing(int M)
    {
        s = new Coordinates(sValue / M, sValue % M);
        e = new Coordinates(eValue / M, eValue % M);
    }
};

// Global Variables

// Table to store table[ e.x , e.y ] = & < s.x , s.y >
Coordinates *InvPilotCrossingTable[180][180];
PilotCrossing pc[100];
long long int possibleSolutionTable[180][180][100];
int N, M, K, X;
int S = 1000000103;


void initializeInvPilotCrossingTable()
{
    for (int i = 0; i < 180; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            InvPilotCrossingTable[i][i] = NULL;
        }
    }
}

bool checkIfPilotCrossingExists(int x, int y)
{
    if (InvPilotCrossingTable[x][y] == NULL)
        return false;
    else
        return true;
}

void initializePossibleSolutionTable(){
    
    for(int i = 0; i < N; i++)
    {
        
        for(int j = 0; j < M ; j++)
        {
            
            for(int k = 0; k < 100; k++)
            {
                possibleSolutionTable[i][j][k] = 0;
            }
            
        }
        
    }
    
}

void createPossibleSolutionTable(int k ){
    
    for (int x = N -1; x >= 0; x--){

        for (int y = M - 1; y>=0; y--){

            if(x == N - 1 && y == M - 1) possibleSolutionTable[x][y][k] = 1;
            else if(x == N - 1 && y != M - 1) {
                possibleSolutionTable[x][y][k] = (
                    possibleSolutionTable[x][y][k] +
                    possibleSolutionTable[x][y + 1][k] ) % S;
            }
            else if(x != N - 1 && y == M - 1){
                possibleSolutionTable[x][y][k] = (
                    possibleSolutionTable[x][y][k] +
                    possibleSolutionTable[x + 1][y][k] ) % S;
            }
            else {
                possibleSolutionTable[x][y][k] = (
                    possibleSolutionTable[x][y][k] +
                    possibleSolutionTable[x + 1][y][k] +
                    possibleSolutionTable[x][y + 1][k] ) % S;
            }
            if( checkIfPilotCrossingExists(x,y) ){

                if( k < X ){
                    Coordinates* temp = InvPilotCrossingTable[x][y];
                    possibleSolutionTable[temp->x][temp->y][k + 1] = (
                        possibleSolutionTable[temp->x][temp->y][k + 1] +
                        possibleSolutionTable[x][y][k] ) % S;
                    possibleSolutionTable[x][y][k] = 0;
                }
                else{
                   possibleSolutionTable[x][y][k] = 0; 
                }
                
            }
        }
    }
}

int main()
{
    // Read input file & initialize invPilotCrossingTable
    scanf("%d", &N);
    scanf("%d", &M);
    scanf("%d", &K);
    scanf("%d", &X);
    initializeInvPilotCrossingTable();
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &pc[i].sValue);
        scanf("%d", &pc[i].eValue);
        pc[i].initializePilotCrossing(M);
        InvPilotCrossingTable[pc[i].s->x][pc[i].s->y] = pc[i].e;
    }
    initializePossibleSolutionTable();
     for (int i = 0; i <= X; i++){
        createPossibleSolutionTable(i);
    }
    printf("%lld\n", possibleSolutionTable[0][0][X]);
    // for(int i = 0 ; i< N ;i ++){
    //     for (int j = 0; j < M ; j++) {
    //         printf("possibleSolutionTable[%d][%d][%d] = %lld\n",i,j,X,possibleSolutionTable[i][j][0]);
    //     }
    // }
    return 0;
}