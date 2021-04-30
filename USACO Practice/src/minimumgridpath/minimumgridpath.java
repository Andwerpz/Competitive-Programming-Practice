//package minimumgridpath;

import java.util.*;
import java.io.*;

public class minimumgridpath {
	public static void main(String[] args) throws IOException {
		
		//we need to try all possible amounts of turns from 2 -> n - 1.
		//we can try out each turn amount by keeping track of a running sum of segment costs, and multiplying the least cost segment by the remaining distance for both vertical and horizontal.
		//return the minimum segment.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			long n = Integer.parseInt(fin.readLine());	//longs everywhere lol, hopefully it doesn't take too much memory
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long hMin = Integer.parseInt(st.nextToken());
			long vMin = Integer.parseInt(st.nextToken());
			long hSum = hMin;
			long vSum = vMin;
			long ans = hMin * n + vMin * n;
			long hCount = 0;
			long vCount = 0;
			for(int i = 2; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(i % 2 == 0) {
					if(hMin > next) {
						hMin = next;
					}
					hSum += next;
					hCount ++;
				}
				else {
					if(vMin > next) {
						vMin = next;
					}
					vSum += next;
					vCount ++;
				}
				ans = Math.min(ans, (hSum - hMin) + hMin * (n - hCount) + (vSum - vMin) + vMin * (n - vCount));
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
