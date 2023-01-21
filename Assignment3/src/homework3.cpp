//BLG 335E ANALYSIS OF ALGORITHMS 1 HOMEWORK 3
//Leminur Çelik
//150190085
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "../include/homework3.h"

using namespace std;

int main(int argc, char **argv){
    string input = argv[1]; //Get the input file from the command line
    auto t1 = clock(); //Time starts
    fstream file (input, ios::in); //Define the input file as file
    int numprocesses; //Initialize how many processes will be in the input file
    int runtime; //Initialize simulator run time
    RBTree rbt; //Create a red black tree
    Node* minimum; //Create a minimum node
    Node* process = new Node; //Create a process node
    int count_complete = 0; //Count the complete nodes 

    if(file.is_open()){
            file >> numprocesses; //Read how many processes from file
            string process_name[numprocesses]; //Create a string array to store name of processes with the size of number of processes
            int time_of_arrival[numprocesses]; //Create an integer array to store arrival time of processes with the size of number of processes
            int burst_time[numprocesses]; //Create an integer array to store burst time of processes with the size of number of processes
            string array[numprocesses]; //Hold the completed nodes
            file >> runtime; //Read CPU time from file
            for (int i = 0; i < numprocesses; i++){
                file >> process_name[i]; //Put process name property into the array
                file >> time_of_arrival[i]; //Put time of arrival property into the array
                file >> burst_time[i]; //Put burst time property into the array
            }
            for (int i = 0; i < runtime; i++){ //Repeat until the max allocated time for the simulation is finished
                cout << i << ","; //Print the CPU time
                for (int j = 0; j < numprocesses; j++){
                    if (i == time_of_arrival[j]){ //If CPU time is equal to time of arrival of any nodes, then insert this node into the tree
                        Node* new_insert = new Node; //Create a new Node
                        new_insert->name = process_name[j]; //Assign the name of node to corresponding name
                        new_insert->bursttime = burst_time[j]; //Assign the burst time of node to corresponding burst time
                        rbt.insert(new_insert->name, new_insert->vruntime, new_insert->bursttime); //Insert a node into the red black tree
                    }
                }
                if(rbt.getRoot()->name != ""){ //If there is a node in the tree, then calculate few things below
                    minimum = rbt.minimum(rbt.getRoot()); //Find the minimum node to use minimum function which takes root as an input
                    cout << minimum->name << "," << minimum->vruntime << "," << minimum->vruntime << ","; //Print current task's name, current task's virtual run time, minimum virtual run time
                    if(rbt.exist_minimum(minimum)){ //If there are nodes smaller than or equal to the virtual run time of the minimum node, then delete the minimum node and check if it will be inserted again
                        string name = minimum->name; //Assign a name to the name of the minimum node
                        int burst_time = minimum->bursttime; //Assign a burst time to the burst time of the minimum node
                        int vruntime = minimum->vruntime; //Assign a virtual run time to the virtual run time of the minimum node
                        rbt.print_inorder(rbt.getRoot()); //Print the tree using inorder traversal
                        rbt.deleteNode(rbt.getRoot(),minimum->vruntime, minimum->name); //Delete the minimum node
                        process->vruntime = vruntime; //Assign process' virtual run time to minimum's virtual run time
                        process->vruntime++; //Update the current process by incrementing its run time value 
                        process->name = name; //Assign process' name to minimum's name
                        process->bursttime = burst_time; //Assign process' burst time to minimum's burst time
                        if(process->vruntime < process->bursttime){ //If the run time of the currently running task is smaller than the burst time, then insert it again
                            rbt.insert(process->name, process->vruntime, process->bursttime);
                            cout << "Incomplete" << endl;
                        }
                        else{ //If the virtual run time of the currently running task is not smaller than the burst time, then put it into array
                            count_complete++; //Increment the completed nodes
                            array[count_complete-1] = process->name; //Assign array's value to the name of the currently running task
                            if(count_complete == numprocesses){ //If completed nodes number is equal to the number of process, then end of the simulation
                                cout << "Completed" << endl;
                            }
                            else{ //If completed nodes number is not equal to the number of process, then the currenly running task is completed
                                cout << "Complete" << endl;
                            }
                        }
                    }  
                    else{ //If there are not any nodes smaller than or equal to the run time of the minimum node, then update the virtual run time of the minimum node and check if it will be reached its burst time
                        rbt.print_inorder(rbt.getRoot()); //Print the tree using inorder traversal
                        minimum->vruntime++; //Update the current process by incrementing its virtual run time value 
                        if(minimum->vruntime >= minimum->bursttime){ //If the current process is reached its burst time, then put it into array and delete it
                            count_complete++; //Increment the completed nodes
                            array[count_complete-1] = minimum->name; //Assign array's value to the name of the currently running task
                            rbt.deleteNode(rbt.getRoot(),minimum->vruntime, minimum->name); //Delete the minimum node
                            if(count_complete == numprocesses){ //If completed nodes number is equal to the number of process, then finish the simulation
                                cout << "Completed" << endl;
                                break; //If all the processes are completed, then finish the simulation
                            }
                            else{ //If completed nodes number is not equal to the number of process, then the currenly running task is completed
                                cout << "Complete" << endl;
                            }
                        }
                        else{ //If the current process is not reached its burst time, then the currenly running task is not completed
                            cout << "Incomplete" << endl;
                        }
                    }
                }
                else{ //If there is not any node in the tree, then calculate nothing and print dashes
                    cout << "-,-,-,-,-,-" << endl;
                }
            }
            cout << endl;
            auto t2 = clock();//Time stops
            cout << "Scheduling finished in " << ((double)(t2-t1)/CLOCKS_PER_SEC) * 1000 << " ms." << endl; //Print execution time
            cout << count_complete << " of " << numprocesses << " processes are completed." << endl; //Print how many processes are completed
            cout << "The order of completion of the tasks: "; //Print the order of completion of the tasks
            for(int i = 0; i < count_complete; i++){
                cout << array[i]; //Print the names of the nodes in order of completion
                if((i + 1) != count_complete){
                    cout << "-";
                }
            }
            cout << endl;
    }
	return 0;
}