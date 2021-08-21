//package strangepartition;

import java.util.*;
import java.io.*;

public class strangepartition {
	public static void main(String[] args) throws IOException {
		
		//1471A
		
		//notice that when combining numbers, the x-total will only decrease. So in order to get the largest x-total, you should not combine any numbers, and to get the minimum, you should
		//combine all the numbers into one.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			long min = 0;
			long max = 0;
			long sum = 0;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				long next = Integer.parseInt(st.nextToken());
				max += next / x;
				if(next % x != 0) {
					max ++;
				}
				sum += next;
			}
			min = (sum / x);
			if(sum % x != 0) {
				min ++;
			}
			fout.append(min).append(" ").append(max).append("\n");
		}
		System.out.print(fout);
	}
}
