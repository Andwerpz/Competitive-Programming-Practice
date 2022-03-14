//package playoff;

import java.util.*;
import java.io.*;

public class playoff {
	public static void main(String[] args) throws IOException {
		
		//1651A
		
		//In the first round, all the even indexed players are eliminated. 
		
		//in every other round, the highest indexed player will win, thus, the player 2^n - 1 will always win.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			fout.append((long) Math.pow(2, n) - 1).append("\n");
		}
		System.out.print(fout);
	}
}
