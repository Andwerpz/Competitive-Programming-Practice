//package extraelement;

import java.util.*;
import java.io.*;

public class extraelement {
	
	public static boolean isValid(int index, long[][] nums) {
		long prev = 0;
		long diff = -1;
		for(int i = 0; i < nums.length; i++) {
			if(i == 0) {
				prev = nums[i][0];
			}
			else if(i == index) {
				continue;
			}
			else {
				if(diff == -1) {
					diff = nums[i][0] - prev;
				}
				else {
					if(diff != nums[i][0] - prev) {
						return false;
					}
				}
				prev = nums[i][0];
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1185D
		
		//man, this problem was annoying. 
		
		//if n > 4, then find the difference that appears the most. If there are more than 2 occurrences of a difference other than the max difference, then the input is invalid. 
		//if there are exactly 2 occurrences, then see if they are adjacent. If they are, see if they add up to the max difference. If they do, then remove the number that is causing that 
		//difference, and if they don't, then the input is invalid. If there is only 1 occurrence, then the extra number is at one end, and figure out which end it is on and remove it.
		
		//in the cases that n < 4, then you can always remove 1 number to make an arithmetic sequence. 
		//if n == 4, then just try removing each number and testing whether it makes an arithmetic sequence. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long[][] nums = new long[n][2];
		for(int i = 0; i < n; i++) {
			nums[i][0] = Integer.parseInt(st.nextToken());
			nums[i][1] = i;
		}
		long[] diff = new long[n - 1];
		Arrays.sort(nums, (a, b) -> Long.compare(a[0], b[0]));
		HashMap<Long, Integer> dict = new HashMap<Long, Integer>();
		for(int i = 0; i < n - 1; i++) {
			diff[i] = Math.abs(nums[i][0] - nums[i + 1][0]);
			dict.put(diff[i], dict.getOrDefault(diff[i], 0) + 1);
		}
		long maxDiff = 0;
		int maxDiffNum = 0;
		for(long i : dict.keySet()) {
			if(dict.get(i) > maxDiffNum || i > maxDiff && dict.get(i) == maxDiffNum) {
				maxDiff = i;
				maxDiffNum = dict.get(i);
			}
		}
		boolean isValid = true;
		boolean seen = false;
		int seenIndex = 0;
		//System.out.println(maxDiff);
		for(int i = 0; i < diff.length; i++) {
			if(diff[i] != maxDiff) {
				//System.out.println(diff[i] + " " + i);
				if(seen) {
					isValid = false;
					break;
				}
				seenIndex = (int)nums[i + 1][1] + 1;
				seen = true;
				if(i == 0) {
					if(diff[i + 1] + diff[i] == maxDiff) {
						seenIndex = (int)nums[1][1] + 1;
						i++;
					}
					else {
						seenIndex = (int)nums[0][1] + 1;
					}
				}
				else if(i != 0 && i != diff.length - 1) {
					if(diff[i + 1] + diff[i] != maxDiff) {
						isValid = false;
						break;
					}
					else {
						i ++;
					}
				}
			}
		}
		if(n == 4 && !isValid) {
			if(extraelement.isValid(1, nums)) {
				System.out.println(nums[1][1] + 1);
			}
			else if(extraelement.isValid(2, nums)) {
				System.out.println(nums[2][1] + 1);
			}
			else {
				System.out.println("-1");
			}
		}
		else if(isValid) {
			if(seen) {
				System.out.println(seenIndex);
			}
			else {
				System.out.println(nums[0][1] + 1);
			}
		}
		else {
			System.out.println("-1");
		}
		//System.out.println(seen + " " + isValid);
	}
}
