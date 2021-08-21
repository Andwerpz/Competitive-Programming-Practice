//package gregorandthepawngame;

import java.util.*;
import java.io.*;

public class gregorandthepawngame {
	public static void main(String[] args) throws IOException {
		
		//1549B
		
		//for each pawn on the bottom row, greedily see if you can make it to the top row.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] top = fin.readLine().toCharArray();
			char[] bottom = fin.readLine().toCharArray();
			int ans = 0;
			for(int i = 0; i < n; i++) {
				if(bottom[i] == '1') {
					if(top[i] == '0') {
						ans ++;
					}
					else if(i - 1 >= 0 && top[i - 1] == '1') {
						ans ++;
					}
					else if(i + 1 != n && top[i + 1] == '1') {
						top[i + 1] = '-';
						ans ++;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
