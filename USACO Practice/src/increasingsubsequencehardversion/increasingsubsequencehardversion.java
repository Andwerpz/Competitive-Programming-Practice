//package increasingsubsequencehardversion;

import java.util.*;
import java.io.*;

public class increasingsubsequencehardversion {
	public static void main(String[] args) throws IOException {
		
		//1157C2
		
		//keep track of the maximum number you have taken so far. 
		//when there is a decision, and both numbers are valid, take the minimum number. If both numbers are equal, then test each side for the longest increasing subarray, and 
		//take the side with the longest increasing subarray.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int ans = 0;
		int low = 0;
		int high = n - 1;
		int min = 0;
		StringBuilder fout = new StringBuilder();
		while(low <= high) {
			//System.out.println("START: " + low + " " + high + " " + min);
			if(low == high) {
				if(nums[low] > min) {
					fout.append("L");
					ans ++;
				}
				break;
			}
			else if(nums[low] > min && nums[high] > min) {
				//System.out.println("YES");
				if(nums[low] < nums[high]) {
					fout.append("L");
					min = nums[low];
					low ++;
					ans ++;
				}
				else if(nums[high] < nums[low]) {
					fout.append("R");
					min = nums[high];
					high --;
					ans ++;
				}
				else if(nums[high] == nums[low]) {
					//System.out.println("YES");
					StringBuilder left = new StringBuilder();
					StringBuilder right = new StringBuilder();
					int tempMin = min;
					for(int i = low; i < high; i++) {
						int next = nums[i];
						if(next <= tempMin) {
							break;
						}
						else {tempMin = next;
							left.append("L");
						}
					}
					for(int i = high; i > low; i--) {
						int next = nums[high];
						if(next <= min) {
							break;
						}
						else {min = nums[high];
							right.append("R");
							high --;
							
						}
					}
					//System.out.println("LEFT: " + left + " RIGHT: " + right);
					fout.append(left.length() > right.length()? left.toString() : right.toString());
					ans += left.length() > right.length()? left.length() : right.length();
					break;
				}
			}
			else if(nums[low] > min) {
				for(int i = low; i < high; i++) {
					int next = nums[low];
					if(next <= min) {
						break;
					}
					else {min = nums[low];
						ans ++;
						fout.append("L");
						low ++;
						
					}
				}
				break;
			}
			else if(nums[high] > min) {
				for(int i = high; i > low; i--) {
					int next = nums[high];
					if(next <= min) {
						break;
					}
					else {min = nums[high];
						ans ++;
						fout.append("R");
						high --;
						
					}
				}
				break;
			}
			else {
				break;
			}
			//System.out.println(low + " " + high);
		}
		System.out.println(ans + "\n" + fout);
	}
}
