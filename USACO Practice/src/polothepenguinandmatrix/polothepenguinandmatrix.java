//package polothepenguinandmatrix;

import java.util.*;
import java.io.*;

public class polothepenguinandmatrix {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];
		boolean isValid = true;
		int mod = -1;
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
				if(mod == -1) {
					mod = nums[i][j] % d;
				}
				else if(mod != nums[i][j] % d){
					isValid = false;
				}
			}
		}
		if(isValid) {
			int[] diff = new int[n * m];
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					int next = (nums[i][j] - mod) / d;
					//System.out.println(i * m + j);
					diff[i * m + j] = next;
				}
			}
			Arrays.sort(diff);
			int target = diff[diff.length / 2];
			int ans = 0;
			for(int i = 0; i < diff.length; i++) {
				ans += Math.abs(target - diff[i]);
			}
			System.out.println(ans);
		}
		else {
			System.out.println(-1);
		}
	}
}
