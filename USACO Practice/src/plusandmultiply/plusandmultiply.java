//package plusandmultiply;

import java.util.*;
import java.io.*;

public class plusandmultiply {
	public static void main(String[] args) throws IOException {
		
		//1542B
		
		//lets say that n exists within the set.
		//how many different values of n % b can occur in the set? You can notice that it is only when we do x * a that we generate a new value of n % b.
		//And notice that if a value n % b == m, then all values greater than n, a, if a % b == m, then a is also in the set.
		//just generate all the powers of a up until n. If n % b == power of a % b, then n is in the set.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			if(b == 1) {
				fout.append("Yes\n");
			}
			else if(a == 1) {
				if((n - 1) % b == 0) {
					fout.append("Yes\n");
				}
				else {
					fout.append("No\n");
				}
			}
			else {
				boolean isValid = false;
				long pointer = 1;
				while(pointer <= n) {
					if(n % b == pointer % b) {
						isValid = true;
						break;
					}
					pointer *= a;
				}
				fout.append(isValid? "Yes\n" : "No\n");
			}
		}
		System.out.print(fout);
	}
}
