//package yetanothercountingproblem;

import java.util.*;
import java.io.*;

public class yetanothercountingproblem {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1342C
		
		//the observation is that given a and b, the pattern repeats every lcm(a, b). Since a and b are restricted to 200, it is easy to construct an array 
		//holding goodness for each number within 1 -> lcm(a, b).
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int q = Integer.parseInt(st.nextToken());
			int gcd = gcd(a, b);
			int lcm = a * (b / gcd);
			int[] pfx = new int[lcm - 1];
			for(int i = 1; i < lcm; i++) {
				if((i % a) % b != (i % b) % a) {
					pfx[i - 1] ++;
				}
				if(i != 1) {
					pfx[i - 1] += pfx[i - 2];
				}
				//System.out.print(pfx[i - 1] + " ");
			}
			for(int i = 0; i < q; i++) {
				st = new StringTokenizer(fin.readLine());
				long l = Long.parseLong(st.nextToken());
				long r = Long.parseLong(st.nextToken());
				if(r - l + 1 >= lcm) {
					int remainder = (int) (l % lcm);
					long ans = (lcm <= 1 ? 0 : pfx[lcm - 2]) - (remainder <= 1? 0 : pfx[remainder - 2]);
					l += lcm - remainder;
					remainder = (int) (r % lcm);
					ans += remainder == 0? 0 : pfx[remainder - 1];
					r -= remainder;
					//System.out.println("NUM: " + ((r - l + 1l) / (long) lcm));
					ans += ((r - l + 1l) / (long)lcm) * (long)(lcm <= 1 ? 0 : pfx[lcm - 2]);
					fout.append(ans).append(" ");
				}
				else {
					l %= (long)lcm;
					r %= (long)lcm;
					if(l <= r) {
						fout.append((r == 0? 0 : pfx[(int)(r - 1)]) - (l <= 1? 0 : pfx[(int)(l - 2)])).append(" ");
					}
					else {
						int remainder = (int) (l % lcm);
						long ans = pfx[lcm - 2] - (remainder <= 1? 0 : pfx[remainder - 2]);
						remainder = (int) (r % lcm);
						ans += remainder == 0? 0 : pfx[remainder - 1];
						fout.append(ans).append(" ");
					}
					
				}
				
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
