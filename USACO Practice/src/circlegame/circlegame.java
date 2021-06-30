//package circlegame;

import java.util.*;
import java.io.*;

public class circlegame {
	public static void main(String[] args) throws IOException {
		
		//1451D
		
		//either player can force the token to alway return to the line denoted by x = y. The player who wants to force can just do the opposite move every time. 
		//so it is guaranteed that the token will reach the maximum point (kz, kz) where it is still inside the circle. Now, if (kz, k(z + 1)) is still inside
		//the circle, then player 1 wins, else player 2 wins.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0 ) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long d = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int moves = 0;
			long x = 0;
			long y = 0;
			boolean turn = true;
			while(x * x + y * y <= d * d) {
				if(turn) {
					turn = false;
					x += k;
				}
				else {
					turn = true;
					y += k;
				}
				moves ++;
			}
			//System.out.println(moves);
			if(moves % 2 == 1) {
				fout.append("Utkarsh\n");
			}
			else{
				fout.append("Ashish\n");
			}
		}
		System.out.print(fout);
	}
}
