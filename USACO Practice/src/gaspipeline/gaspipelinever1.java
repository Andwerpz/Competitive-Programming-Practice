package gaspipeline;

import java.util.*;
import java.io.*;

public class gaspipelinever1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			for(int i = 2; i < n - 2; i++) {
				if(s[i - 1] == '1' && s[i + 1] == 1) {
					s[i] = 1;
				}
			}
			//no dp array needed. 
			long high = b;
			long low = b;
			for(int i = 1; i <= n; i++) {
				
				if(i < n && i != 1) {
					if(s[i - 1] == '0') {	//0
						if(s[i] == '0') {	//0 0 
							if(s[i - 2] == '1') {	//we have to go down
								low = high + 2 * a + b;
								high += a + 2 * b;
								//System.out.println("going down " + i);
							}
							else {
								high += a + 2 * b;
								low += a + b;
							}
							
						}
						else {	// 0 1
							high += a + 2 * b;
							low += 2 * a + 2 * b;
							high = Math.min(high, low);	//since at road crossings, we're forced to choose the high route, we can use this to merge the options.
						}
					}
					else {	//1, only action is to do the high pipe
//						if(s[i] == '0') {	//1 0
//							low = high + 2 * a + b;
//							high += a + 2 * b;
//						}
//						else {	//1 1
//							high += a + 2 * b;
//						}
						high += a + 2 * b;
					}
				}
				else if(i == 1) {//special case for first segment since all pipelines start at height 1
					if(s[i] == '0') {
						high += 2 * a + 2 * b;
						low += a + b;
					}
					else {
						high += 2 * a + 2 * b;
						low += 2 * a + 2 * b;
						high = Math.min(high, low);
					}
				}
				else {	//special case for last number, since all pipelines end at height 1.
					if(s[i - 2] == '1') {
						high += 2 * a + b;
						low = high;
					}
					else {
						high += 2 * a + b;
						low += a + b;
					}
				}
				//System.out.println(low + " " + high);
			}
			fout.append(Math.min(high, low)).append("\n");
		}
		System.out.print(fout);
	}
}
