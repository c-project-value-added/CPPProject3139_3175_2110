#include<bits/stdc++.h>
using namespace std;

//Structure to save the player details
struct player
{
	int id;
	int rating;
};


//Function to calculate the maximum weight for card replacement
template <typename T>
T return_max_index(T a1, T a2, T a3, T a4)
{
    int maximum=a1,max_index=0;
    if(a2>maximum)
    {
        maximum=a2;
        max_index=1;
    }
    else if(a3>maximum)
    {
        maximum=a3;
        max_index=2;
    }
    else if(a4>maximum)
    {
        maximum=a4;
        max_index=3;
    }
    return max_index;
}

//Function to save the player data on the first time execution of the program
void enter_player_data()
{
	FILE *outfile;
	outfile=fopen("players.dat","w");
	cout<<"\nEnter the details for the first time use:\n";
	for(int i=0; i<4; i++)
    {
        struct player p;
        cout<<"\nEnter the Player ID:";
        cin>>p.id;
        cout<<"\nEnter the player rating (either 1 - Conservative or 2- Aggressive):\n";
        cin>>p.rating;
        fwrite(&p, sizeof(struct player), 1, outfile);
        if(fwrite != 0)
        {
            cout<<"contents to file written successfully !\n";
        }
        else
        {
            cout<<"Error writing file !\n";
        }
    }
	fclose(outfile);
}

int main ()
{
    char choice;
    cout<<"\n Are you using the program for the first time(Y/N)";
    cin>>choice;
    if(choice=='y'||choice=='Y')
    {
        enter_player_data();
    }

    FILE*infile;
    infile = fopen ("players.dat", "r");
    if(infile == NULL)
    {
        cout<<"\nError opening file. Ending the program\n";
        exit(1);
    }
    struct player p;
    struct player players[4];
    int i=0;
    while(fread(&p, sizeof(struct player), 1, infile))
    {
        players[i].id=p.id;
        players[i].rating=p.rating;
        i+=1;
    }
    cout<<"\nThe player details are as follows:";
    for(i=0;i<4;i++)
    {
        cout<<"\nPlayer ID:"<<players[i].id;
        cout<<"\nPlayer Rating:"<<players[i].rating;
    }


    int p_id;
    int p_rating;
    cout<<"\nEnter the player ID of the player for whom you want to get the predicted moves:";
    cin>>p_id;
    for(i=0;i<4;i++)
    {
        if(players[i].id==p_id)
        {
            p_rating=players[i].rating;
        }
    }
    int arr[4];
    int lower=1, upper = 4;
    srand(time(0));
    cout<<"\nThe current cards with the player are:\n";
    for(i=0; i<4; i++)
    {
        arr[i]=(rand()%(upper-lower+1))+lower;
        cout<<arr[i]<<endl;
    }
    int flag=0;
    vector <int> switches;//Vector to save the replaced cards of the player
    //While loop to predict the next move of the player until the player wins the match
    while(flag!=1)
    {
        int counter[4]={0,0,0,0};
        float weight[4]={0.0,0.0,0.0,0.0};
        for(i=0; i<4; i++)
        {
            if(arr[i]==1)
            {
                counter[0]+=1;
            }
            else if(arr[i]==1)
            {
                counter[1]+=1;
            }
            else if(arr[i]==1)
            {
                counter[2]+=1;
            }
            else
            {
                counter[3]+=1;
            }
        }
        int min_index=0;
        for(i=1;i<4;i++)
        {
            if(counter[i]<counter[min_index] && counter[i]!=0)
            {
                min_index=i;
            }
        }
        if(p_rating==1)
        {
            if(switches.size()==0)
            {
                switches.push_back(min_index);
                cout<<"\nThe card exchanged is "<<min_index+1;
                arr[min_index]=(rand()%(upper-lower+1))+lower;
            }
            else
            {
                for(i=0;i<switches.size();i++)
                {
                    int num=switches[i];
                    if(counter[num]!=0) weight[num]+=1;
                }
                for(i=0;i<4;i++)
                {
                    float temp=weight[i];
                    weight[i]=(float)(temp/switches.size())-(float)(counter[i]/switches.size());
                }
                min_index=return_max_index(weight[0],weight[1],weight[2],weight[3]);
                switches.push_back(min_index);
                cout<<"\nThe card exchanged is "<<min_index+1;
                arr[min_index]=(rand()%(upper-lower+1))+lower;
            }
        }
        else
        {
            cout<<"\nThe card exchanged by the player is "<<min_index+1;
            arr[min_index]=(rand()%(upper-lower+1))+lower;
            switches.push_back(min_index);
        }
        cout<<"\nThe cards currently with the player are as follows: ";
        for(i=0;i<4;i++)
        {
            cout<<arr[i]<<" ";
        }
        if(arr[0]==arr[1]==arr[2]==arr[3])
        {
            cout<<"\nThe player has won the game.";
            flag=1;
            break;
        }
    }
	return 0;
}
