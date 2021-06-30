package ayoubsfunction;

import java.util.*;
import java.io.*;

public class ayoubsfunction {
	
	public static long sum(long n) {
		return (n * (n + 1)) / 2;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1301C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long m = Integer.parseInt(st.nextToken());
			long numOnes = m;
			long numZero = n - m;
			if(numOnes <= numZero - 1) {
				fout.append(sum(n - 1)).append("\n");
			}
			else {
				long rem = numZero % (m + 1);
				long mult = numZero / (m + 1) + 1;
				long first = (sum(m) - sum(rem - 1)) * mult - sum(m - rem);
				long second = sum(rem - 1) * mult;
				fout.append(first + second).append("\n");
			}
		}
		System.out.print(fout);
	}
}
