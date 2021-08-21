//package pokemonarmyeasyversion;

import java.util.*;
import java.io.*;

public class pokemonarmyeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1420C1
		
		//since all the numbers in the array are distinct, the array can be thought of increasing and decreasing segments. Take every peak and valley. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			long ans = 0;
			boolean selected = false;
			int pointer = -1;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = 0; i < n - 1; i++) {
				if(nums[i] > nums[i + 1] && !selected) {
					selected = true;
					pointer = i;
					ans += nums[i];
				}
				else if(nums[i] < nums[i + 1] && selected) {
					selected = false;
					pointer = i;
					ans -= nums[i];
				}
			}
			if(!selected) {
				int max = 0;
				for(int i = pointer + 1; i < n; i++) {
					max = Math.max(nums[i], max);
				}
				ans += max;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
