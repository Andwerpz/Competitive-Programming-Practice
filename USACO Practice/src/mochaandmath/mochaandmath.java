//package mochaandmath;

import java.util.*;
import java.io.*;

public class mochaandmath {
	public static void main(String[] args) throws IOException {
		
		//1559A
		
		//notice that using the operations, you can and every number with every other number. So a bit that is present in the answer has to be present in every number.
		
		//just check every bit against every number to see if it is present.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- >0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long power = 1;
			long ans = 0;
			for(int i = 0; i <= 30; i++) {
				boolean isValid = true;
				for(int j = 0; j < n; j++) {
					if(((1 << i) | nums[j]) != nums[j]) {
						isValid = false;
						break;
					}
				}
				if(isValid) {
					ans += power;
				}
				power *= 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
