//package twoknights;

import java.util.*;
import java.io.*;

public class twoknights {
	public static void main(String[] args) throws IOException {
		
		//CSES 1072
		
		//we can hardcode solutions for 1x1 and 2x2 boards. 
		
		//for 3x3 and above, notice that the number of bad positions of the 2 knights is equal to the amount of times you can
		//fit a 3x2 rectangle x4. In a 3x2 rectangle, there are 2 possible positions where the knights would attack, and there are
		//2 possible rotations that you can fit 3x2 rectangles, the other being 2x3. 
		
		//the total amount of positions the knights can be placed is (n^2) * (n^2 - 1) / 2. So the ans is the total amount of positions
		//minus the amount of invalid positions.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		for(long i = 1; i <= n; i++) {
			if(i == 1) {
				fout.append("0\n");
			}
			else if(i == 2) {
				fout.append("6\n");
			}
			else {
				long atk = (i - 1) * (i - 2) * 4;
				long place = ((i * i) * (i * i - 1)) / 2;
				fout.append(place - atk).append("\n");
			}
		}
		System.out.print(fout);
	}
}
