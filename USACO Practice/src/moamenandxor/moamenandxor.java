package moamenandxor;

import java.util.*;
import java.io.*;

public class moamenandxor {
	public static void main(String[] args) throws IOException {
		
		//1557C
		
		//gotta figure this one out later, combination math is hard.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long mod = (long) (1e9 + 7);
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long k = Integer.parseInt(st.nextToken());
			long ans = 1;
			long layer = 1;
			for(int i = 0; i < n - 1; i += 2) {
				layer *= n - i;
				layer %= mod;
				layer *= n - i - 1;
				layer %= mod;
			}
			System.out.println(layer);
			for(int i = 0; i < k - 1; i++) {
				ans *= layer;
				ans %= mod;
			}
			System.out.println("ANS: " + ans);
			if(k != 0) {
				ans *= layer - 1;
				ans %= mod;
			}
			if(n % 2 == 0 && k != 0) {
				long add = 1;
				layer = 1;
				for(int i = 0; i < n; i++) {
					layer *= 2;
					layer %= mod;
				}
				for(int i = 0; i < k - 1; i ++) {
					add *= layer;
					add %= mod;
				}
				ans += add;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
