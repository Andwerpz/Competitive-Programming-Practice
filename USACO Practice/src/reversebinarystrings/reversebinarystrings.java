//package reversebinarystrings;

import java.util.*;
import java.io.*;

public class reversebinarystrings {
	public static void main(String[] args) throws IOException {
		
		//1437B
		
		//the target string is going to either start with '1' or '0'. Just go along the line and see how many substrings disagree with the target string.
		//the number of reversals required for that target string is the number of bad substrings. Do this for both target strings, and take the min.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			int ans = 0;
			int curAns = 0;
			boolean wrong = false;
			for(int i = 0; i < n; i++) {
				if(s[i] == (i % 2 == 0? '1' : '0')) {
					if(wrong) {
						curAns ++;
					}
					wrong = false;
				}
				else {
					wrong = true;
					if(i == n - 1) {
						wrong = false;
						curAns ++;
					}
				}
			}
			ans = curAns;
			curAns = 0;
			for(int i = 0; i < n; i++) {
				if(s[i] == (i % 2 == 1? '1' : '0')) {
					if(wrong) {
						curAns ++;
					}
					wrong = false;
				}
				else {
					wrong = true;
					if(i == n - 1) {
						wrong = false;
						curAns ++;
					}
				}
			}
			ans = Math.min(ans, curAns);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
