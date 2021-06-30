//package minimumties;

import java.util.*;
import java.io.*;

public class minimumties {
	public static void main(String[] args) throws IOException {
		
		//1487C
		
		//i use the following greedy algorithm to generate all the outcomes of games.
		//we first must notice that given an odd number of teams, you can always generate the outcomes so that there are no ties. This is because
		//each team plays an even amount of other teams, so they can just win half and lose half of their games. If there is an even number of teams, 
		//then each team must tie once in order for their scores to be equal; win half, lose half, and tie one because of playing an odd number of teams.
		//So to generate, all you have to do is go along and make each team win against the next n / 2 teams if n % 2 = 1, or (n - 2) / 2 if n % 2 = 0. 
		//then if n % 2 = 0, then you make the team tie against the next team, and then lose against all other teams.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int winCount = n % 2 == 0? (n - 2) / 2 : n / 2;
			int tieCount = (n + 1) % 2;
			for(int i = 0; i < n; i++) {
				int wins = 0;
				int ties = 0;
				for(int j = i + 1; j < n; j++) {
					if(wins < winCount) {
						fout.append("1 ");
						wins ++;
					}
					else if(wins == winCount && ties < tieCount) {
						fout.append("0 ");
						ties ++;
					}
					else {
						fout.append("-1 ");
					}
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
