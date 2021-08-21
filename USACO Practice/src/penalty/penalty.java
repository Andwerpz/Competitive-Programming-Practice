//package penalty;

import java.util.*;
import java.io.*;

public class penalty {
	public static void main(String[] args) throws IOException {
		
		//1553C
		
		//we can test two scenarios, and take the minimum: make team 1 win, and make team 2 win. Since the input is small, we can just simulate it.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int ans = 10;
			int t1Score = 0;
			int t1Kicks = 5;
			int t2Score = 0;
			int t2Kicks = 5;
			for(int i = 0; i < s.length; i++) {
				if(i % 2 == 0) {
					if(s[i] != '0') {
						t1Score ++;
					}
					t1Kicks --;
				}
				else {
					if(s[i] == '1') {
						t2Score ++;
					}
					t2Kicks --;
				}
				if(t1Score + t1Kicks < t2Score || t2Score + t2Kicks < t1Score) {
					ans = Math.min(ans, i + 1);
					break;
				}
				//System.out.println(t1Score + " " + t1Kicks + " " + t2Score + " " + t2Kicks);
			}
			//System.out.println();
			t1Score = 0;
			t1Kicks = 5;
			t2Score = 0;
			t2Kicks = 5;
			for(int i = 0; i < s.length; i++) {
				if(i % 2 == 0) {
					if(s[i] == '1') {
						t1Score ++;
					}
					t1Kicks --;
				}
				else {
					if(s[i] != '0') {
						t2Score ++;
					}
					t2Kicks --;
				}
				if(t1Score + t1Kicks < t2Score || t2Score + t2Kicks < t1Score) {
					ans = Math.min(ans, i + 1);
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
