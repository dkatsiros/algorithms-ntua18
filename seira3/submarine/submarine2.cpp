    #include <iostream>
    #include <set>

    using namespace std;

    typedef int pcint;

    
    // Class for coordinates 
    class Coordinates{
        public: 
            int x,y;
            Coordinates(int a, int b){
                x = a;
                y = b;
            }
    };
    
    // Class for each PilotCrossing, saving start and end point: (sx,sy) --> (ex,ey)
    class PilotCrossing{
        public: 
            int sValue, eValue;
            Coordinates *s = NULL, *e = NULL;

            PilotCrossing(void) {
                s = NULL;
                e = NULL;
                sValue = 0;
                eValue = 0; 
        }
            void initializePilotCrossing(int M){
                    s = new Coordinates(sValue / M , sValue % M);
                    e = new Coordinates(eValue / M , eValue % M);
            }
    };

    // Global Variables
    
    // Table to store table[ e.x , e.y ] = & < s.x , s.y >
    Coordinates *InvPilotCrossingTable[180][180];
    PilotCrossing pc[100];
    int possibleSolutionTable[180][180][100];
    int N,M,K,X;
    int globalId;

    void initializePossibleSolutionTable(){
        
        for(int i = 0; i < 180; i++)
        {
            
            for(int j = 0; j < 180; j++)
            {
                
                for(int k = 0; k < 100; k++)
                {
                    possibleSolutionTable[i][j][k] = -1;
                }
                
            }
            
        }
        
    }

    bool isOutOfMatrix(int x, int y){
        if (x > N - 1 || x < 0 || y > M - 1 || y < 0) return true; else return false;
    }

    void initializeInvPilotCrossingTable(){
        for (int i = 0; i< 180; i++){
            for(int j = 0; j < 180; j++){
                InvPilotCrossingTable[i][i] = NULL;
            }
        }
    }

    bool checkIfPilotCrossingExists(int x, int y){
        if( InvPilotCrossingTable[x][y] == NULL) return false;
        else return true;
    }

    int possibleSolution(int x, int y, int k){
        int downPossibleSolutions = 0, rightPossibleSolutions = 0;
        bool downExists = !isOutOfMatrix( x + 1, y );
        bool rightExists = !isOutOfMatrix( x , y - 1);

        // Down check
        if (downExists){

            // if PilotCrossing exists get these solutions
            if ( checkIfPilotCrossingExists( x + 1, y ) ){
                Coordinates *tempCoordinates = InvPilotCrossingTable[x + 1][y];
                // Check if we dont already have found solutions there
                if (possibleSolutionTable[tempCoordinates->x][tempCoordinates->y][k] == -1 )
                {
                    downPossibleSolutions = possibleSolution(tempCoordinates->x, tempCoordinates->y,k + 1);
                    possibleSolutionTable[tempCoordinates->x][tempCoordinates->y][k] = downPossibleSolutions;
                }
                else if (possibleSolutionTable[tempCoordinates->x][tempCoordinates->y][k] + k < K)  
                {   
                    downPossibleSolutions = possibleSolutionTable[tempCoordinates->x][tempCoordinates->y][k];
                }
            }

            // No PilotCrossing so just check down box
            else{
                // Check if we already have found solutions there(?)
                if (possibleSolutionTable[x + 1][y] != -1){
                    // yes we have found
                    downPossibleSolutions = possibleSolutionTable[x + 1][y];
                }
                else{
                    // no, compute them
                    downPossibleSolutions = possibleSolution( x + 1, y );
                    possibleSolutionTable[x + 1][y] = downPossibleSolutions;
                }
            }
        }
        else{
            // down box doesnt exist. We should return 0;
            downPossibleSolutions = 0;
        }

        // Right check
        if (rightExists)
        {

            // if PilotCrossing exists get these solutions
            if (checkIfPilotCrossingExists(x , y - 1))
            {
                Coordinates *tempCoordinates = InvPilotCrossingTable[x][y - 1];
                // Check if we already have found solutions there
                if (possibleSolutionTable[tempCoordinates->x][tempCoordinates->y] != -1)
                {
                    rightPossibleSolutions = possibleSolutionTable[tempCoordinates->x][tempCoordinates->y];
                }
                else
                {
                    rightPossibleSolutions = possibleSolution(tempCoordinates->x, tempCoordinates->y);
                    possibleSolutionTable[tempCoordinates->x][tempCoordinates->y] = rightPossibleSolutions;
                }
            }

            // No PilotCrossing so just check down box
            else
            {
                // Check if we already have found solutions there(?)
                if (possibleSolutionTable[x][y - 1] != -1)
                {
                    // yes we have found
                    rightPossibleSolutions = possibleSolutionTable[x][y - 1];
                }
                else
                {
                    // no, compute them
                    rightPossibleSolutions = possibleSolution(x , y - 1);
                    possibleSolutionTable[x][y - 1] = rightPossibleSolutions;
                }
            }
        }
        else
        {
            // down box doesnt exist. We should return 0;
            rightPossibleSolutions = 0;
        }

        // Now we have the values
        return downPossibleSolutions + rightPossibleSolutions;
    }

    int main(){
        // Read input file & initialize invPilotCrossingTable
        scanf("%d", &N);
        scanf("%d", &M);
        scanf("%d", &K);
        scanf("%d\n", &X);
        initializeInvPilotCrossingTable();
        for (int i = 0; i < K ; i++){
            scanf("%d", &pc[i].sValue);
            scanf("%d", &pc[i].eValue);
            pc[i].initializePilotCrossing(M);
            InvPilotCrossingTable[ pc[i].e->x ][ pc[i].e->y ] = pc[i].s;
        }

        return 0;
    }