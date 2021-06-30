//package lordofthevalues;

import java.util.*;
import java.io.*;

public class lordofthevalues {
	public static void main(String[] args) throws IOException {
		
		//1523B
		
		//read the problem statement better you dummy
		
		//for any pair of numbers; a, b, you can transform them into -a, -b by applying operations 1, 2, 1, 2, 1, 2. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			String input = fin.readLine();
			fout.append((n / 2) * 6).append("\n");
			for(int i = 0; i < n / 2; i++) {
				int a = i * 2;
				int b = i * 2 + 1;
				for(int j = 0; j < 6; j++) {
					if(j % 2 == 0) {
						fout.append("1 ").append(a + 1).append(" ").append(b + 1).append("\n");
					}
					else {
						fout.append("2 ").append(a + 1).append(" ").append(b + 1).append("\n");
					}
				}
			}
		}
		System.out.print(fout);
	}
}
