//package armchairs;

import java.util.*;
import java.io.*;

public class armchairs {
	public static void main(String[] args) throws IOException {
		
		//1525D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			//System.out.print(nums[i] + " " );
		}
		//System.out.println();
		int ans = 0;
		for(int i = 0; i < n; i++) {
			
			if(nums[i] == 1) {
				int dist = 1;
				while(true) {
					//
					if(i - dist >= 0 && nums[i - dist] == 0) {
						nums[i - dist] = 2;
						break;
					}
					if(i + dist < n && nums[i + dist] == 0) {
						nums[i + dist] = 2;
						break;
					}
					dist ++;
				}
				ans += dist;
			}
		}
		System.out.println(ans);
	}
}
