//package division;

import java.util.*;
import java.io.*;

public class division {
	
	public static boolean isPrime(long val) {
		for(int i = 2; i <= (int) Math.sqrt(val); i++) {
			//System.out.println("YES");
			if(val % i == 0) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1444A
		
		//lots of repeated variables, next time i should figure out a better implementation
		
		//if p is not divisible by q, then the answer is always p.
		
		//if p is divisible by q, then we need to isolate 1 factor of q, and divide until p has less of that factor than q. Take the maximum out of all the factors of q.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long q = Long.parseLong(st.nextToken());
			long k = Long.parseLong(st.nextToken());
			if(q % k != 0) {
				fout.append(q).append("\n");
			}
			else {
				long ans = 0;
				if(isPrime(k)) {
					while(q % k == 0) {
						q /= k;
					}
					ans = q;
				}
				else {
					long multiple = q / k;
					long multiple2 = multiple;
					long k2 = k;
					for(int i = 2; i <= (int) Math.sqrt(k2); i++) {
						//System.out.println(Math.sqrt(k2));
						if(k2 % i == 0) {
							//System.out.println(i + " ----");
							k = k2;
							multiple = multiple2;
							int next = (int) (k / i);
							int qAmt = 0;
							long temp = q;
							while(k % i == 0) {
								k /= i;
							}
							while(multiple % i == 0) {
								//System.out.println("R");
								multiple /= i;
								qAmt ++;
							}
							for(int j = 0; j < qAmt + 1; j++) {
								//System.out.println(j);
								temp /= i;
							}
							ans = Math.max(temp, ans);
							int old = i;
							k = k2;
							i = next;
							multiple = multiple2;
							qAmt = 0;
							temp = q;
							while(k % i == 0) {
								k /= i;
							}
							while(multiple % i == 0) {
								//System.out.println("R");
								multiple /= i;
								qAmt ++;
							}
							for(int j = 0; j < qAmt + 1; j++) {
								//System.out.println(j);
								temp /= i;
							}
							ans = Math.max(temp, ans);
							//System.out.println(old + " " + next);
							i = old;
						}
					}
				}
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
