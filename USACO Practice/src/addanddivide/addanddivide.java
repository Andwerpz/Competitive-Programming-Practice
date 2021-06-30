//package addanddivide;

import java.util.*;
import java.io.*;

public class addanddivide {
	public static void main(String[] args) throws IOException {
		
		//1485A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int ans = Integer.MAX_VALUE;
			int add = 0;
			while(true) {
				if(b + add != 1) {
					int curB = b + add;
					int curA = a;
					int curAns = add;
					//System.out.println(curB);
					while(curA != 0) {
						//System.out.println(curA);
						curAns ++;
						curA /= curB;
					}
					if(add == 0) {
						ans = curAns;
					}
					else {
						if(ans < curAns) {
							break;
						}
						ans = Math.min(ans, curAns);
					}
				}
				
				
				add ++;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
