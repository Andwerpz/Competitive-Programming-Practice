//package catcycle;

import java.util.*;
import java.io.*;

public class catcycle {
	public static void main(String[] args) throws IOException {
		
		//1487B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			if(n % 2 == 0) {
				fout.append(k % n == 0? n : k % n).append("\n");
			}
			else {
				int skip = n / 2;
				long ans = 1;
				long skipAmt = (k - 1) / skip;
				long remainder = (k - 1) % skip;
				ans += skipAmt * (skip + 1) + remainder;
				ans = ans % n == 0? n : ans % n;
				//System.out.println(skipAmt + " " + remainder + " " + skip);
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
