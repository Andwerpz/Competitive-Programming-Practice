package permutationbysum;

import java.util.*;
import java.io.*;

public class permutationbysumver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			int s = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			HashSet<Integer> sumPart = new HashSet<Integer>();
			HashSet<Integer> notSum = new HashSet<Integer>();
			for(int i = 1; i <= n; i++) {
				nums[i - 1] = i;
			}
			int counter = r - l + 1;
			for(int i = n; i >= 1; i--) {
				System.out.println(s);
				 if((i == s && counter == 1) || (s - i >= i)) {
					 sumPart.add(i);
					 s -= i;
					 counter --;
				 }
				 else {
					 notSum.add(i);
				 }
			}
			if(s != 0 || sumPart.size() != r - l + 1) {
				fout.append("-1\n");
			}
			else {
				for(int i = 0; i < n; i++) {
					if(i >= l && i <= r) {
						int next = sumPart.iterator().next();
						fout.append(next).append(" ");
						sumPart.remove(next);
					}
					else {
						int next = notSum.iterator().next();
						fout.append(next).append(" ");
						notSum.remove(next);
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
