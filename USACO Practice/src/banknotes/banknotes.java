//package banknotes;

import java.util.*;
import java.io.*;

public class banknotes {
	public static void main(String[] args) throws IOException {
		
		//Codeforces - 1606C
		
		//no weird overflow errors in java
		
		//greedy solution: go from the lowest digit and add as many banknotes as possible. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			long n, k;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			n = Integer.parseInt(st.nextToken());
			k = Integer.parseInt(st.nextToken());
			k ++;
			long prev = 0;
			long ans = 0;
			st = new StringTokenizer(fin.readLine());
			prev = Integer.parseInt(st.nextToken());
			for(int i = 1; i < n; i++) {
				long next = Integer.parseInt(st.nextToken());
				long powerDiff = next - prev;
				long max = (long) (Math.pow((long) 10, powerDiff) - (long) 1);
				ans += (long) Math.pow((long) 10, prev) * Math.min(max, k);
				k -= Math.min(max, k);
				prev = next;
				if(k <= 0) {
					break;
				}
			}
			String temp = "";
	        if(k != 0){
	            temp = k + "";
	        }
	        if(n == 1){
	            fout.append(k).append("\n");
	        }
	        else{
	            fout.append(temp).append(ans).append("\n");
	        }
		}
		System.out.print(fout);
	}
}
