//package omkarandbadstory;

import java.util.*;
import java.io.*;

public class omkarandbadstory {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1536A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			ArrayList<Integer> nums = new ArrayList<Integer>();
			boolean negative = false;
			for(int i = 0; i < n; i++) {
				nums.add(Integer.parseInt(st.nextToken()));
				if(nums.get(nums.size() - 1) < 0) {
					negative = true;
				}
			}
			if(!negative) {
				fout.append("YES\n");
				int gcd = nums.get(0);
				int max = 0;
				for(int i = 0; i < n; i++) {
					max = Math.max(nums.get(i), max);
					gcd = gcd(gcd, nums.get(i));
				}
				for(int i = gcd; i < max; i += gcd) {
					if(!nums.contains(i)) {
						nums.add(i);
					}
				}
				fout.append(nums.size()).append("\n");
				for(int i = 0; i < nums.size(); i++) {
					fout.append(nums.get(i)).append(" ");
				}
				fout.append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
