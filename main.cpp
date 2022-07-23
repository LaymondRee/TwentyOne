/**************************************************
 * Program: assignment2.cpp
 * Author: Raymond Lee
 * Date: 01-31-21
 * Description: Twenty-one, a game similar to Blackjack
 * Input: integers
 * Output: The game twenty-one
**************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int player_total(); //Controls player's hand total
int dealer_total(); //Controls dealer's hand total

int main() {
	srand(time(NULL));
	int players = 0;
	int bank[] = {0,0,0,0};
	int bet[] = {0,0,0,0};
	int total[] = {21,21,21,21};
	int dealer = 0;
	int again = 2;

	cout << "How many players (1-4)?" << endl; //Enter amount of players
	cin >> players;
	cout << endl;

	while (players > 4 || players < 1){ //Handle bad user input for players
		cout << "Please enter a number between 1 and 4" << endl;
		cin >> players;
		cout << endl;
	}

	cout << "Playing with " << players << " players" << endl;

	for (int i = 0; i < players; i++){ //Enter starting money for players
		do {
			cout << "Enter money for player " << i + 1 << ": ";
			cin >> bank[i];
		}while (bank[i] <= 0); //Handle bas user input for money
	}

	cout << endl;

	for (int i = 0; i < players; i++){ //Print total money of players
		cout << "Player " << i + 1 << " has: $" << bank[i] << endl;
	}

	cout << endl;

	do {
		again = 2;

		for (int i = 0; i < players; i++){ //Enter bet for players
			if (bank[i] > 0){
			do{
			cout << "Enter bet for player " << i + 1 << ": ";
			cin >> bet[i];
			}while (bet[i] > bank [i] || bet[i] <= 0); //Handle bad user input for bets
			}
		}
		
		cout << endl;

		for (int i = 0; i < players; i++){ //Print all player bets
			if (bank[i] > 0){
			cout << "Player " << i + 1 << " bet: $" << bet[i] << endl;
			}
		}

		cout << endl;

		for (int i = 0; i < players; i++){ //Players decide to hit or stand
			if (bank[i] > 0){
				cout << "Player " << i + 1 <<  ":" << endl;
				total[i] = player_total();
				if (total[i] > 21){ //Player busts and automatically loses
					bank[i] -= bet[i];
					cout << "Player " << i + 1 << " is now at $" << bank[i] << endl << endl;
				}else if (total[i] == 21){ //Player gets 21 and automatically gets payout
					bank [i] += bet[i];
					cout << "Player " << i + 1 << " now at $" << bank[i] << endl << endl;
				}
			}
		}

		if ((total[0] < 21) || (total[1] < 21) || (total[2] < 21) || (total[3] < 21)){
			cout << "Dealer:" << endl; //Gives dealer total
			dealer = dealer_total();
		}

		for (int i = 0; i < players; i++){ //Controlls player payouts
			if (bank[i] > 0){
				if ((total[i] > dealer) && (total[i] < 21) && (dealer <= 21)){ //Player has higher total
					bank[i] += bet[i];
					cout << "Player " << i + 1 << " had a higher total than the dealer" << endl;
					cout << "Player " << i + 1 << " now has $" << bank[i] << endl << endl;
				}else if ((total [i] < dealer) && (total[i] < 21) && (dealer <= 21)){
					bank[i] -= bet[i];
					cout << "Player " << i + 1 << " had a lower total than the dealer" << endl; //Dealer has higher total
					cout << "Player " << i + 1 << " now has $" << bank[i] << endl << endl;
				}else if ((total[i] == dealer) && (total[i] < 21) && (dealer <= 21)){ //Same total
					cout << "Player " << i + 1 << " had the same total as the dealer" << endl;
					cout << "Player " << i + 1 << " now has $" << bank[i] << endl << endl;
				}else if ((dealer > 21) && total[i] < 21){ //Dealer goes over 21
					bank[i] += bet[i];
					cout << "The dealer busted" << endl;
					cout << "Player " << i + 1 << " now has $" << bank[i] << endl << endl;
				}
			}
		}


	cout << "The new $ totals are:" << endl;

	for (int i = 0; i < players; i++){ //Relists total money of players
		cout << "Player " << i + 1 << " has: $" << bank[i] << endl;
	}

	cout << endl;

	if (bank[0] + bank[1] + bank[2] + bank[3] == 0){ //End game if all players out of money
		cout << "Sorry, you are all out of money" << endl;
		exit(EXIT_FAILURE);
	}

	while (again != 1 && again != 0){ //Handles bad user inputs for playing again
		cout << endl << "Would you like to (1) play again or (0) cash out?" << endl;
		cin >> again;
	}

	}while (again == 1); //Controls if another round will be played

	return 0;
}

int player_total(){ //Controls player's total
	int total = 0;
	int hit = 0;

	do{
		int card = (rand() % 11) + 1; //Generates number between 1 and 11
		total += card; // Adds card to total
		cout << "You drew " << card << ", your total is " << total << endl;

		if (total == 21){
			cout << "You won!" << endl;
			break;

		}else if (total > 21){
			cout << "You lose!" << endl;
			break;

		}else{
			hit = 2;
				while (hit != 1 && hit != 0){ //Handles bad user input for hit or stand
				cout << "Hit (1) or Stand (0)" << endl;
				cin >> hit;	
			}
		}
	}while (hit == 1);

	cout << endl;

	return total;
}

int dealer_total(){ //Controls dealer's total
	int total = 0;
	char buffer = ' ';

	do{
		int card = (rand() % 11) + 1;
		total += card;
		cout << "The dealer drew " << card << " their total is " << total << endl;
		cout << "Press any key to continue" << endl;
		cin >> buffer; //Gives time for player to see what dealer gets
	}while (total < 16); //Dealer hits until they reach 15

	cout << endl;

	return total;
}
