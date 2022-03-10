//package divplusmod;

import java.util.*;
import java.io.*;

public class divplusmod {
	public static void main(String[] args) throws IOException {
		
		//1650B
		
		//you just need to check two values, r, and the highest multiple of a lower than r, -1. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int ans = r / a + r % a;
			int firstMult = (r / a) * a - 1;
			if(firstMult >= l) {
				ans = Math.max(ans, firstMult / a + firstMult % a);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
