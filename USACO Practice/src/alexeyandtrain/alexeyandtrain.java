//package alexeyandtrain;

import java.util.*;
import java.io.*;

public class alexeyandtrain {
	public static void main(String[] args) throws IOException {
		
		//1501A
		
		//simulation, implementation
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long curTime = 0;
			long[][] nums = new long[n][2];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				long a = Integer.parseInt(st.nextToken());
				long b = Integer.parseInt(st.nextToken());
				nums[i][0] = a;
				nums[i][1] = b;
			}
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				long a = nums[i][0];
				long b = nums[i][1];
				long nextDelay = Integer.parseInt(st.nextToken());
				long minimumDelay = (b - a) / 2 + ((b - a) % 2 == 1? 1 : 0);
				long transitTime = 0;
				//System.out.println(minimumDelay);
				if(i == 0) {
					transitTime = a;
				}
				else {
					transitTime = a - nums[i - 1][1];
				}
				//System.out.println(transitTime);
				curTime += transitTime + nextDelay;
				if(i != n - 1) {
					curTime = Math.max(b, curTime + minimumDelay);
				}
				
				//System.out.println("cur: " + curTime);
			}
			fout.append(curTime).append("\n");
		}
		System.out.print(fout);
	}
}
