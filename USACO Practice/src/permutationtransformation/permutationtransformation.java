//package permutationtransformation;

import java.util.*;
import java.io.*;

public class permutationtransformation {
	
	static int[] ans;
	
	public static void getMax(int[] nums, int l, int r, int layer) {
		int maxIndex = 0;
		int max = 0;
		for(int i = l; i <= r; i++) {
			if(nums[i] > max) {
				maxIndex = i;
				max = nums[i];
			}
		}
		ans[maxIndex] = layer;
		if(l == r) {
			return;
		}
		else if(maxIndex == l) {
			getMax(nums, l + 1, r, layer + 1);
		}
		else if(maxIndex == r) {
			getMax(nums, l, r - 1, layer + 1);
		}
		else {
			getMax(nums, l, maxIndex - 1, layer + 1);
			getMax(nums, maxIndex + 1, r, layer + 1);
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1490D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			ans = new int[n];
			getMax(nums, 0, n - 1, 0);
			for(int i = 0; i < n; i++) {
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
