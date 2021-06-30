//package elections;

import java.util.*;
import java.io.*;

public class elections {
	
	public static ArrayList<Integer> getMin(int[] a, int[] b) {
		ArrayList<int[]> dict = new ArrayList<int[]>();
		int more = 0;
		int less = 0;
		for(int i = 0; i < a.length; i++) {
			if(a[i] >= b[i]) {
				more += a[i] - b[i];
			}
			else {
				less += b[i] - a[i];
				dict.add(new int[] {i + 1, b[i] - a[i]});
			}
		}
		dict.sort((c, d) -> Integer.compare(c[1], d[1]));
		ArrayList<Integer> ans = new ArrayList<Integer>();
		while(less > more) {
			less -= dict.get(dict.size() - 1)[1];
			ans.add(dict.get(dict.size() - 1)[0]);
			dict.remove(dict.size() - 1);
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1267E
		
		//the inputs are small enough that you can just brute force the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < n; j++) {
				nums[j][i] = Integer.parseInt(st.nextToken());
			}
		}
		ArrayList<Integer> ans = new ArrayList<Integer>();
		for(int i = 0; i < n - 1; i++) {
			if(i == 0) {
				ans = getMin(nums[i], nums[n - 1]);
			}
			else {
				ArrayList<Integer> next = getMin(nums[i], nums[n - 1]);
				if(next.size() < ans.size()) {
					ans = next;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans.size()).append("\n");
		for(int i = 0; i < ans.size(); i++) {
			fout.append(ans.get(i)).append(" ");
		}
		System.out.println(fout);
	}
}
