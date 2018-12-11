#include "AStarSearch.h"

using namespace std;


// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] == 0)
        return (true);
    else
        return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double) ((row-dest.first)
                          + (col-dest.second)));
        // return ((double)sqrt ((row-dest.first)*(row-dest.first)
        //                   + (col-dest.second)*(col-dest.second)));
}

//print out array
void printArray(int temp_vector[][COL], int row, int col)
{
    for (int i = row-1; i >= 0; i--){
        for (int j = 0; j < col; j++){
            cout << temp_vector[i][j]<<" ";
        }
        cout<<endl;
    }
}

//print out vector
void printVector(vector<vector<int> > temp_vector)
{
    for (int i = 0; i < temp_vector.size(); i++){
        for (int j = 0; j < temp_vector[i].size(); j++){
            cout << "vector is: "<<temp_vector[i][j];
        }
        cout<<endl;
    }
}

// calculate distance between two points
double distanceBetweenTwoPoints(double x, double y, double a, double b){
    return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(stack<Pair>& foo, int grid[][COL], cell cellDetails[][COL], Pair src, Pair dest)
{
    printf ("\nThe Path is ");
    int srcRow = src.first;
    int srcCol = src.second;
    int destRow = dest.first;
    int destCol = dest.second;
    int row = dest.first;
    int col = dest.second;
    double steps = -1.0;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        foo.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push (make_pair (row, col));
    foo.push (make_pair (row, col));

    printf ("\nThe Path issssss ");
    /*while (!foo.empty())
    {
         printf ("\ntesting!!! ");
        pair<int,int> q = foo.top();
        foo.pop();
        printf("-> (%d,%d) ",q.first,q.second);
    }*/

     printf ("\nEnd testing!!! ");
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        //printf("-> (%d,%d) ",p.first,p.second);
        grid[p.first][p.second] = 1;
        steps = steps + 1; //number of steps going through
    }
    cout<<endl;
    cout<<"steps are: "<<steps<<endl;
    cout<<"destrow is: "<<" "<<destRow<<"destcol is: "<<" "<<destCol<<"srcRow is: "<<" "<<srcRow<<"srcCol is: "<<" "<<srcCol<<endl;
    cout<<"calculated steps are: "<<distanceBetweenTwoPoints(destRow, destCol, srcRow, srcCol)<<endl;
    printArray(grid, ROW, COL);
    if (steps == distanceBetweenTwoPoints(destRow, destCol, srcRow, srcCol))
    {
        cout<<"straight line!!!!!!!!!!!!"<<endl;
    }else{
        cout<<"No straight line!!!!!!!!!!!!!"<<endl;
    }
    return;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarSearch(stack<Pair>& foo, int grid[][COL], Pair src, Pair dest)
{
    // If the source is out of range
    if (isValid (src.first, src.second) == false)
    {
        printf ("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid (dest.first, dest.second) == false)
    {
        printf ("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == false ||
            isUnBlocked(grid, dest.first, dest.second) == false)
    {
        printf ("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest) == true)
    {
        printf ("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means
    // that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof (closedList));

    // Declare a 2D array of structure to hold the details
    //of that cell
    cell cellDetails[ROW][COL];

    int i, j;

    for (i=0; i<ROW; i++)
    {
        for (j=0; j<COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implenented as a set of pair of pair.*/
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair (0.0, make_pair (i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the open list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;



        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i-1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i-1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (foo, grid, cellDetails, src, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i-1][j] == false &&
                     isUnBlocked(grid, i-1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i-1][j].f == FLT_MAX ||
                        cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair(i-1, j)));

                    // Update the details of this cell
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i+1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i+1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(foo, grid, cellDetails, src, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i+1][j] == false &&
                     isUnBlocked(grid, i+1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i+1][j].f == FLT_MAX ||
                        cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i+1, j)));
                    // Update the details of this cell
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid (i, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(foo, grid, cellDetails, src, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j+1] == false &&
                     isUnBlocked (grid, i, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i][j+1].f == FLT_MAX ||
                        cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                        make_pair (i, j+1)));

                    // Update the details of this cell
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(foo, grid, cellDetails, src, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j-1] == false &&
                     isUnBlocked(grid, i, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i][j-1].f == FLT_MAX ||
                        cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew,
                                          make_pair (i, j-1)));

                    // Update the details of this cell
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}

//promote segment
vector<Point> Promote_segment(vector<Layer> &layerarray, int grid[][COL], APC apc0, APC apc1, double layer1start, double layer2start, double stepxx, double stepyy, int layer_index, vector <ViaResult> &viaarray)
{
    vector<vector<int>> temp_vector;
    vector<vector<int>> longest_vector;
    vector<vector<int>> vect0;
    vector<vector<int>> vect;


    int status;
    if((apc0.promote == false) && ((apc1.promote == false))) status=0;
    if((apc0.promote == false) && ((apc1.promote == true))) status=1;
    if((apc0.promote == true) && ((apc1.promote == false))) status=2;
    if((apc0.promote == true) && ((apc1.promote == true))) status=3;

            if ((status == 2) || (status == 0))
            {
                int first_apc_size = apc0.aps.size();
                int second_apc_size = apc1.aps.size();

                for (int first_idx = 0; first_idx < first_apc_size; first_idx++)
                {
                    vect0.push_back(vector<int>());
                    int row_number = ((int)(apc0.aps[first_idx].yCoordinate) - (int) layer1start) / (int) (stepyy);
                    int column_number = ((int)(apc0.aps[first_idx].xCoordinate) - (int) layer2start) / (int) (stepxx);
                    vect0[first_idx].push_back(row_number);
                    vect0[first_idx].push_back(column_number);
                }

                for (int second_idx = 0; second_idx < second_apc_size; second_idx++)
                {
                    vect.push_back(vector<int>());
                    int row_number = ((int)(apc1.aps[second_idx].yCoordinate) - (int) layer1start) / (int) (stepyy);
                    int column_number = ((int)(apc1.aps[second_idx].xCoordinate) - (int) layer2start) / (int) (stepxx);
                    vect[second_idx].push_back(row_number);
                    vect[second_idx].push_back(column_number);
                }
            }
            else
            {
                int first_apc_size = apc0.aps.size();
                int second_apc_size = apc1.aps.size();

                for (int first_idx = 0; first_idx < first_apc_size; first_idx++)
                {
                    vect.push_back(vector<int>());
                    int row_number = ((int)(apc0.aps[first_idx].yCoordinate) - (int) layer1start) / (int) (stepyy);
                    int column_number = ((int)(apc0.aps[first_idx].xCoordinate) - (int) layer2start) / (int) (stepxx);
                    vect[first_idx].push_back(row_number);
                    vect[first_idx].push_back(column_number);
                }

                for (int second_idx = 0; second_idx < second_apc_size; second_idx++)
                {
                    vect0.push_back(vector<int>());
                    int row_number = ((int)(apc1.aps[second_idx].yCoordinate) - (int) layer1start) / (int) (stepyy);
                    int column_number = ((int)(apc1.aps[second_idx].xCoordinate) - (int) layer2start) / (int) (stepxx);
                    vect0[second_idx].push_back(row_number);
                    vect0[second_idx].push_back(column_number);
                }
            }




    int temp_size = 0;

    for (int k=0; k<vect0.size();k++){
     for (int i = 0; i < vect.size(); i++){
       for (int j = 0; j < vect[i].size(); j++){
            if (vect0[k][j] == vect[i][j]){
                temp_vector.push_back(vect[i]);
                break;
            }
        }
    }
    }

    // cout<<"temp_vector is!!!!!!!!!!!!!!!: "<<endl;
    printVector(temp_vector);
    if (vect0[0][0] == temp_vector[0][0]){
        sort(temp_vector.begin(),temp_vector.end());
        // cout<<"yes!!!!"<<endl;
        printVector(temp_vector);
    }

    temp_size = temp_vector.size();

    stack<Pair> tempp_vector; // path goes through

    Pair src = make_pair(vect0[0][0], vect0[0][1]);
    Pair dest;
    if (vect0[0][0] == temp_vector[0][0]){
        dest = make_pair(temp_vector[0][0], temp_vector[0][1]);
    }
    else {
        dest = make_pair(temp_vector[temp_size-1][0], temp_vector[temp_size-1][1]);
    }
    vector<Point> AAA;


    // int flagg = 0;
    // for (int k=0; k<vect0.size();k++)
    // {
    //     for (int i = 0; i < vect.size(); i++)
    //     {
    //         if (vect0[k] == vect[i])
    //         {
    //             //temp_vector.push_back(vect[i]);
    //             flagg=1;
    //             break;
    //         }
        
    //     }
    // }
   
    // if (flagg == 1)
    // {

    // }
    // else 
    // {
        aStarSearch(tempp_vector, grid, src, dest);

        vector<Pair> temppp_vector;
        while (!tempp_vector.empty())
        {
            temppp_vector.push_back(tempp_vector.top());
            tempp_vector.pop();
        }



        pair <double, double> z;
        for (int i= 0; i<temppp_vector.size(); i++){     //index to real location
            Point temp = Point();
            int xtemp = get<1>(temppp_vector[i]);
            int ytemp = get<0>(temppp_vector[i]);
            temp.xCoordinate = (double) ((double)(xtemp) * stepxx + layer2start);
            temp.yCoordinate = (double) ((double)(ytemp) * stepyy + layer1start);
            AAA.push_back(temp);
        }

        //promote apc
        if (status < 3)         
        {
            pair<int,int> x;
            pair<int,int> y;
            pair<int,int> z;
            vector<Pair> promote_APC;
            // cout<<"x and y starts!!!!!!"<<endl;
            if (temppp_vector.size()!=0)
            {
                for (int i = 0; i < temppp_vector.size(); i++){
                    for (int j = 0; j<vect.size(); j++){
                        // cout<<"starting is: "<<endl;
                        x = temppp_vector[i];
                        y = make_pair(vect[j][0], vect[j][1]);
                         //printf("-> (%d,%d) ",x.first,x.second);
                         //printf("-> (%d,%d) ",y.first,y.second);
                         // cout<<"i is: "<<i<<endl;
                         // cout<<"j is: "<<j<<endl;
                         // cout<<"temppp_vector size is: "<<temppp_vector.size()<<endl;
                         if (x==y){
                            promote_APC.push_back(x);
                            z= promote_APC[promote_APC.size()-1];
                            // cout<<"x==y!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                            //printf("-> (%d,%d) ",z.first,z.second);
                            // cout<<"next one!!!"<<endl;
                         }
                    }
                    //tempp_vector.pop();
                    // cout<<"pop is finished!!!"<<endl;
                }

                APC apctemp = APC();
                apctemp.connect = false;
                apctemp.promote = true;
                int aps_size = promote_APC.size();
                // cout<<"outside aps size is: "<<aps_size<<endl;
                for(int i =0; i < aps_size; i++)
                {
                    // cout << aps_size<<endl;
                    // cout << get<1>(promote_APC[i]) << "  " << get<0>(promote_APC[i]) << endl;
                    // cout << "..." << endl;
                    AP ap_temp = AP();
                    ap_temp.xCoordinate = double (get<1>(promote_APC[i]) * stepxx + layer2start);
                    ap_temp.yCoordinate = double (get<0>(promote_APC[i]) * stepyy + layer1start);
                    apctemp.aps.push_back(ap_temp);
                }
                // cout<<"jump out??"<<endl;
                apctemp.net = apc0.net;
                //cout << layer_index+1 << endl;
                double panelstart;
                int direction;
                panelstart = layerarray[layer_index+1].panelArray[0].left;
                direction = (layer_index + 1) % 2;

                int currentPanelIndex;
                if(direction == 0)
                {
                    currentPanelIndex = (int) (apctemp.aps[0].yCoordinate - panelstart) / (int) layerarray[layer_index+1].unitWidth;
                }
                else
                {
                    currentPanelIndex = (int) (apctemp.aps[0].xCoordinate - panelstart) / (int) layerarray[layer_index+1].unitWidth;
                }
                //cout << currentPanelIndex << endl;
                // cout << "first point: " << apctemp.aps[0].yCoordinate << endl;
                // cout << "panel start: " << panelstart << endl;
                // cout << "unit width: " << layerarray[layer_index+1].unitWidth << endl;
                layerarray[layer_index+1].panelArray[currentPanelIndex].apcArray.push_back(apctemp);
            }
        }

        //save via
        if (status > 0 )
        {
            cout << "pushing back via... " << endl;
            ViaResult via_temp = ViaResult();
            via_temp.net = apc0.net;
            Point point_temp = Point();
            point_temp.xCoordinate = double (get<1>(src) * stepxx + layer2start);
            point_temp.yCoordinate = double (get<0>(src) * stepyy + layer1start);
            via_temp.location = point_temp;
            via_temp.viaType = "VIA";
            via_temp.viaType = via_temp.viaType + std::to_string(layer_index);
            via_temp.viaType = via_temp.viaType + std::to_string(layer_index+1);
            via_temp.viaType = via_temp.viaType + "_1C";
            viaarray.push_back(via_temp);
        }

        if (status == 3 )
        {
            cout << "pushing back via... " << endl;
            ViaResult via_temp = ViaResult();
            via_temp.net = apc0.net;
            Point point_temp = Point();
            point_temp.xCoordinate = double (get<1>(dest) * stepxx + layer2start);
            point_temp.yCoordinate = double (get<0>(dest) * stepyy + layer1start);
            via_temp.location = point_temp;
            via_temp.viaType = "VIA";
            via_temp.viaType = via_temp.viaType + std::to_string(layer_index);
            via_temp.viaType = via_temp.viaType + std::to_string(layer_index+1);
            via_temp.viaType = via_temp.viaType + "_1C";
            viaarray.push_back(via_temp);

        }
    // }




    

    //return promote_APC;

    return AAA;
}


int vector_uniqueness(vector<int> vec){
    int unique_elements = 0;
    vector< int > used;
    for ( vector< int >::const_iterator it = vec.cbegin(); it != vec.cend(); ++it )
    {
        if ( find( used.cbegin(), used.cend(), *it ) == used.cend() )
        {
            used.push_back(*it);
            ++unique_elements;
        }
    }
    cout<<"unique element is: "<<unique_elements<<endl;
    return unique_elements;
}
// Driver program to test above function
void APC_process(vector <Layer> &layerarray, vector <SegmentResult> &segmentarray, vector <ViaResult> &viaarray, int layer_index, int panelIdx, double layer1start, double layer2start, double stepxx, double stepyy)
{

    //COL = layerarray[layer_index].COL;
    //ROW = layerarray[layer_index].ROW;

    cout << "connecting apc ..." << endl;

    int grid[ROW][COL];

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            grid[i][j] = layerarray[layer_index].congestionGridArray[i*COL+j].used;
        }
    }


    for (int i =0; i<layerarray[layer_index].panelArray[panelIdx].apcArray.size(); i++)
    {
        //vector<int> apcvect;
        vector<APC> to_be_connected;
        std::string currentNet;
        
            if (layerarray[layer_index].panelArray[panelIdx].apcArray[i].connect == true){
                continue;
            }

        for (int j =i; j<layerarray[layer_index].panelArray[panelIdx].apcArray.size(); j++)
        {
            if ((layerarray[layer_index].panelArray[panelIdx].apcArray[i].net == layerarray[layer_index].panelArray[panelIdx].apcArray[j].net) && (layerarray[layer_index].panelArray[panelIdx].apcArray[j].connect != true)){
                layerarray[layer_index].panelArray[panelIdx].apcArray[j].connect = true; // set to_be_connected to true
                //apcvect.push_back(panel.apcArray[j]);
                //Promote_APC(grid, panel.apcArray[i], panel.apcArray[j]);
                to_be_connected.push_back(layerarray[layer_index].panelArray[panelIdx].apcArray[j]);
                currentNet = layerarray[layer_index].panelArray[panelIdx].apcArray[i].net;
            }
        }

        bool hasPromote;
        hasPromote = false;
        //cout << "to be connected size" << to_be_connected.size()-1 << endl;
        for (int i = 0; i<to_be_connected.size(); i++)
        {
            if (to_be_connected[i].promote == true)
                {hasPromote = true;
                cout << "promote!" << endl;}  
        }
        //a start
        if(hasPromote == true)
        {
            //cout << "to be connected size" << to_be_connected.size()-1 << endl;
            for (int i = 0; i<to_be_connected.size()-1; i++)
            {

                cout << "connecting two apc ..." << endl;
                SegmentResult segment_temp = SegmentResult();
                cout << "apc0 size: " << to_be_connected[i].aps.size() << " apc1 size: " << to_be_connected[i+1].aps.size() << " net: " << to_be_connected[i].net << endl;
                cout << "apc0 first: " << to_be_connected[i].aps[0].xCoordinate << " " << to_be_connected[i].aps[0].yCoordinate;
                cout << " apc0 last: " << to_be_connected[i].aps[to_be_connected[i].aps.size()-1].xCoordinate << " " << to_be_connected[i].aps[to_be_connected[i].aps.size()-1].yCoordinate << endl;
                cout << "apc1 first: " << to_be_connected[i+1].aps[0].xCoordinate << " " << to_be_connected[i+1].aps[0].yCoordinate;
                cout << " apc1 last: " << to_be_connected[i+1].aps[to_be_connected[i+1].aps.size()-1].xCoordinate << " " << to_be_connected[i+1].aps[to_be_connected[i+1].aps.size()-1].yCoordinate << endl;
                segment_temp.pointArray = Promote_segment(layerarray, grid, to_be_connected[i], to_be_connected[i+1], layer1start, layer2start, stepxx, stepyy, layer_index, viaarray);
                
                segment_temp.net = to_be_connected[i].net;
                segment_temp.layerName = "Metal";
                segment_temp.layerName = segment_temp.layerName + std::to_string(layer_index+1);
                segmentarray.push_back(segment_temp);
            }
        }
    }

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            layerarray[layer_index].congestionGridArray[i*COL+j].used = grid[i][j];
        }
    }

}












