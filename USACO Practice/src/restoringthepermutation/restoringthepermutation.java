//package restoringthepermutation;

import java.util.*;
import java.io.*;

public class restoringthepermutation {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashSet<Integer> missing = new HashSet<Integer>();
			for(int i = 1; i <= n; i++) {
				missing.add(i);
			}
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(missing.contains(nums[i])){
					missing.remove(nums[i]);
				}
				else {
					nums[i] = 0;	//removing extra occurrences of the lead number to make constructing the strings easier
				}
			}
			int[] m = new int[missing.size()];
			int c = 0;
			for(int i : missing) {
				m[c] = i;
				c ++;
			}
			Arrays.sort(m);
			c = 0;
			for(int i = 0; i < nums.length; i++) {	//min permutation
				if(nums[i] != 0) {
					fout.append(nums[i]).append(" ");
				}
				else {
					fout.append(m[c]).append(" ");
					c++;
				}
			}
			fout.append("\n");
			TreeSet<Integer> tree = new TreeSet<Integer>();	//tree set feels like cheating, could do this with segment tree for maximum
			tree.addAll(missing);
			int curMax = 0;
			for(int i = 0; i < nums.length; i++) {	//max permutation
				if(nums[i] != 0) {
					fout.append(nums[i]).append(" ");
					curMax = nums[i];
				}
				else {
					int next = tree.floor(curMax);
					fout.append(next).append(" ");
					tree.remove(next);
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
