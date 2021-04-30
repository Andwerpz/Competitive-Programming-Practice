//package and0sumbig;

import java.util.*;
import java.io.*;

public class and0sumbig {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int  t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long k = Integer.parseInt(st.nextToken());
			long ans = 1;
			long mod = 1000000007;
			for(int i = 0; i < k; i++) {
				ans *= n;
				ans %= mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
