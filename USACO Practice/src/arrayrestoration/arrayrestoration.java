//package arrayrestoration;

import java.util.*;
import java.io.*;

public class arrayrestoration {
	public static void main(String[] args) throws IOException {
		
		//1023D
		
		//very annoying
		
		//just use a tree set to keep track of the active segments. Make sure to make all remaining 0s into 1s.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		boolean[] v = new boolean[q + 1];
		TreeSet<Integer> dict = new TreeSet<Integer>();
		dict.add(1);
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			int cur = nums[i];
			if(cur != 0) {
				if(v[cur]) {
					isValid = false;
					break;
				}
				if(!dict.contains(cur)) {
					dict.add(cur);
				}
				int next = dict.last();
				while(next > cur) {
					v[next] = true;
					dict.remove(next);
					next = dict.last();
				}
			}
		}
		for(int i : dict) {
			v[i] = true;
		}
		//System.out.println(dict);
		int maxUnvisited = 0;
		if(!v[q]) {
			//System.out.println("YES");
			maxUnvisited = q;
		}
		int[] ans = new int[n];
		for(int i = 0; i < n; i++) {
			if(nums[i] != 0) {
				ans[i] = nums[i];
			}
			else {
				if(maxUnvisited != 0) {
					ans[i] = q;
					maxUnvisited = 0;
				}
				else {
					//System.out.println((i == 0? 0 : nums[i - 1]) + " " + (i == (n - 1)? 0 : nums[i + 1]));
					ans[i] = Math.max((i == 0? 0 : ans[i - 1]), (i == (n - 1)? 0 : nums[i + 1]));
					if(ans[i] == 0) {
						ans[i] = 1;
					}
				}
			}
		}
		if(maxUnvisited == q) {
			isValid = false;
		}
		if(isValid) {
			StringBuilder fout = new StringBuilder();
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
			System.out.print(fout);
		}
		else {
			System.out.println("NO");
		}
	}	
}
